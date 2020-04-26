DIROBJ := obj/
DIREXE := exec/
DIRHEA := include/
DIRSRC := src/

LDLIBS := -pthread -std=c++11
CC := g++

all: dirs main

dirs:
	mkdir -p $(DIREXE)

main:
	g++ $(DIRSRC)*.cpp -o $(DIREXE)CINEMA_SIMULATION -I$(DIRHEA) $(LDLIBS)

clean :
	rm -rf *~ core $(DIROBJ) $(DIREXE) $(DIRHEA)*~ $(DIRSRC)*~ $(DIRHEA)*gch

run:
	$(DIREXE)CINEMA_SIMULATION
