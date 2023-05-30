CC := gcc
CFLAGS := -Wall -Wextra -pthread

SRCDIR := src
BINDIR := bin

# List of source files
SOT_BARRIER_SRC := $(SRCDIR)/sot_barrier/sot_barrier.c
BARRIER_TEST_SRC := $(SRCDIR)/testing/barrier.c
VECTOR_TEST_SRC := $(SRCDIR)/testing/vector.c
VECTOR_UTIL_SRC := $(SRCDIR)/vector_utils/vector.c
COUNTDOWN_SRC := $(SRCDIR)/countdown/countdown.c
COUNTDOWN_TEST_SRC := $(SRCDIR)/testing/countdown.c

# Executable targets
BARRIER_TEST_TARGET := $(BINDIR)/barrier
VECTOR_TEST_TARGET := $(BINDIR)/vector
COUNTDOWN_TEST_TARGET := $(BINDIR)/countdown

# Build rules
all: barrier_test vector_test countdown_test

barrier_test: $(BARRIER_TEST_TARGET)

$(BARRIER_TEST_TARGET): $(BARRIER_TEST_SRC) $(SOT_BARRIER_SRC)
	$(CC) $(CFLAGS) -o $@ $^

vector_test: $(VECTOR_TEST_TARGET)

$(VECTOR_TEST_TARGET): $(VECTOR_TEST_SRC) $(SOT_BARRIER_SRC) $(VECTOR_UTIL_SRC)
	$(CC) $(CFLAGS) -o $@ $^

countdown_test: $(COUNTDOWN_TEST_TARGET) $(SOT_BARRIER_SRC) $(COUNTDOWN_SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(BARRIER_TEST_TARGET) $(VECTOR_TEST_TARGET) $(COUNTDOWN_TEST_TARGET)

.PHONY: all clean
