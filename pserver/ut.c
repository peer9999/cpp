#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <signal.h>
#include "config.h"

#define TFILENAME      "/tmp/psbXXXXXX"
#define INFEXT         ".inf"

#ifdef SIGVOID
#define SIGTYPE void
#else
#define SIGTYPE int
#endif

extern char *ctime (), *mktemp (), *malloc (), *strcpy (), *time2a ();
extern char *strrchr (), *strcat ();
/*extern long time ();*/
FILE *f2open ();
extern int strlen (), strcmp (), access (), sleep (), creat (), unlink ();
extern int close ();
extern void error (), exit (), quit ();

/*
 * Get string from file.
 * Return 1 if ok, else 0.
 */

int getstr (fd, s)
FILE *fd;
register char *s;
{
    register c;

    while ((c = getc (fd)) >= 0 && c != '\n')
        *s++ = c;
    *s = 0;
    return (c >= 0);
}

/*
 * Copy file to stdout, up to ^Z, deleting ^M.
 * Return 0 on success, -1 on error.
 */

int fcat (name)
char *name;
{
    FILE *fd;
    register c;

    fd = fopen (name, "r");
    if (! fd)
        return (-1);
    while ((c = getc (fd)) >= 0 && c != '\32')
        if (c != '\15')
            putchar (c);
    fclose (fd);
    return (0);
}

int f2cat (dir, file)
char *dir, *file;
{
    char buf [256];

    strcpy (buf, dir);
    strcat (buf, "/");
    strcat (buf, file);
    return (fcat (buf));
}

/*
 * Copy file to file.
 * Return 0 on success,
 * -1 on read error,
 * -2 on write error.
 */

int ffcopy (from, to)
FILE *from, *to;
{
    char buf [512], *p;
    register n, k;

    for (;;) {
        n = fread (buf, 1, sizeof (buf), from);
        if (n < 0) {
            error ("ïÛÉÂËÁ ŞÔÅÎÉÑ");
            return (-1);
        }
        if (n == 0)
            break;
        p = buf;
        while (n > 0) {
            k = fwrite (p, 1, n, to);
            if (k <= 0) {
                error ("ïÛÉÂËÁ ÚÁĞÉÓÉ");
                return (-2);
            }
            n -= k;
            p += k;
        }
    }
    return (0);
}

/*
 * Copy len bytes from file to file.
 * Return 0 on success,
 * -1 on read error,
 * -2 on write error.
 */

int ffncopy (from, to, len)
FILE *from, *to;
long len;
{
    char buf [512], *p;
    register n, k;

    while (len > 0) {
        n = fread (buf, 1, sizeof (buf), from);
        if (n < 0) {
            error ("ïÛÉÂËÁ ŞÔÅÎÉÑ");
            return (-1);
        }
        if (n == 0)
            break;
        if (n > len)
            n = len;
        len -= n;
        p = buf;
        while (n > 0) {
            k = fwrite (p, 1, n, to);
            if (k <= 0) {
                error ("ïÛÉÂËÁ ÚÁĞÉÓÉ");
                return (-2);
            }
            n -= k;
            p += k;
        }
    }
    return (0);
}

int log (logfile, progname, s, a, b, c, d)
char *logfile, *progname, *s, *a, *b, *c, *d;
{
    FILE *fd;

    fd = fopen (logfile, "a");
    if (! fd)
        return (-1);
    fprintf (fd, "%s  ", time2a (time ((long *) 0)));
    if (progname)
        fprintf (fd, "%s  ", progname);
    fprintf (fd, s, a, b, c, d);
    fprintf (fd, "\n");
    fclose (fd);
    return (0);
}

/*
 * Wait until queue is unlocked,
 * then lock it by creating lock file.
 */

void lock (name)
char *name;
{
    /* wait while queue is locked */
    while (! access (name, 0))
        sleep (1);

    /* lock queue */
    if (creat (name, 0) < 0) {
        error ("îÅ ÍÏÇÕ ÓÏÚÄÁÔØ %s", name);
        exit (-1);
    }
}

/*
 * Return 1 if file is locked.
 */

int locked (name)
char *name;
{
    return (! access (name, 0));
}

/*
 * Unlock queue by deleting lock file
 */

void unlock (name)
char *name;
{
    unlink (name);
}

/*
 * Signal catched, unlock and exit.
 */

SIGTYPE catcher ()
{
    error ("signal catched");
    quit ();
}

/*
 * Set cather of signal, if it is not ignored.
 */

void catch (sig, fun)
int sig;
SIGTYPE (*fun) ();
{
    if (signal (sig, SIG_IGN) != SIG_IGN)
        signal (sig, fun);
}

/*
 * Set up signal catcher.
 */

void sigcatch ()
{
    catch (SIGINT, catcher);
    catch (SIGQUIT, catcher);
    catch (SIGTERM, catcher);
}

void sigign ()
{
    signal (SIGINT, SIG_IGN);
    signal (SIGQUIT, SIG_IGN);
    signal (SIGTERM, catcher);
}

long filesize (name)
char *name;
{
    struct stat x;

    if (stat (name, &x) < 0)
        return (0);
    return (x.st_size);
}

long file2size (dir, file)
char *file;
{
    struct stat x;
    char buf [256];

    strcpy (buf, dir);
    strcat (buf, "/");
    strcat (buf, file);

    if (stat (buf, &x) < 0)
        return (0);
    return (x.st_size);
}

char *strlower (str)
char *str;
{
    register char *p;

    for (p = str; *p; ++p) {
        if (*p >= 'A' && *p <= 'Z')
            *p += 'a' - 'A';
        if (*p >= (char)0340 && *p <= (char)0376)
            *p -= 040;
    }
    return (str);
}

/*
 * °¢•Ÿ’¢‘ªŸ§‘™• §¢••™ (£•›¥”© Ÿ¤ 00:00:00 1.1.70)
 * § ¤•›£¤Ÿ§Ÿ•  ¢•”£¤‘§œ•™•.  ·Ÿª§¢‘­‘•¤£¡ ¥›‘ª‘¤•œ¨
 * ‘ §¥¤¢•™š stati£ ’¥–•¢.
 * °¢•”£¤‘§œ•™• §¢••™: dd.mm.yy/hh:mm:ss
 */

char *time2a (tim)
long tim;
{
    struct tm *ptm, *localtime();
    static char cdate [30];

    ptm = localtime (&tim);
    sprintf (cdate, "%02d.%02d.%02d/%02d:%02d:%02d",
        ptm->tm_mday, ptm->tm_mon + 1, ptm->tm_year,
        ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
    return (cdate);
}

/*
 * ³Ÿ Ÿ£¤‘§œ•™• £ «‘’œŸŸ. · £œ¥®‘• ¥£ •˜‘ §Ÿª§¢‘­‘•¤ 1.
 * »‘’œŸ Ÿ¦•¤ £Ÿ”•¢¦‘¤¨ £œ•”¥­™• £™§Ÿœ©:
 *
 * ^       - § ‘®‘œ• «‘’œŸ‘ - Ÿ¤¢™“‘™• «‘’œŸ‘
 * *       - œ’‘¡ £¤¢Ÿ›‘
 * ?       - œ’Ÿš £™§Ÿœ
 * [a-z]   - £™§Ÿœ § ”™‘ ‘ªŸ•
 * [^a-z]  - £™§Ÿœ §• ”™‘ ‘ªŸ‘
 */

int match (s, p)
register char *s, *p;
{
    register scc;
    int c, yes;

    yes = 1;
    if (*p == '^') {
        yes = 0;
        ++p;
    }
    for (;;) {
        scc = *s++ & 0377;
        switch (c = *p++) {
            default:
                if ((c & 0377) != scc)
                    return (! yes);
                continue;
            case 0:
                return (scc==0 ? yes : !yes);
            case '?':
                if (scc == 0)
                    return (! yes);
                continue;
            case '*':
                if (! *p)
                    return (yes);
                for (--s; *s; ++s)
                    if (match (s, p))
                        return (yes);
                return (! yes);
            case '[': {
                int ok, lc, good;
                lc = 077777;
                good = 1;
                if (*p == '^') {
                    good = 0;
                    ++p;
                }
                ok = ! good;
                for (;;) {
                    int cc;
                    cc = *p++;
                    if (cc == 0)
                        return (! yes);         /* Missing ] */
                    if (cc == ']')
                        break;
                    if (cc == '-') {
                        if (lc <= scc && scc <= *p++)
                            ok = good;
                    } else
                        if (scc == (lc = cc))
                            ok = good;
                }
                if (! ok)
                    return (! yes);
                continue;
            }
        }
    }
}

char *strcopy (str)
char *str;
{
    unsigned len = strlen (str);
    char *p = malloc (len+1);

    if (! p) {
        error ("out of memory in strcopy");
        exit (-1);
    }
    strcpy (p, str);
    return (p);
}

int checkpermissions (username, dirname, permfile)
char *username, *dirname, *permfile;
{
    FILE *fd;
    char line [512];
    char *p;
    int permissions;

    fd = f2open (dirname, permfile, "r");
    if (! fd)
        return (0);
    permissions = 0;
    while (getstr (fd, line)) {
        p = line;
        while (*p == ' ' || *p == '\t')
            ++p;
        if (! *p || *p == '#')
            continue;
        if (line[0] == '^') {
            if (match (username, line+1))
                break;
        } else if (match (username, line)) {
            permissions = 1;
            break;
        }
    }
    fclose (fd);
    return (permissions);
}

FILE *f2open (dirname, filename, mode)
char *dirname, *filename, *mode;
{
    char buf [512];

    sprintf (buf, "%s/%s", dirname, filename);
    return (fopen (buf, mode));
}

int f2access (dirname, filename, mode)
char *dirname, *filename;
int mode;
{
    char buf [512];

    sprintf (buf, "%s/%s", dirname, filename);
    return (access (buf, mode));
}

void f2clean (dirname, filename)
char *dirname, *filename;
{
    char buf [512];

    sprintf (buf, "%s/%s", dirname, filename);
    close (creat (buf, 0664));
}

void mkinfoname (name, buf)
char *name, *buf;
{
    char *p;
    register i;
    static char *tab [] = {
        ".cpio", ".ar", ".tar", ".zoo",
        ".zip", ".lzh", ".arc", ".arj",
        ".shar", "gif", ".tif", ".jpg",
        ".pcx", ".pbm", ".pgm", ".ppm",
        ".exe", ".com",
        ".lha", ".dbf", ".dbz", 0,
    };

    strcpy (buf, name);
    p = strrchr (buf, '.');
    if (! p)
        goto ret;
    if (! strcmp (p, ".Z") || ! strcmp (p, ".F")) {
        *p = 0;
        p = strrchr (buf, '.');
        if (! p)
            goto ret;
    }
    for (i = 0; tab[i]; ++i)
        if (! strcmp (p, tab[i])) {
            strcpy (p, INFEXT);
            return;
        }
ret:
    strcat (buf, INFEXT);
}
