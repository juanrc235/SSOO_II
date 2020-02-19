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
#define BARRA "/"

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

  file = fopen("estudiantes_p1.text", "r");

  if (file) {

    while (getdelim(&line, &len, '\n', file) != -1) {

      nombre_dir = strtok(line, ESPACIO);
      strtok(NULL, ESPACIO);
      str_nota = strtok(NULL, ESPACIO);
      nota = atoi(str_nota);

      memset(&dst_path[0], 0, sizeof(dst_path));
      memset(&msg[0], 0, sizeof(msg));

      strcat(dst_path, nombre_dir);
      strcat(dst_path, BARRA);
      strcat(dst_path, NOMBRE_FICHERO);
      e_file = fopen(dst_path, "w");

      printf("[PC] Escrito mensaje en <%s>\n", dst_path);

      strcat(msg, MSG);
      strcat(msg, ESPACIO);
      sprintf(str_nota, "%d", nota);
      strcat(msg, str_nota);
      strcat(msg, "\t\n");
      fwrite(msg, 1, sizeof(msg), e_file);

      fclose(e_file);

    }

    fclose(file);
  }

  return 0;
}
