/*
 *      psend 2.0 27.01.99
 *      Copyright (C) 1995-98 Ruslan Shevelinski
 */

#include <stdio.h>
#include <fcntl.h>
#include "config.h"
#include "server.h"
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>

#define VERSION        "�������� ������ �������������� ������� PhoneStat (C), ������ 2.0"
#define COPYRIGHT      "Copyright (c) 1995-2004, Ruslan Shevelinski, BELPAK"

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
    /* unlink (tmpf); */
    exit (-1);
}

/*
 * Output error message to log file.
 * VARARGS1
 */

void error (s, a, b, c, d)
char *s, *a, *b, *c, *d;
{

    log (LOGFILE, PSEND, s, a, b, c, d);
}

/*
 * Print error message.
 * VARARGS1
 */

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
        } else
            fprintf (fd, "Subject: [PhoneStat] %s\n", smessage);

        fprintf (fd, "\n");
        //fprintf (fd, "%s\n", "� ������� ���� 2004 ���� �������������� ��������� ����������� ���� ���");
        //fprintf (fd, "%s\n", "� ����� � ������������� �� ������ �����  10-����� ���������� ������ ��"); 
        //fprintf (fd, "%s\n", "��ޣ����.   ���   ���������   �����������,   ������������  �������   �"); 
        //fprintf (fd, "%s\n", "��� ������ 2004 ����, ���������� ������� ������� 5/2...12/2, 1/2...4/2");
        //fprintf (fd, "%s\n", "����������� ����� ������� �� ���� ����� �����  �������.  ����  �������"); 
        //fprintf (fd, "%s\n", "��������  ��  ��������������   ��������   �����������,   ��   ��������");
        //fprintf (fd, "%s\n\n", "������������ ��� �� ���� ��� � �����.");
        fprintf (fd, "%s\n", VERSION);
        fprintf (fd, "%s\n\n\n", COPYRIGHT);

        do {
            if (koi)
                recoder (buf);
            fputs (buf, fd);
            if (ftell (from) - cont > 1024 * 1024L + 10240) {
                fprintf (fd, "\n---- ����������� � ��������� ������ -------------------------------------------\n");
                break;
            }
        } while (fgets (buf, 512, from));

        putc ('\n', fd);
        pclose (fd);
        sleep(3);
        cont = ftell (from);
    }
}

/* ���������, ������ �� ������ abc.domain � ����� domain */

int checkdomain (domain, address)
char *domain, *address;
{
    char *p1, *p2;

    if (! strlen (domain))
        return 0;
    if (! strlen (address))
        return 0;

    p1 = domain + strlen (domain) - 1;
    p2 = address + strlen (address) - 1;

    while (1) {
        if (*p1 != *p2)
            return 0;
        if (p1 == domain) {
            if (p2 == address)
                return 1;
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
    char name [128], name1[128], name2[128], dirname[128];

    strcpy (smessage, "�������������� ���������");

    sprintf (name, "%s/%s/subject", PUBLICDIR, dir);
    fd = fopen (name, "r");

    if (!fd)
        error ("��� ������� � ���������� ����� %s/%s/subject", PUBLICDIR, dir);
    else {
        if (! fgets (smessage, 128, fd))
            error ("�� ���� ��������� ��������� ���� %s/%s/subject", PUBLICDIR, dir);
        else
            recoder (smessage);
        fclose (fd);
    }

    sprintf (name1, "%s/%s/%s", PUBLICDIR, dir, file);
    fd1 = fopen (name1, "r");

    sprintf (dirname, "%s/%s/", PUBLICDIR, dir);
    fddir = opendir (dirname);
    sprintf (name2, "%s/%s/%s", PUBLICDIR, dir, sender);
    while ((dirbuf = readdir (fddir)) != NULL ) {
        if (strcasecmp(dirbuf->d_name, sender) == 0){
            sprintf (name2, "%s/%s/%s", PUBLICDIR, dir, dirbuf->d_name);
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

/* �������� �� ������� ���������� */
/* ��������� ���������� � ������ 3.0 */

void procsender (sender, dir)
char *sender, *dir;
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

    if (checkdomain ("brest.by", sender))
        dodata (sender, dir, l_file);
    else {
        error ("������������ %s �� �������� ��������� ����������� ����� ���� ������", sender);
        if (access (DATALIEN, 4)) {
            error ("���� %s ����������", DATALIEN);
            quit ();
        } else
            fcat (DATALIEN);
    }
}


int main (ac, av)
int ac;
char **av;
{
    char name [100];
    int fd;
    long replysz;
    FILE *fp;
    struct subsrec s;

    if (ac > 3 || ac < 2) {
        fprintf (stderr, "usage: %s [period] [config-file]\n", av [0]);
        exit (-1);
    }

    if (! config (av[2])) {
        fprintf (stderr, "cannot read config file\n");
        exit (-1);
    }

    sprintf (name, "%s/subscribe", SERVDIR);

    fd = open (name, O_RDONLY);
    if (fd < 0) {
        error ("�� ���� ������� %s\n", name);
        exit (-1);
    }

    error ("����� ������������");
    while (1) {
        if (read (fd, &s, sizeof(s)) != sizeof(s))
            break;
        if (s.status)
            procsender (s.domain, av[1]);
    }
    error ("������� ������������");
}
