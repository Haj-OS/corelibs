.POSIX:
.SUFFIXES: .c

# needed for libc wiring
TARGET = x86_64
CFLAGS = -g -Iinclude -I../libc/include -nostdinc
TEST_BIN = test
LIB = libstd.a

OBJS = src/vec.o 

all: $(LIB) $(TEST_BIN)

$(LIB): $(OBJS)
	@echo "  AR $@"
	@$(AR) rcs $@ $(OBJS)

$(TEST_BIN): $(LIB)
	@echo "  CC $@"
	@$(CC) $(CFLAGS) -static -nostdlib -nostartfiles test.c $(LIB) \
		../libc/arch/$(TARGET)/start.o ../libc/libc.a -o $@

.c.o:
	@echo "  CC $<"
	@$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(LIB) $(OBJS) $(TEST_BIN)

.PHONY: all clean
