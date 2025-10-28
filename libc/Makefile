.POSIX:
.SUFFIXES: .c .s

TARGET = x86_64
CFLAGS = -g -Iinclude -fno-stack-protector -nostdinc
BIN = gensyscalls
LIB = libc.a

GEN = arch/$(TARGET)/syscalls.s
OBJS = arch/$(TARGET)/syscalls.o src/libc_start.o
CRT = arch/$(TARGET)/crti.o arch/$(TARGET)/crtn.o arch/$(TARGET)/start.o

all: $(GEN) $(LIB) $(CRT)

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

.s.o:
	@echo "  AS $<"
	@$(AS) -c $< -o $@

.c.o:
	@echo "  CC $<"
	@$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(BIN) $(LIB) $(GEN) $(OBJS) $(CRT)

.PHONY: all clean
