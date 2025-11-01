.POSIX:
.SUFFIXES: .c .s

TARGET = x86_64
PREFIX = /usr/local
CFLAGS = -g -Iinclude -fno-stack-protector -nostdinc \
		 -Wno-builtin-declaration-mismatch
BIN = gensyscalls
TEST_BIN = test
LIB = libc.a

GEN = arch/$(TARGET)/syscalls.s
OBJS = arch/$(TARGET)/syscalls.o src/libc_start.o src/errno.o src/stdio.o \
	   src/stdalign.o src/alloc.o src/string.o src/alloc/buffer.o
CRT = arch/$(TARGET)/crti.o arch/$(TARGET)/crtn.o arch/$(TARGET)/start.o

all: $(GEN) $(LIB) $(CRT) $(TEST_BIN)

$(LIB): $(OBJS)
	@echo "  AR $@"
	@$(AR) rcs $@ $(OBJS)

$(GEN): $(BIN)
	@cp arch/$(TARGET)/syscalls.s.in $@
	@echo "  GENSYSCALLS $(TARGET)"
	@./$(BIN) $(TARGET)

$(BIN):
	@echo "  CC $@"
	@$(CC) $@.c -o $@

$(TEST_BIN): $(LIB) test.o
	@echo "  CC $@"
	@$(CC) $(CFLAGS) -static -nostdlib -nostartfiles test.c $(CRT) $(LIB) -o $@

.s.o:
	@echo "  AS $<"
	@$(AS) -c $< -o $@

.c.o:
	@echo "  CC $<"
	@$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(BIN) $(LIB) $(GEN) $(OBJS) $(CRT) $(TEST_BIN)

INLIB = $(DESTDIR)$(PREFIX)/lib
ININC = $(DESTDIR)$(PREFIX)/include

install: all
	install -d $(INLIB)
	install -d $(ININC)
	install -m 755 $(LIB) $(INLIB)/$(LIB)
	install -m 644 arch/$(TARGET)/start.o $(INLIB)/crt1.o
	install -m 644 arch/$(TARGET)/crtn.o $(INLIB)/crtn.o
	install -m 644 arch/$(TARGET)/crti.o $(INLIB)/crti.o
	cp -rv include/* $(ININC)

.PHONY: all clean install
