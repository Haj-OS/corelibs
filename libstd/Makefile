.POSIX:
.SUFFIXES: .c

# needed for libc wiring
TARGET = x86_64
PREFIX = /usr/local
CFLAGS = -g -Iinclude -fno-stack-protector -I../libc/include -nostdinc
TEST_BIN = test
LIB = libstd.a

OBJS = src/vec.o 

all: $(LIB) $(TEST_BIN)

$(LIB): $(OBJS)
	@echo "  AR $@"
	@$(AR) rcs $@ $(OBJS)

$(TEST_BIN): $(LIB) test.o
	@echo "  CC $@"
	@$(CC) $(CFLAGS) -static -nostdlib -nostartfiles test.c $(LIB) \
		../libc/arch/$(TARGET)/start.o ../libc/libc.a -o $@

.c.o:
	@echo "  CC $<"
	@$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(LIB) $(OBJS) $(TEST_BIN)

INLIB = $(DESTDIR)$(PREFIX)/lib
ININC = $(DESTDIR)$(PREFIX)/include/std

install: all
	install -d $(INLIB)
	install -d $(ININC)
	install -m 755 $(LIB) $(INLIB)/$(LIB)
	cp -rv include/* $(ININC)

.PHONY: all clean install
