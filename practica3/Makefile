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

run3:
	$(DIREXE)SSOOIIGLE presidente "8-libros-txt/21 LEYES DEL LIDERAZGO - JOHN C. MAXWELL.txt" 5
