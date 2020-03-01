#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constantes.h"

int main(int argc, char const *argv[]) {

  FILE *file;
  char *line = NULL;
  size_t len = 0;
  char command[16];
  char *nombre_dir = NULL;

  file = fopen(argv[1], "r");

  if (file) {

    while (getdelim(&line, &len, '\n', file) != -1) {

      nombre_dir = strtok(line, ESPACIO);
      sprintf(command, "rm -fr %s", nombre_dir);
      system(command);
      printf("[PD] Eliminado %s\n", nombre_dir);
      
    }
    fclose(file);
  }

  return 0;
}
