CC = gcc
CFLAGS = -Wall -Werror
SRCDIR = ../../src
BINDIR = ../../bin

SOURCES_SUM = $(SRCDIR)/matrix/matrix-threads-sum.c \
                     $(SRCDIR)/matrix/matrix.c

SOURCES_MUL = $(SRCDIR)/matrix/matrix-threads-mul.c \
                     $(SRCDIR)/matrix/matrix.c

SOURCES_SEQ = $(SRCDIR)/matrix/matrix-seq.c \
                     $(SRCDIR)/matrix/matrix.c

all: $(BINDIR)/matrix-threads-sum $(BINDIR)/matrix-threads-mul $(BINDIR)/matrix-seq

$(BINDIR)/matrix-threads-sum: $(SOURCES_SUM)
	$(CC) $(CFLAGS) -o $@ $^ -pthread

$(BINDIR)/matrix-threads-mul: $(SOURCES_MUL)
	$(CC) $(CFLAGS) -o $@ $^ -pthread

$(BINDIR)/matrix-seq: $(SOURCES_SEQ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(BINDIR)/matrix-threads-sum $(BINDIR)/matrix-threads-mul $(BINDIR)/matrix-seq
