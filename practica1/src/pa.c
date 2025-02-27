/*******************************************************************************
* Project         : Práctica de laboratorio 1 de SSOO II
*
* Program name    : pa.c
*
* Purpose         : Crea un directorio para cada alumno que se encuentra en el
*                   fichero de datos.
*
*******************************************************************************/

#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "constantes.h"

#include <unistd.h>

ssize_t getdelim(char **lineptr, size_t *n, int delim, FILE *stream);

void crear_dir(char nombre_dir[], int permisos) {
  struct stat st = {0};

  if (stat(nombre_dir, &st) == -1) {
    mkdir(nombre_dir, permisos);
    printf("[PA] Directorio creado: %s/\n", nombre_dir);
  } else {
    fprintf(stderr, "[PA] El directorio <%s/ ya existe\n", nombre_dir);
  }

}

int main(int argc, char const *argv[]) {

  /*sleep(20); para probar el Ctrl+C*/

  char *line = NULL;
  char *nombre_dir = NULL;
  size_t len = 0;

  FILE *file;
  file = fopen(argv[0], "r");

  if (file) {

    while (getdelim(&line, &len, '\n', file) != -1) {
      nombre_dir = strtok(line, ESPACIO);
      crear_dir(nombre_dir, PERMISOS);
    }

    fclose(file);
  }

  return EXIT_SUCCESS;
}
