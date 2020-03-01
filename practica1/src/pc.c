#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constantes.h"

ssize_t getdelim(char **lineptr, size_t *n, int delim, FILE *stream);

int calcular_nota_necesaria(int n1) {
  return  2*MINIMA_NOTA - n1;
}

int main(int argc, char const *argv[]) {

  char *line = NULL;
  char *nombre_dir = NULL, *str_nota = NULL, dst_path[256];
  int nota = 0, n_bytes = sizeof(MSG) + 3, sumatorio = 0, n_alumnos = 0;
  char msg[n_bytes];

  size_t len = 0;
  FILE *file;
  FILE *e_file;

  file = fopen(argv[0], "r");

  if (file) {

    while (getdelim(&line, &len, '\n', file) != -1) {

      nombre_dir = strtok(line, ESPACIO);
      strtok(NULL, ESPACIO);
      str_nota = strtok(NULL, ESPACIO);
      nota = atoi(str_nota);
      sumatorio += nota;
      n_alumnos += 1;

      sprintf(dst_path, "%s/%s", nombre_dir, NOMBRE_FICHERO);
      e_file = fopen(dst_path, "w");

      sprintf(msg, "%s %d\t\n", MSG, nota);
      fwrite(msg, 1, sizeof(msg), e_file);

      fclose(e_file);

    }
    fclose(file);
  }

  printf("%.2f", (double)sumatorio/n_alumnos);

  return 0;
}
