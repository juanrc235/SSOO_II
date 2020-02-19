#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

#define ESPACIO " "
#define COPY "cp "
#define N_BYTES 4096
#define BARRA "/"
#define SRC_PATH "modelos/"
#define EXTENSION ".pdf"

ssize_t getdelim(char **lineptr, size_t *n, int delim, FILE *stream);

void copiar (char *src_path, char *dst_path) {

  int len = sizeof(src_path) + sizeof(dst_path) + sizeof(COPY) + sizeof(ESPACIO);
  char command[len];

  strcat(command, COPY);
  strcat(command, src_path);
  strcat(command, ESPACIO);
  strcat(command, dst_path);

  printf("%s\n", command);

  system(command);

  memset(&command[0], 0, sizeof(command));

}

int main(int argc, char const *argv[]) {

  char *line = NULL;
  char *nombre_dir = NULL, *tipo_ex = NULL, src_path[256], dst_path[256];
  char file_name[256];
  struct stat sb;

  size_t len = 0;
  FILE *file;

  file = fopen("estudiantes_p1.text", "r");

  if (file) {

    while (getdelim(&line, &len, '\n', file) != -1) {
      nombre_dir = strtok(line, ESPACIO);
      tipo_ex = strtok(NULL, ESPACIO);

      if (stat(nombre_dir, &sb) == 0 && S_ISDIR(sb.st_mode)) {

        /* Construimos el nombre del fichero */
        strcat(file_name, tipo_ex);
        strcat(file_name, EXTENSION);

        /* Construimos el directorio destino */
        strcat(dst_path, nombre_dir);
        strcat(dst_path, BARRA);

        /* Construimos el directorio origen */
        strcat(src_path, SRC_PATH);
        strcat(src_path, file_name);

        copiar(src_path, dst_path);

        /* Limpia las variables */
        memset(&file_name[0], 0, sizeof(file_name));
        memset(&dst_path[0], 0, sizeof(dst_path));
        memset(&src_path[0], 0, sizeof(src_path));
      } else {
        printf("[PB] El directorio <%s/> no existe\n", nombre_dir);
      }

    }

    fclose(file);
  }

  return 0;
}
