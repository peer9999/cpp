#include <stdio.h>
#include "config.h"

#define TMPFNAME "/tmp/psXXXXXX"

char tmpf [] = TMPFNAME;
char *BINDIR = "/usr/local/bin";

extern FILE *f2open (), *popen ();
extern long filesize (), time ();
extern char *mktemp ();
extern int umask (), fork (), sleep (), close (), creat (), unlink ();
extern int pclose ();
extern void exit (), strcpy ();

extern int config (), log (), f2access (), getstr (), ffncopy (), ffcopy ();
extern void sigign (), f2clean (), error ();

/*
 * Abnormal termination of program.
 */

void quit ()
{
    exit (-1);
}

/*
 * Output error message to log file.
 * VARARGS1
 */

void error (s, a, b, c, d)
char *s, *a, *b, *c, *d;
{
    log (LOGFILE, DAEMON, s, a, b, c, d);
}

/*
 * Scan line from specefied offset to find
 * string, beginning with "From ".
 * Return offset.
 */

long findfrom (fd, off, fromptr)
FILE *fd;
long off;
char **fromptr;
{
    register c, boln, bof;
    register long ret;
    static char from [100];
    char *p;

    fseek (fd, off, 0);
    bof = 1;
    boln = 1;
    ret = off;
    *fromptr = "";
    for (;;) {
        c = getc (fd);
        if (c < 0)
            return (bof ? -1 : off);
        bof = 0;
        ++off;
        if (c == '\n') {
            boln = 1;
            ret = off;
            continue;
        }
        if (boln && c == 'F') {
            if (getc (fd) == 'r' && getc (fd) == 'o' && getc (fd) == 'm' && getc (fd) == ' ') {
                fgets (from, sizeof (from), fd);
                *fromptr = from;
                for (p = from; *p && *p != ' ' && *p != '\n' && *p != '\r'; ++p);
                *p = 0;
                return (ret);
            }
            off = ret + 1;
            fseek (fd, off, 0);
        }
        boln = 0;
    }
}

/*
 * Get next free queue ident from ident file.
 * Increment ident in file.
 */

int getident ()
{
    FILE *fd;
    int ident;

    /* if queue file does not exist, create it */
    if (f2access (SERVDIR, "queueident", 0))
        f2clean (SERVDIR, "queueident");

    /* open queue file */
    fd = f2open (SERVDIR, "queueident", "r+");
    if (! fd) {
        error ("Не могу открыть %s/queueident", SERVDIR);
        quit ();
    }

    /* get next free ident from ident file */
    ident = 0;
    fscanf (fd, "%d", &ident);

    /* increment ident */
    rewind (fd);
    fprintf (fd, "%d          \n", ident + 1);
    fclose (fd);

    return (ident);
}

/*
 * Append batch file name to atcive queue file.
 */

void enqueue (name)
char *name;
{
    FILE *fd;

    /* open active file for appending */
    fd = f2open (SERVDIR, "queueactive", "a");
    if (! fd) {
        error ("Не могу открыть  %s/queueactive", SERVDIR);
        quit ();
    }
    fprintf (fd, "%s\n", name);
    fclose (fd);
}

void runqueuer ()
{
    FILE *fd, *tfd;
    register long beg, next;
    int ident;
    char name [100];
    char from [100], *fromptr;

    fd = fopen (MAILBOX, "r");
    if (! fd) {
        error ("Не могу прочитать %s", MAILBOX);
        return;
    }
    beg = findfrom (fd, 0L, &fromptr);
    strcpy (from, fromptr);
    for (;;) {
        next = findfrom (fd, beg + 1, &fromptr);
        if (next < 0)
            break;

        /* get next free queue ident */
        ident = getident ();

        /* make queue file name */
        sprintf (name, "%s/queue/q%d", SERVDIR, ident);

        /* create queue file */
        tfd = fopen (name, "w");
        if (! tfd) {
            error ("Не могу открыть %s", name);
            quit ();
        }

        /* save query into queue file */
        fseek (fd, beg, 0);
        ffncopy (fd, tfd, next - beg);
        if (ferror (tfd)) {
            error ("Ошибка записи в %s", name);
            quit ();
        }
        fclose (tfd);

        /* append name of query to queue active file */
        enqueue (name);

        error ("Задание %d от %s", ident, from);
        beg = next;
        strcpy (from, fromptr);
    }
    fclose (fd);
    if (close (creat (MAILBOX, 0600)) < 0) {
        error ("Не могу переоткрыть %s", MAILBOX);
        quit ();
    }
}

/*
 * Get content of active file into temp file,
 * then clean active file.
 * Leave temp file rewinded.
 */

int dequeue (actfd)
FILE *actfd;
{
    FILE *fd;

    /* open active file for reading */
    fd = f2open (SERVDIR, "queueactive", "r");
    if (! fd)
        return (1);     /* no active jobs in queue */

    /* copy active file to temp file */
    if (ffcopy (fd, actfd) < 0) {
        fclose (fd);
        return (0);
    }
    fclose (fd);
    rewind (actfd);

    /* clean active file */
    f2clean (SERVDIR, "queueactive");
    return (1);
}

/*
 * Process batch job.
 */

int batch (name)
char *name;
{
    char buf [256];
    FILE *pd, *fd;

    if (f2access (BINDIR, "/pserver", 1)) {
        error ("Не могу выполнить %s/pserver", BINDIR);
        return (0);
    }
    sprintf (buf, "%s/pserver", BINDIR);
    pd = popen (buf, "w");
    if (! pd) {
        error ("Не могу выполнить '%s'", buf);
        return (0);
    }
    fd = fopen (name, "r");
    if (! fd) {
        error ("Не могу прочитать '%s'", name);
        pclose (pd);
        return (0);
    }
    ffcopy (fd, pd);
    fclose (fd);
    pclose (pd);
    sleep (1);
    return (1);
}

void runbatcher ()
{
    FILE *actf;
    char name [100];

    /* open temp file on read/write */
    close (creat (tmpf, 0664));
    actf = fopen (tmpf, "r+");
    if (! actf) {
        error ("Не могу создать %s", tmpf);
        quit ();
    }
    unlink (tmpf);

    /* get queue active file into temp file */
    if (! dequeue (actf))
        quit ();

    /* process batches */
    while (getstr (actf, name)) {
        if (! *name)
            continue;
        if (batch (name))
            error ("Обработан %s", name);
        unlink (name);
    }
    fclose (actf);
}

int main (argc, argv)
int argc;
char **argv;
{
    int pid;
    char qactivefile [256];

    umask (002);
    if (argc > 2) {
        fprintf (stderr, "usage: %s [config-file]\n", argv [0]);
        exit (-1);
    }
    if (! config (argv [1])) {
        fprintf (stderr, "cannot read config file\n");
        exit (-1);
    }

    /* let's fork */
    pid = fork ();
    if (pid < 0) {
        fprintf (stderr, "%s: cannot fork\n", argv [0]);
        exit (-1);
    }
    if (pid)
        exit (0);
    /* now we are a child */

    /* make temp file name */
    mktemp (tmpf);

    /* catch signals */
    sigign ();

    error ("Демон запущен");

    sprintf (qactivefile, "%s/queueactive", SERVDIR);
    for (;;) {
        if (filesize (MAILBOX))
            runqueuer ();
        if (filesize (qactivefile))
            runbatcher ();
        sleep (DAEMONDELAY);
    }

    /* NOTREACHED */
}
