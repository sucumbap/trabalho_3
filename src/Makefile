CC = gcc
CFLAGS = -Wall -Werror
SRCDIR = ../../src
BINDIR = ../../bin

SOURCES = $(SRCDIR)/server_tcp/server.c $(SRCDIR)/server_tcp/server.h \
				 $(SRCDIR)/server_utils/utils.c $(SRCDIR)/server_utils/utils.h

all: $(BINDIR)/server_tcp

$(BINDIR)/server_tcp: $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $(SRCDIR)/server_tcp/server.c $(SRCDIR)/server_utils/utils.c

clean:
	rm -f $(BINDIR)/server_tcp
