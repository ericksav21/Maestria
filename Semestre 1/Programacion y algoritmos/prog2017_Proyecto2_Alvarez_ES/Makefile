CPP=g++
CFLAGS=-w -c -std=c++11
LFLAGS=-std=c++11
EXEC=main
IMGDIR:=data
CPPS:=$(wildcard *.cpp)
OBJS:=$(patsubst %.cpp,%.o,$(CPPS))
IMGS:=$(wildcard $(IMGDIR)/*.pgm)
OBJDIR:=obj
OUTPUTDIR:=out
DIROBJS:=$(addprefix $(OBJDIR)/,$(OBJS))
DIRIMGS:=$(IMGS:$(IMGDIR)/%=%)

$(EXEC): $(DIROBJS) | $(OUTPUTDIR)
	$(CPP) $(LFLAGS) -o $@ $(DIROBJS) -lcairo -lm

$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CPP) $(CFLAGS) $< -o $@

$(OBJDIR):
	mkdir -p $@

$(OUTPUTDIR):
	mkdir -p $@

debug:
	$(MAKE) CFLAGS="-g -std=c++11 -w -c" LFLAGS="-g -std=c++11"

release:
	$(MAKE) CFLAGS="-O2 -std=c++11 -w -c" LFLAGS="-O2 -std=c++11"

run1:
	rm -f out/*.png
	sh runner.sh '1'

run2:
	rm -f out/*.png
	sh runner.sh '2'

clean:
	rm -f $(EXEC) $(DIROBJS)

help:
	@echo 'Opciones de compilación:'
	@echo 'Comando: make - Compila normalmente, genera un ejecutable llamado main y sus archivos objeto en la carpeta obj.'
	@echo 'Comando: make release - Compila de manera optimizada.'
	@echo 'Comando: make debug - Compila en modo debug.'
	@echo 'Comando: make clean - Limpia todos los archivos generados por la compilación incluyendo el ejecutable.'
	@echo 'Comando: make run1 - Realiza una ejecución del UMDA con las imágenes contenidas en la carpeta data y guarda los resultados en la carpeta out.'
	@echo 'Comando: make run2 - Realiza una ejecución del AG con las imágenes contenidas en la carpeta data y guarda los resultados en la carpeta out.'
