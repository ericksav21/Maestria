CC=gcc
CFLAGS=-c
LFLAGS=-o
EXEC=main
CPPS:=$(wildcard *.c)
OBJDIR:=../obj
OBJS:=$(patsubst %.c,%.o,$(CPPS))
DIROBJS:=$(addprefix $(OBJDIR)/,$(OBJS))
BINDIR:=../bin
DIRBINS:=$(addprefix $(BINDIR)/,$(EXEC))
$(DIRBINS): $(OBJS)
	$(CC) $(LFLAGS) $@ $(OBJS) -lm
	mv $(OBJS) $(OBJDIR)/

$(DIROBJS):
	$(CC) $(CFLAGS) $(CPPS) -o $@