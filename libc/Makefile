.POSIX:
.SUFFIXES: .c .s

TARGET = x86_64
CFLAGS = -g -Iinclude -fno-stack-protector -nostdinc
BIN = gensyscalls
TEST_BIN = test
LIB = libc.a

GEN = arch/$(TARGET)/syscalls.s
OBJS = arch/$(TARGET)/syscalls.o src/libc_start.o src/errno.o
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

$(TEST_BIN): $(LIB)
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

.PHONY: all clean
