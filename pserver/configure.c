#include <stdio.h>

#define INITCONFIG
#include "config.h"

extern char *strlower (), *strcopy ();
extern int strcmp (), atoi (), getstr ();

static void setvalue (var, value)
char *var, *value;
{
    int i;

    var = strlower (var);
    for (i = 0; inttable[i].name; ++i)
        if (! strcmp (var, inttable[i].name))
            *inttable[i].value = atoi (value);
    for (i = 0; strtable[i].name; ++i)
        if (! strcmp (var, strtable[i].name))
            *strtable[i].value = strcopy (value);
}

/*
 * Read config file.
 * Lines must hahe syntax "name = value".
 * Empty lines and lines beginning with # are ignored.
 */

int config (name)
char *name;
{
    FILE *fd;
    char line [512];
    char *var, *value;

    if (name)
        CONFIGFILE = name;
    fd = fopen (CONFIGFILE, "r");
    if (! fd)
        return (0);
    while (getstr (fd, line)) {
        var = line;
        while (*var == ' ' || *var == '\t')
            ++var;
        if (*var == 0 || *var == '#')
            continue;
        value = var;
        while (*value && *value != ' ' && *value != '\t' && *value != '=')
            ++value;
        if (! *value)
            continue;
        *value++ = 0;
        while (*value == ' ' || *value == '\t')
            ++value;
        if (*value != '=')
            continue;
        ++value;
        while (*value == ' ' || *value == '\t')
            ++value;
        setvalue (var, value);
    }
    fclose (fd);
    return (1);
}
