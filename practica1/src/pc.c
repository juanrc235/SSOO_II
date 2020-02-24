#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

#define ESPACIO " "
#define MINIMA_NOTA 5
#define MSG "La nota que debes obtener en este nuevo examen para superar la prueba es"
#define NOMBRE_FICHERO "fichero.txt"

ssize_t getdelim(char **lineptr, size_t *n, int delim, FILE *stream);

int calcular_nota_necesaria(int n1) {
  return  2*MINIMA_NOTA - n1;
}

int main(int argc, char const *argv[]) {

  char *line = NULL;
  char *nombre_dir = NULL, *str_nota = NULL, dst_path[256];
  int nota = 0, n_bytes = sizeof(MSG) + 3;
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

      sprintf(dst_path, "%s/%s", nombre_dir, NOMBRE_FICHERO);
      e_file = fopen(dst_path, "w");

      sprintf(msg, "%s %d\t\n", MSG, nota);
      fwrite(msg, 1, sizeof(msg), e_file);

      /*printf("[PC] Escrito mensaje en <%s>\n", dst_path);*/

      fclose(e_file);

    }
    fclose(file);
  }

  fprintf(stdout, "3");

  return 0;
}
