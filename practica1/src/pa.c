#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PERMISOS 0777
#define ESPACIO " "

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

  char *line = NULL;
  char *nombre_dir = NULL;
  size_t len = 0;

  FILE *file;
  file = fopen(argv[0], "r");

  sleep(50);

  if (file) {

    while (getdelim(&line, &len, '\n', file) != -1) {
      nombre_dir = strtok(line, ESPACIO);
      crear_dir(nombre_dir, PERMISOS);
    }

    fclose(file);
  }

  return EXIT_SUCCESS;
}
