CC=gcc
CFLAGS=-g -c
LFLAGS=-g -o
EXEC=main
CPPS:=$(wildcard *.c)
OBJS:=$(patsubst %.c, %.o, $(CPPS))

$(EXEC): $(OBJS) funciones_matriz.h
	$(CC) $(LFLAGS) $@ $(OBJS) -lm

$(OBJS): funciones_matriz.h
	$(CC) $(CFLAGS) $(CPPS)

clean:
	rm -f $(EXEC) $(OBJS)