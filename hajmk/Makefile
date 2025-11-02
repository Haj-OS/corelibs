.POSIX:
.SUFFIXES: .c

# needed for libc wiring
TARGET = x86_64
PREFIX = /usr/local
CFLAGS = -g -Iinclude -fno-stack-protector -I../libc/include \
		 -I../libstd/include -nostdinc

LIB = libbuild.a

OBJS = 

all: $(LIB)

$(LIB): $(OBJS)
	@echo "  AR $@"
	@$(AR) rcs $@ $(OBJS)

.c.o:
	@echo "  CC $<"
	@$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(LIB) $(OBJS)

INBIN = $(DESTDIR)$(PREFIX)/bin
INLIB = $(DESTDIR)$(PREFIX)/lib
ININC = $(DESTDIR)$(PREFIX)/include

install: all
	install -d $(INLIB)
	install -d $(ININC)
	install -d $(INBIN)
	install -m 755 bin/hajmk $(INBIN)/hajmk
	install -m 755 $(LIB) $(INLIB)/$(LIB)
	cp -rv include/* $(ININC)

.PHONY: all clean install
