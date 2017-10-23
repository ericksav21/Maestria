CPP=g++
CFLAGS=
LFLAGS=-Wall -c
EXEC=main
CPPS:=$(wildcard *.cpp)
OBJS:=$(patsubst %.cpp,%.o,$(CPPS))
OBJDIR:=obj
DIROBJS:=$(addprefix $(OBJDIR)/,$(OBJS))

$(EXEC): $(DIROBJS)
	@echo @a

clean:
	rm -f main *.o
