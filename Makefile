CC := clang
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
THREAD_POOL_SRC := $(SRCDIR)/thread_pool/pool.c
THREAD_POOL_TEST_SRC := $(SRCDIR)/testing/pool.c

# Object files
SOT_BARRIER_OBJ := $(BINDIR)/sot_barrier.o
BARRIER_TEST_OBJ := $(BINDIR)/barrier_test.o
VECTOR_TEST_OBJ := $(BINDIR)/vector_test.o
VECTOR_UTIL_OBJ := $(BINDIR)/vector_util.o
COUNTDOWN_OBJ := $(BINDIR)/countdown.o
COUNTDOWN_TEST_OBJ := $(BINDIR)/countdown_test.o
THREAD_POOL_OBJ := $(BINDIR)/thread_pool.o
THREAD_POOL_TEST_OBJ := $(BINDIR)/thread_pool_test.o

# Executable targets
BARRIER_TEST_TARGET := $(BINDIR)/barrier_test
VECTOR_TEST_TARGET := $(BINDIR)/vector_test
COUNTDOWN_TEST_TARGET := $(BINDIR)/countdown_test
THREAD_POOL_TEST_TARGET := $(BINDIR)/thread_pool_test

# Build rules
all: barrier_test vector_test countdown_test thread_pool_test

barrier_test: $(BARRIER_TEST_TARGET)

$(BARRIER_TEST_TARGET): $(BARRIER_TEST_OBJ) $(SOT_BARRIER_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

vector_test: $(VECTOR_TEST_TARGET)

$(VECTOR_TEST_TARGET): $(VECTOR_TEST_OBJ) $(SOT_BARRIER_OBJ) $(VECTOR_UTIL_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

countdown_test: $(COUNTDOWN_TEST_TARGET)

$(COUNTDOWN_TEST_TARGET): $(COUNTDOWN_TEST_OBJ) $(SOT_BARRIER_OBJ) $(COUNTDOWN_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

thread_pool_test: $(THREAD_POOL_TEST_TARGET)

$(THREAD_POOL_TEST_TARGET): $(THREAD_POOL_TEST_OBJ) $(THREAD_POOL_OBJ) $(SOT_BARRIER_OBJ)
	$(CC) $(CFLAGS) -o $@ $^


$(SOT_BARRIER_OBJ): $(SOT_BARRIER_SRC)
	$(CC) $(CFLAGS) -c -o $@ $<
	
$(BARRIER_TEST_OBJ): $(BARRIER_TEST_SRC)
	$(CC) $(CFLAGS) -c -o $@ $<

$(VECTOR_TEST_OBJ): $(VECTOR_TEST_SRC)
	$(CC) $(CFLAGS) -c -o $@ $<

$(VECTOR_UTIL_OBJ): $(VECTOR_UTIL_SRC)
	$(CC) $(CFLAGS) -c -o $@ $<

$(COUNTDOWN_OBJ): $(COUNTDOWN_SRC)
	$(CC) $(CFLAGS) -c -o $@ $<

$(COUNTDOWN_TEST_OBJ): $(COUNTDOWN_TEST_SRC)
	$(CC) $(CFLAGS) -c -o $@ $<

$(THREAD_POOL_OBJ): $(THREAD_POOL_SRC)
	$(CC) $(CFLAGS) -c -o $@ $<

$(THREAD_POOL_TEST_OBJ): $(THREAD_POOL_TEST_SRC)
	$(CC) $(CFLAGS) -c -o $@ $<

clean_obj:
	rm -f $(SOT_BARRIER_OBJ) $(BARRIER_TEST_OBJ) $(VECTOR_TEST_OBJ) $(VECTOR_UTIL_OBJ) $(COUNTDOWN_OBJ) $(COUNTDOWN_TEST_OBJ) $(THREAD_POOL_OBJ) $(THREAD_POOL_TEST_OBJ)
clean:
	rm -f $(BARRIER_TEST_TARGET) $(VECTOR_TEST_TARGET) $(COUNTDOWN_TEST_TARGET) $(THREAD_POOL_TEST_TARGET)
	rm -f $(SOT_BARRIER_OBJ) $(BARRIER_TEST_OBJ) $(VECTOR_TEST_OBJ) $(VECTOR_UTIL_OBJ) $(COUNTDOWN_OBJ) $(COUNTDOWN_TEST_OBJ) $(THREAD_POOL_OBJ) $(THREAD_POOL_TEST_OBJ)

.PHONY: all clean
