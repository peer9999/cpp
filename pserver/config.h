#define SERVER         "s"
#define DAEMON         "s"
#define LOGMSG         "l"
#define UPDATA         "u"
#define MERROR         "e"
#define SNDATA         "d"
#define REGISTR        "r"
#define PSEND          "p"

extern char *MAILBOX, *SERVDIR, *PUBLICDIR, *MAILTOCMD, *LOGFILE,
            *MYADDRESS, *CONFIGFILE, *DATAMNG, *DATARCV, *DATASUB,
            *DATAREG, *DATALIEN, *STATMSG, *ADMINISTRATOR, *STATFILE;

extern int DAEMONDELAY;

#ifdef INITCONFIG

char *CONFIGFILE        = "/usr/local/etc/pstat.conf";

char *SERVDIR           = "/var/spool/pstat";
char *PUBLICDIR         = "/var/spool/samba/phonestat";
char *LOGFILE           = "/var/log/pstat/pstat-log";
char *STATFILE          = "/var/log/pstat/pstat-stat";

char *DATAMNG           = "/disk1/pstat/manager";
char *DATARCV           = "/var/spool/samba/phonestat/conf/access";
char *DATASUB           = "/var/spool/samba/phonestat/conf/registr";
char *DATAREG           = "/var/spool/pstat/message";
char *DATALIEN          = "/var/spool/pstat/alien";
char *STATMSG           = "subject";

char *MAILBOX           = "/var/mail/pstat";
char *MAILTOCMD         = "/usr/sbin/sendmail";
char *MYADDRESS         = "pstat@brest.by";
char *ADMINISTRATOR     = "admin@brest.beltelecom.by";

int DAEMONDELAY         = 60;           /* seconds */

struct {
    char *name;
    int *value;
} inttable [] = {
    "daemondelay",          &DAEMONDELAY,
    0,                      0,
};

struct {
    char *name;
    char **value;
} strtable [] = {
    "log",                  &LOGFILE,
    "mailbox",              &MAILBOX,
    "mailtocmd",            &MAILTOCMD,
    "myaddress",            &MYADDRESS,
    "publicdir",            &PUBLICDIR,
    "servdir",              &SERVDIR,
    "statfile",             &STATFILE,
    "datamng",              &DATAMNG,
    "datarcv",              &DATARCV,
    "datasub",              &DATASUB,
    "datareg",              &DATAREG,
    "statmsg",              &STATMSG,
    "administrator",        &ADMINISTRATOR,
    0,                      0,
};

#endif /* INITCONFIG */
