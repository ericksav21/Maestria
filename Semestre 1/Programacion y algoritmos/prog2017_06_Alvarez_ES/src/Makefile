CC=gcc
CFLAGS=-c
LFLAGS=-o
EXEC=main
CPPS:=$(wildcard ∗.c)
OBJS:=$(patsubst %.c,%.o,$(CPPS))
OBJDIR:=../obj
DIROBJS:=$(addprefix $(OBJDIR)/,$(OBJS))
BINDIR:=bin
DIRBINS:=$(addprefix $(BINDIR)/,$(OBJS))
$(EXEC): *.c $(DIROBJS)
	$(CC) $(CFLAGS) $< $(DIROBJS)