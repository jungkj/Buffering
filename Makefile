CC=gcc
CFLAGS=-g -Wall --std=c99

SRCS1 = print_file.c
DEPS1 = 
OBJS1 = $(patsubst %.c,%.o,$(SRCS1))
CMDS1 = $(basename $(SRCS1))

SRCS2 = buf_io.c buf_print_file.c 
DEPS2 = buf_io.h
OBJS2 = $(patsubst %.c,%.o,$(SRCS2))
CMDS2 = buf_print_file

.PHONY: all
all: $(CMDS1) $(CMDS2)

$(OBJS1): %.o: %.c $(DEPS1)
	$(CC) $(CFLAGS) -c -o $@ $<

$(CMDS1): %: $(OBJS1)
	$(CC) $(CFLAGS) -o $@ $(OBJS1)

$(OBJS2): %.o: %.c $(DEPS2)
	$(CC) $(CFLAGS) -c -o $@ $<

$(CMDS2): %: $(OBJS2)
	$(CC) $(CFLAGS) -o $@ $(OBJS2)

.PHONY: clean
clean:
	/bin/rm -f $(CMDS1) $(OBJS1) $(CMDS2) $(OBJS2)
