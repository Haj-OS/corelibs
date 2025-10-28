.POSIX:
# CFG
TARGET = x86_64
CC = cc
AS = as
AR = ar

PROJS = libc

all: $(PROJS)

$(PROJS):
	$(MAKE) -C $@ all

clean:
	@./scripts/clean.sh "$(MAKE)" "$(PROJS)"

.PHONY: all clean $(PROJS)
