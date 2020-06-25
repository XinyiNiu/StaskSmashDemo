CFILES := $(wildcard *.c)
PROGS := $(patsubst %.c,%,$(CFILES))
CFLAGS := -m32 -ggdb -static -fno-stack-protector -z execstack
CC := gcc

all: $(PROGS)
	@echo $(PROGS)

clean:
	rm -f $(PROGS)

stack: stack.c
	sudo $(CC) -o $@ $(CFLAGS) $<

