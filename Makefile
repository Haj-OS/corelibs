.POSIX:
# CFG
TARGET = x86_64
CC = cc
AS = as
AR = ar
PREFIX = /usr/local

PROJS = libc libstd hajmk 

all: $(PROJS)

$(PROJS):
	$(MAKE) -C $@ all

clean:
	@./scripts/clean.sh "$(MAKE)" "$(PROJS)"

install:
	@./scripts/install.sh "$(MAKE)" "$(DESTDIR)" "$(PREFIX)" "$(PROJS)"

.PHONY: all clean $(PROJS)
