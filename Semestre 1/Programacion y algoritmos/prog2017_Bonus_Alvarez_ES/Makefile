CC=gcc
CFLAGS=-c
LFLAGS=-o
EXEC=main
CPPS:=$(wildcard *.c)
OBJS:=$(patsubst %.c, %.o, $(CPPS))

$(EXEC): $(OBJS)
	$(CC) $(LFLAGS) $@ $(OBJS)

$(OBJS): $(CPPS)
	$(CC) $(CFLAGS) $<

release:
	$(MAKE) CFLAGS="-std=c99 -O2 -D NDEBUG -c" LFLAGS="-std=c99 -O2 -o"

debug:
	$(MAKE) CFLAGS="-std=c99 -g -c" LFLAGS="-std=c99 -g -o"

clean:
	rm -f $(EXEC) $(OBJS)