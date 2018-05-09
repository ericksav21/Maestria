CPP=gcc
CFLAGS=-w -c
LFLAGS=
EXEC=main
CPPS:=$(wildcard *.c)
OBJS:=$(patsubst %.c,%.o,$(CPPS))
OBJDIR:=obj
DIROBJS:=$(addprefix $(OBJDIR)/,$(OBJS))

$(EXEC): $(DIROBJS)
	$(CPP) $(LFLAGS) -o $@ $(DIROBJS) -lm

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CPP) $(CFLAGS) $< -o $@

$(OBJDIR):
	mkdir -p $@

debug:
	$(MAKE) CFLAGS="-g -w -c" LFLAGS="-g"

release:
	$(MAKE) CFLAGS="-O2 -w -c" LFLAGS="-O2"

clean:
	rm -f $(EXEC) $(DIROBJS) f_eval.txt g_norm.txt result.txt

help:
	@echo 'Opciones de compilación:'
	@echo 'Comando: make - Compila normalmente, genera un ejecutable llamado main y sus archivos objeto en la carpeta obj.'
	@echo 'Comando: make release - Compila de manera optimizada.'
	@echo 'Comando: make debug - Compila en modo debug.'
	@echo 'Comando: make clean - Limpia todos los archivos generados por la compilación incluyendo el ejecutable.'
