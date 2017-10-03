CC=gcc
CFLAGS=-g -c
LFLAGS=-g -o
EXEC=main
CPPS:=$(wildcard *.c)
OBJS:=$(patsubst %.c, %.o, $(CPPS))

$(EXEC): $(OBJS) newton.h
	$(CC) $(LFLAGS) $@ $(OBJS) -lm

$(OBJS):
	$(CC) $(CFLAGS) $(CPPS)

clean:
	rm -f $(EXEC) $(OBJS)