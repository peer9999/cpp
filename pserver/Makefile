OSFLAGS         = -O
LIBS            =
CC              = gcc

SHELL           = /bin/sh
DEST            = /root/install/source/pstat
LDFLAGS         =
CFLAGS          = $(OSFLAGS)
LD              = $(CC)

DOBJS           = daemon.o ut.o configure.o
DSRCS           = daemon.c ut.c configure.c

SOBJS           = server.o ut.o configure.o header.o
SSRCS           = server.c ut.c configure.c header.c

POBJS           = psend.o ut.o configure.o
PSRCS           = psend.c ut.c configure.c

ALL             = daemon server psend

ALLLINT         = daemon.ln server.ln psend.ln

all:    $(ALL)

lint:   $(ALLLINT)

server: $(SOBJS)
	$(LD) $(LDFLAGS) $(SOBJS) $(LIBS) -o server

daemon: $(DOBJS)
	$(LD) $(LDFLAGS) $(DOBJS) $(LIBS) -o daemon

psend:  $(POBJS)
	$(LD) $(LDFLAGS) $(POBJS) $(LIBS) -o psend

clean:
	rm -f *.o *.b .,* core a.out lint $(ALL) $(ALLLINT)

install: $(DEST)/bin/server $(DEST)/bin/mailservd

$(DEST)/bin/server: server
	-mv -f $(DEST)/bin/server $(DEST)/bin/server~
	cp server $(DEST)/bin
	strip $(DEST)/bin/server
	chmod 775 $(DEST)/bin/server

$(DEST)/bin/mailservd: daemon
	-mv -f $(DEST)/bin/mailservd $(DEST)/bin/mailservd~
	cp daemon $(DEST)/bin/mailservd
	strip $(DEST)/bin/mailservd
	chown mis $(DEST)/bin/mailservd
	chmod 4775 $(DEST)/bin/mailservd

daemon.ln: $(DSRCS)
	lint $(OSFLAGS) $(DSRCS) > daemon.ln

server.ln: $(SSRCS)
	lint $(OSFLAGS) $(SSRCS) > server.ln

psend.ln: $(PSRCS)
	lint $(OSFLAGS) $(PSRCS) > psend.ln

###
configure.o: config.h
daemon.o: config.h
psend.o: config.h server.h
header.o: header.h
server.o: config.h header.h server.h
