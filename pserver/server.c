/*
 *      PhoneStat 3.2
 *      Copyright (C) 1995-99 Ruslan Shevelinski
 */

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <fcntl.h>
#include "config.h"
#include "header.h"
#include "server.h"

#define VERSION        "�������� ����� �������������� ������� PhoneStat (C), ������ 3.2 (19.08.99)"
#define COPYRIGHT      "Copyright (c) 1995-2004, Ruslan Shevelinski, BELPAK"
#define TMPFNAME       "/tmp/dpsXXXXXX"
#define isspace(c)     ((c)==' '||(c)=='\t'||(c)=='\r')

char tmpf [] = TMPFNAME;
char *inputptr;        /* pointer to input line */
char *sender;

extern long filesize (), file2size (), time ();
extern char *getsendername (), *strcopy (), *ctime (), *strcpy (), *strcat ();
extern char *mktemp (), *strlower (), getstr ();
extern FILE *f2open (), *popen ();
extern int unlink (), system (), chdir (), strncmp (), pclose ();
extern void exit ();
extern int log (), runs (), config (), ffcopy (), checkpermissions ();
extern void doquit (), sigcatch (), scanheader ();

char *recoder (str)
char *str;
{
    struct recodes *k, *i;
    unsigned char *p;

    k = altkoi;
    p = str;

    while (*p) {
        for (i = k; i->src ; ++i)
            if (*p == i->src) {
                *p = i->dst;
                break;
            }
        ++p;
    }
    return (str);
}

void quit ()
{
    unlink (tmpf);
    exit (-1);
}

/*
 * Output error message to log file.
 * VARARGS1
 */

void error (s, a, b, c, d)
char *s, *a, *b, *c, *d;
{
    /*
    char cmd [512];
    FILE *fd;

    sprintf (cmd, "%s -f%s %s", MAILTOCMD, MYADDRESS, ADMINISTRATOR);

    fd = popen (cmd, "w");
    if (fd) {
        fprintf (fd, "From: %s\n", MYADDRESS);
        fprintf (fd, "To: %s\n", ADMINISTRATOR);
        fprintf (fd, "Subject: !!! ��������� ��������� ������� PhoneStat !!!\n");
        fprintf (fd, "\n\n");
        fprintf (fd, s, a, b, c, d);
        pclose (fd);
    } else
        log (LOGFILE, MERROR, "�� ���� ��������� '%s'", cmd);
    */

    log (LOGFILE, MERROR, s, a, b, c, d);
}

/*
 * Print error message.
 * VARARGS1
 */

void message (s, a, b, c)
char *s, *a, *b, *c;
{
    printf (s, a, b, c);
    printf ("\n");
}

/*
 * Print fatal error message, copy rest of stdin to stdout,
 * then exit from program.
 * VARARGS1
 */

/*
void fatal (s, a, b, c)
char *s, *a, *b, *c;
{
    register ch, eoln;

    printf ("! ");
    printf (s, a, b, c);
    printf ("\n");
    eoln = 1;
    while ((ch = getchar ()) >= 0) {
        if (eoln) {
            printf ("Ignored: ");
            eoln = 0;
        }
        putchar (ch);
        if (ch == '\n')
            eoln = 1;
    }
    doquit ();
}
*/

int run (s, a, b, c, d, e, f)
char *s, *a, *b, *c, *d, *e, *f;
{
    char buf [1024];

    sprintf (buf, s, a, b, c, d, e, f);
    return (runs (buf));
}

int runs (cmd)
char *cmd;
{
    int status;

    fflush (stdout);
    status = system (cmd);
    if (status)
        message ("Error 0x%x executing %s", status, cmd);
    fseek (stdout, 0L, 2);
    return (status);
}

/*
 * Get sender address from 'From:' field
 * of mail header.
 */

char *getsendername (field)
char *field;
{
    register c;
    register char *cp, *cp2;
    int gotlt, lastsp, level;
    char addr [256];

    gotlt = 0;
    lastsp = 0;
    cp = field;
    cp2 = addr;
    while (c = *cp++)
        switch (c) {
            case '(':
                level = 1;
                while (*cp != '\0' && level) {
                    switch (*cp++) {
                        case '(':
                            level++;
                            break;
                        case ')':
                            level--;
                            break;
                    }
                }
                if (*cp)
                    cp++;
                lastsp = 0;
                break;
            case ' ':
                if (cp[0] == 'a' && cp[1] == 't' && cp[2] == ' ')
                    cp += 3, *cp2++ = '@';
                else if (cp[0] == '@' && cp[1] == ' ')
                    cp += 2, *cp2++ = '@';
                else
                    lastsp = 1;
                break;
            case '<':
                cp2 = addr;
                gotlt++;
                lastsp = 0;
                break;
            case '>':
                if (gotlt)
                    goto done;
                /* Fall into . . . */
            default:
                if (lastsp) {
                    lastsp = 0;
                    *cp2++ = ' ';
                }
                *cp2++ = c;
                break;
        }
done:
    *cp2 = 0;
    if (*addr == '@') {
        char buf [512];
        strcpy (buf, addr);
        strcpy (addr, "root");
        strcat (addr, buf);
    }
    return (strcopy (addr));
}

void replyto (sender, from, smessage, koi)
FILE *from;
char *sender, *smessage, koi;
{
    FILE *fd;
    unsigned count = 2;
    long cont = 0;
    char cmd [512], buf [513];

    buf [512] = 0;
    sprintf (cmd, "%s -f%s %s", MAILTOCMD, MYADDRESS, sender);

    while (fgets (buf, 512, from)) {
        fd = popen (cmd, "w");

        if (! fd) {
            error ("�� ���� ��������� '%s'", cmd);
            quit ();
        }

        fprintf (fd, "From: %s\n", MYADDRESS);
        fprintf (fd, "To: %s\n", sender);
        fprintf (fd, "MIME-Version: 1.0\nContent-Type: text/plain; charset=KOI8-R\nContent-Transfer-Encoding: 8bit\n");

        if (cont) {
            fprintf (fd, "Subject: [PhoneStat] (����� %d) %s\n", count, smessage);
            ++count;
        } else {
            fprintf (fd, "Subject: [PhoneStat] %s\n", smessage);
        }

        fprintf (fd, "\n");

        do {
            if (koi) recoder (buf);
            fputs (buf, fd);
            if (ftell (from) - cont > 1024 * 1024L + 10240) {
                fprintf (fd, "\n--- ����������� � ��������� ������ --------------------------------------------\n");
                break;
            }
        } while (fgets (buf, 512, from));

        putc ('\n', fd);
        pclose (fd);
        cont = ftell (from);
    }
}

/* ���������, ������ �� ������ abc.domain � ����� domain */

int checkdomain (domain, address)
char *domain, *address;
{
    char *p1, *p2, flag;

    if (! strlen (domain))
        return 0;
    if (! strlen (address))
        return 0;

    p1 = domain + strlen (domain) - 1;
    p2 = address + strlen (address) - 1;
    flag = 0;

    while (1) {
        if (*p1 != *p2)
            return 0;
        if (*p1 == '@')
            flag = 1;
        if (p1 == domain) {
            if (p2 == address)
                return 1;
            if (flag == 1)
                return 0;
            --p2;
            if (*p2 == '@' || *p2 == '.')
                return 1;
            else
                return 0;
        } else
            --p1;
        if (p2 == address)
            return 0;
        else
            --p2;
    }
}

void dohelp (sender)
char *sender;
{
    FILE *fd;

    fd = f2open (SERVDIR, "help", "r");

    if (!fd) {
        error ("���� %s/help ����������", SERVDIR);
        quit ();
    }

    puts ("������ ������� ��������� �������");
    replyto (sender, fd, "������", 0);
    log (LOGFILE, SERVER, "�������� ����� ������ ������������ %s", sender);
    fclose (fd);
}

void dodata (sender, dir, file)
char *sender, *dir, *file;
{
    FILE *fd;
    FILE *fd1;
    FILE *fd2;
    DIR *fddir;
    register struct dirent *dirbuf;
    long replysz;
    char smessage [128];
    char name [128], name1[128], name2[128], dirname[128], temp_dir[128];
    char *c_slash="/", *p_pointer;

    strcpy (smessage, "�������������� ���������");

    p_pointer=strstr(dir,c_slash);

    if (p_pointer == NULL) {
        sprintf (temp_dir, "%s/2", dir);
    } else {
        sprintf (temp_dir, "%s", dir);
    }

    sprintf (name, "%s/%s/subject", PUBLICDIR, temp_dir);
    fd = fopen (name, "r");

    if (!fd)
        error ("��� ������� � ���������� ����� %s/%s/subject", PUBLICDIR, temp_dir);
    else {
        if (! fgets (smessage, 128, fd))
            error ("�� ���� ��������� ��������� ���� %s/%s/subject", PUBLICDIR, temp_dir);
        else
            recoder (smessage);
        fclose (fd);
    }

    sprintf (name1, "%s/%s/%s", PUBLICDIR, temp_dir, file);
    fd1 = fopen (name1, "r");

    sprintf (dirname, "%s/%s/", PUBLICDIR, temp_dir);
    fddir = opendir (dirname);
    sprintf (name2, "%s/%s/%s", PUBLICDIR, temp_dir, sender);
    while ((dirbuf = readdir (fddir)) != NULL ) {
        if (strcasecmp(dirbuf->d_name, sender) == 0) {
            sprintf (name2, "%s/%s/%s", PUBLICDIR, temp_dir, dirbuf->d_name);
            continue;
        }
    }
    closedir(fddir);
    fd2 = fopen (name2, "r");

    if (!fd1 && !fd2) {
        puts ("�������������� ��������� �� ��������� ������ ����������\n����������:\n�������������� ��������� ��������� ����� �����������  ������\n�������� �  ���������  ����� ����������� �����,\n����������������   ��������  ������  ������������.");
        error ("��� ������� � ����� %s %s", name1, name2);
    } else {
        if (fd1) {
            puts ("�������������� ��������� ������� ��������� �������");
            replysz = filesize (name1);
            replyto (sender, fd1, smessage, 1);
            log (LOGFILE, SNDATA, "�������� ������ %s ������������ %s ������ %ld ����", name1, sender, replysz);
            fclose (fd1);
        }
        if (fd2) {
            puts ("�������������� ��������� ������� ��������� �������");
            replysz = filesize (name2);
            replyto (sender, fd2, smessage, 1);
            log (LOGFILE, SNDATA, "�������� ������ %s ������������ %s ������ %ld ����", name2, sender, replysz);
            fclose (fd2);
        }
    }

}

void dosubscribe (sender)
char *sender;
{
    char name [128];
    int fd;
    unsigned numrec;
    struct subsrec s;

    sprintf (name, "%s/subscribe", SERVDIR);
    fd = open (name, O_CREAT|O_RDWR, 0664);

    if (fd < 0) {
        error ("�� ���� ������� (�������) ���� %s/subscribe", SERVDIR);
        quit ();
    }

    while (read (fd, &s, sizeof(s)) == sizeof(s))
        if (s.status && !strcmp (s.domain, sender)) {
            puts ("�������������� �������� ���� �������� ���� �����");
            close (fd);
            return;
        }

    lseek (fd, 0L, 0);
    numrec = 0;

    while (1) {
        if (read (fd, &s, sizeof(s)) != sizeof(s))
            break;
        if (!s.status) {
            lseek (fd, (long) numrec*sizeof(s), 0);
            break;
        }
        ++numrec;
    }

    memset (&s, 0, sizeof(s));
    strncpy (s.domain, sender, 127);
    s.status = 1;

    if (write (fd, &s, sizeof(s)) < 0) {
        error ("������ ������ � ���� %s/subscribe", SERVDIR);
        quit ();
    } else
        puts ("�������������� �������� ��������");

    close (fd);
}

void dounsubscribe (sender)
char *sender;
{
    char flag;
    char name [100];
    int fd;
    unsigned numrec;
    struct subsrec s;

    sprintf (name, "%s/subscribe", SERVDIR);
    fd = open (name, O_RDWR);

    if (fd < 0) {
        error ("�� ���� ������� ���� %s/subscribe", SERVDIR);
        quit ();
    }

    numrec = 0;
    flag = 0;

    while (1) {
        if (read (fd, &s, sizeof(s)) != sizeof(s))
            break;
        if (s.status && !strcmp (s.domain, sender)) {
            flag = 1;
            s.status = 0;
            lseek (fd, (long)numrec*sizeof(s), 0);
            if (write (fd, &s, sizeof(s)) < 0) {
                error ("������ ������ � ���� %s/subscribe", SERVDIR);
                quit ();
            } else
                puts ("�������������� �������� ���������");
            break;
        }
        ++numrec;
    }

    if (! flag)
        puts ("�������������� �������� �� ���� ��������");

    close (fd);
}

void dostat (sender)
char *sender;
{
    char domain [9];
    char buf [128];
    char buf_dom [128];
    char *ptr, *dptr;
    long letters, bytes, buf_tr;
    FILE *fd;

    letters = 0;
    bytes = 0;

    fd = fopen (STATFILE, "r");

    if (!fd) {
        error ("���� %s ����������", STATFILE);
        quit ();
    }

    ptr = sender;

    while (*ptr != '@' && *ptr)
        ++ptr;

    if (*ptr)
        ++ptr;

    dptr = domain;

    while (*ptr != '.' && *ptr && (dptr-domain < 9)) {
        *dptr = *ptr;
        ++ptr;
        ++dptr;
    }

    *dptr = '\0';

    while (fgets (buf, 128, fd)) {
        sscanf (buf, "%s%*s%*s%ld", buf_dom, &buf_tr);

        if (!strcmp (domain, buf_dom)) {
            ++letters;
            bytes += buf_tr;
        }
    }

    fclose (fd);

    bytes = (long) bytes / 1024;
    printf ("�������� ����� - %ld, ����� ������� - %ld �����\n", letters, bytes);
}

void docheck (sender)
char *sender;
{
    puts ("������� �� �����������");
}


char *getword ()
{
    register char *p, *s;

    p = inputptr;
    while (isspace (*p))
        ++p;
    if (! *p)
        return (0);
    s = p;
    while (*p && ! isspace (*p))
        ++p;
    if (*p)
        *p++ = 0;
    inputptr = p;
    return (s);
}

unsigned searchcmd (name)
char *name;
{
    register struct cmdtab *t;

    for (t=cmdtable; t->cmdcode; ++t)
        if (! strcmp (t->cmdname, name))
            return (t->cmdcode);
    return (0);
}


/* ���������� ������ � ������ */

void docmd (sender, cmdstr, file)
char *sender, *cmdstr, *file;
{
    char flag;
    register char *p;
    register unsigned cmdcode;

    flag = 0;

    puts ("--------------------------------------------------------------------------------");
    puts ("        ��� ��������� ������� ������ ������ ��������� ������ ������,");
    puts ("        ������  �   ����  ���������  ������  Subject: �������  help");
    puts ("--------------------------------------------------------------------------------\n");

    puts ("> ����� ��������� � ��������� ������, ��������� � ���� Subject:\n");
    inputptr = cmdstr;

    while (inputptr && (p = getword ())) {
        printf ("> %-8s - ", p);
        strlower (p);
        cmdcode = searchcmd (p);

        switch (cmdcode) {
            case 0 :
                puts ("����������� �������");
                break;
            case 1 :
                dohelp (sender);
                flag = 1;
                break;
            case 2 :
                dodata (sender, p, file);
                flag = 1;
                break;
            case 3 :
                dosubscribe (sender);
                flag = 1;
                break;
            case 4 :
                dounsubscribe (sender);
                flag = 1;
                break;
            case 5 :
                docheck (sender);
                flag = 1;
                break;
            case 6 :
                dostat (sender);
                flag = 1;
        }
    }

    if ( ! flag ) {
        puts ("> ...\n");
        puts ("> ����� �� ��������� �� ����� �������� ������� � ���� Subject: ������ ������ �");
        puts ("> ������� ����� ���� ��� ����������� ��� ��� ������������ � ������������� ���-");
        puts ("> ��� ����������������.\n");
        printf ("> �������: ");
        dohelp (sender);
    }
}

/* �������� �� ������� ���������� */
/* ��������� ���������� � ������ 3.0 */

void procsender (sender)
char *sender;
{
    FILE *fd;
    char line [256];
    char l_domain [128], l_file [128];
    char flag;

    flag = 0;

    fd = fopen (DATARCV, "r");
    if (! fd) {
        error ("�� ���� ������� %s", DATARCV);
        quit ();
    }

    while (getstr (fd, line)) {
        if (sscanf (line, "%s%s", l_domain, l_file) != 2)
            continue;
        if (checkdomain (l_domain, sender)) {
            flag = 1;
            break;
        }
    }

    fclose (fd);

    if (!flag)
        *l_file = "";

    if (checkdomain ("brest.by", sender) || checkdomain("bresttelecom.by", sender))
        docmd (sender, h_subject, l_file);
    else {
        error ("������������ %s �� �������� ��������� ����������� ����� ���� ������", sender);

        if (access (DATALIEN, 4)) {
            error ("���� %s ����������", DATALIEN);
            quit ();
        } else
            fcat (DATALIEN);
    }
}

int main (argc, argv)
int argc;
char **argv;
{
    FILE *fd;
    char *s;
    long replysz;

    if (argc > 2) {
        fprintf (stderr, "usage: %s [config-file]\n", argv [0]);
        exit (-1);
    }
    if (! config (argv [1])) {
        fprintf (stderr, "cannot read config file\n");
        exit (-1);
    }

    /* catch signals */
    sigcatch ();

    /* make temp file name */
    mktemp (tmpf);

    /* enter public directory */
    if (chdir (PUBLICDIR) < 0) {
        error ("�� ���� ����� � ������� %s", PUBLICDIR);
        quit ();
    }

    /* open temp file on stdout */
    if (! freopen (tmpf, "w", stdout)) {
        error ("�� ���� ����������� stdout � %s", tmpf);
        quit ();
    }
    fclose (stderr);        /* no stderr */

    /* scan header and find 'From' field */
    scanheader (stdin);
    if (h_reply_to)
        sender = strlower(getsendername (h_reply_to));
    else if (h_resent_from)
        sender = strlower(getsendername (h_resent_from));
    else if (h_from)
        sender = strlower(getsendername (h_from));
    else if (h_sender)
        sender = strlower(getsendername (h_sender));
    else {
        error ("�� ���� ���������� ����� �����������");
        quit ();
    }

    for (s = sender; *s && *s != '@'; ++s);
    if (*s == '@')
        strlower (s + 1);

    /* check if this mail is from uucp */
    if (! strncmp (sender, "uucp@", 5) || ! strncmp (sender, "MAILER-DAEMON", 13) || ! strcmp (sender, MYADDRESS)) {
        fd = f2open (SERVDIR, "junkfile", "a");
        if (! fd) {
            error ("�� ���� ������� %s/junkfile", SERVDIR);
            quit ();
        }
        fprintf (fd, "\nFrom %s\n\n", sender);
        ffcopy (stdin, fd);
        fclose (fd);
        error ("��������� ����������� %s ���������", sender);
        return (0);
    }

    /* print version etc. */
    //message("� ������� ���� 2004 ���� �������������� ��������� ����������� ���� ���");
    //message("� ����� � ������������� �� ������ �����  10-����� ���������� ������ ��"); 
    //message("��ޣ����.   ���   ���������   �����������,   ������������  �������   �"); 
    //message("��� ������ 2004 ����, ���������� ������� ������� 5/2...12/2, 1/2...4/2");
    //message("����������� �����  �������  �� ���� ����� ����� �������.  ���� �������"); 
    //message("��������   ��   ��������������   ��������   �����������,  ��  ��������");
    //message("������������ ��� �� ���� ��� � �����.");
    //puts ("\n");
    message (VERSION);
    message (COPYRIGHT);
    puts ("\n");

    /* read and execute commands */
    //if (! checkpermissions (sender, SERVDIR, "users")) {
    //    printf ("Permission denied\n");
    //    error ("������ ������������ %s ��������", sender);
    //} else if (! checkpermissions (h_from_, SERVDIR, "paths")) {
    //    printf ("Permission denied\n");
    //    error ("������ ������������ � ������� ������ %s ��������", h_from_);
    //}

    fd = fopen ("/dev/null", "w");
    if (! fd) {
        error ("�� ���� ������� /dev/null �� ������");
        quit ();
    }

    ffcopy (stdin, fd);
    fclose (fd);

    procsender (sender);

    fclose (stdout);
    replysz = filesize (tmpf);
    fd = fopen (tmpf, "r");
    unlink (tmpf);

    if (! fd) {
        error ("�� ���� ����������� %s", tmpf);
        quit ();
    }

    replyto (sender, fd, "������ ���������", 0);
    log (LOGFILE, SERVER, "�������� ��������� ������������ %s ������ %ld ����", sender, replysz);
    return (0);
}
