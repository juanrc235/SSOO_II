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
	g++ src/*.cpp -o $(DIREXE)main

clean :
	rm -rf *~ core $(DIROBJ) $(DIREXE) $(DIRHEA)*~ $(DIRSRC)*~

run:
	$(DIREXE)main casa "fichero_casos.txt" 2
