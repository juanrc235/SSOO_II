#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

#define ESPACIO " "
#define N_BYTES 4096

ssize_t getdelim(char **lineptr, size_t *n, int delim, FILE *stream);

void copiar (char *src_path, char *dst_path) {

  int len = sizeof(src_path) + sizeof(dst_path) + 3;
  char command[len];

  sprintf(command, "cp %s %s", src_path, dst_path);
  printf("[PB] Copiado <%s> en <%s>\n", src_path, dst_path);

  system(command);
}

int main(int argc, char const *argv[]) {

  char *line = NULL;
  char *nombre_dir = NULL, *tipo_ex = NULL, src_path[256], dst_path[256];
  char file_name[256];
  struct stat sb;

  size_t len = 0;
  FILE *file;

  file = fopen(argv[0], "r");

  if (file) {

    while (getdelim(&line, &len, '\n', file) != -1) {
      nombre_dir = strtok(line, ESPACIO);
      tipo_ex = strtok(NULL, ESPACIO);

      if (stat(nombre_dir, &sb) == 0 && S_ISDIR(sb.st_mode)) {

        /* Construimos el nombre del fichero */
        sprintf(file_name, "%s.pdf", tipo_ex);

        /* Construimos el directorio destino */
        sprintf(dst_path, "%s/", nombre_dir);

        /* Construimos el directorio origen */
        sprintf(src_path, "modelos/%s", file_name);

        copiar(src_path, dst_path);

      } else {
        printf("[PB] El directorio <%s/> no existe\n", nombre_dir);
      }

    }

    fclose(file);
  }

  return 0;
}
