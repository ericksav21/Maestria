CC=gcc
EXEC=main
SRCDIR=src
OBJDIR=obj
BINDIR=bin
LATEXDIR=latex
DOCSDIR=docs

$(EXEC):
	cd $(SRCDIR) && $(MAKE)

opt:
	cd $(SRCDIR) && $(MAKE) CFLAGS="-O2"

deb:
	cd $(SRCDIR) && $(MAKE) CFLAGS="-g"

help:
	@echo 'Clasificador de textos, elaborado por Erick Salvador Alvarez Valencia.'
	@echo 'Opciones de compilación:'
	@echo 'Comando: make - Compila normalmente, genera un ejecutable llamado main.'
	@echo 'Comando: make opt - Compila de manera optimizada.'
	@echo 'Comando: make deb - Compila en modo debug.'
	@echo 'Comando: make clatex - Compila el reporte escrito en latex y genera un archivo PDF en la carpeta docs.'
	@echo 'Comando: make clean - Limpia todos los archivos generados por la compilación, excepto los ejecutables y el documento en PDF.'
	@echo 'Comando: make cleanall - Limpia todos los archivos, incluyendo los ejecutables y los documentos.'

clatex:
	cd $(LATEXDIR) && $(MAKE)

clean:
	rm -f $(BINDIR)/chunked_*.txt $(BINDIR)/words.txt $(BINDIR)/frequencies.txt $(BINDIR)/clasified.txt $(OBJDIR)/*.o $(DOCSDIR)/*.log $(DOCSDIR)/*.aux

cleanall:
	rm -f $(BINDIR)/* $(OBJDIR)/*.o $(DOCSDIR)/*