DIROBJ := obj/
DIREXE := exec/
DIRHEA := include/
DIRSRC := src/

CFLAGS := -I$(DIRHEA) -c -Wall -ansi
LDLIBS := -lpthread -lrt
CC := g++

all: dirs main

dirs:
	mkdir -p $(DIROBJ) $(DIREXE)

main:
	g++ src/*.cpp -o $(DIREXE)SSOOIIGLE -pthread -std=c++11

clean :
	rm -rf *~ core $(DIROBJ) $(DIREXE) $(DIRHEA)*~ $(DIRSRC)*~

run:
	$(DIREXE)SSOOIIGLE casa "fichero_casos.txt" 2

run2:
	$(DIREXE)SSOOIIGLE casa "8-libros-txt/Abe Shana - La última sirena.txt" 5
