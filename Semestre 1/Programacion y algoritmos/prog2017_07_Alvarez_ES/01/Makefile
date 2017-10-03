CC=gcc
CFLAGS=-g -c
LFLAGS=-g -o
EXEC=main
CPPS:=$(wildcard *.c)
OBJS:=$(patsubst %.c, %.o, $(CPPS))

$(EXEC): $(OBJS) impares.h
	$(CC) $(LFLAGS) $@ $(OBJS)

$(OBJS):
	$(CC) $(CFLAGS) $(CPPS)

clean:
	rm -f $(EXEC) $(OBJS)