DIROBJ := obj/
DIREXE := exec/
DIRHEA := include/
DIRSRC := src/

LDLIBS := -pthread -std=c++11
CC := g++

all: dirs SSOOIIGLE

dirs:
	mkdir -p $(DIREXE)

SSOOIIGLE:
	g++ $(DIRSRC)*.cpp -o $(DIREXE)SSOOIIGLE -I$(DIRHEA) $(LDLIBS)

clean :
	rm -rf *~ core $(DIROBJ) $(DIREXE) $(DIRHEA)*~ $(DIRSRC)*~

run:
	$(DIREXE)SSOOIIGLE casa "8-libros-txt/fichero_casos.txt" 2

run2:
	$(DIREXE)SSOOIIGLE casa "8-libros-txt/Abe Shana - La última sirena.txt" 5
