CPP=g++
CFLAGS=-std=c++11 -w -c
LFLAGS=-std=c++11
EXEC=main
CPPS:=$(wildcard *.cpp)
OBJS:=$(patsubst %.cpp,%.o,$(CPPS))
OBJDIR:=obj
DIROBJS:=$(addprefix $(OBJDIR)/,$(OBJS))

$(EXEC): $(DIROBJS)
	$(CPP) $(LFLAGS) -o $@ $(DIROBJS)

$(OBJDIR)/%.o: %.cpp
	$(CPP) $(CFLAGS) $< -o $@

debug:
	$(MAKE) CFLAGS="-g -std=c++11 -w -c" LFLAGS="-g -std=c++11"

release:
	$(MAKE) CFLAGS="-O2 -std=c++11 -w -c" LFLAGS="-O2 -std=c++11"

clean:
	rm -f $(EXEC) $(DIROBJS)
