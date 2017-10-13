CC=gcc
CFLAGS=-g -c
LFLAGS=-g -o
EXEC=main
CPPS:=$(wildcard *.c)
OBJS:=$(patsubst %.c, %.o, $(CPPS))

$(EXEC): $(OBJS) imagen.h
	$(CC) $(LFLAGS) $@ $(OBJS) -lm

*.o: $(CPPS)
	$(CC) $(CFLAGS) $<

clean:
	rm -f $(EXEC) $(OBJS)