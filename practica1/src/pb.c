#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

#define PERMISOS 0777
#define ESPACIO " "
#define N_BYTES 4096

void copiar (char *src_path, char *dst_path) {

  unsigned char buffer[N_BYTES];
  int src_fd = open(src_path, O_RDONLY);
  int dst_fd = open(dst_path, O_CREAT | O_WRONLY);
  int err, n;

  while (1) {

     err = read(src_fd, buffer, N_BYTES);
     if (err == -1) {
         printf("Error reading file.\n");
         exit(1);
     }

     n = err;
     if (n == 0) {
       break;
     }

     err = write(dst_fd, buffer, n);
     if (err == -1) {
         printf("Error writing to file.\n");
         exit(1);
     }
  }

  close(src_fd);
  close(dst_fd);
}

int main(int argc, char const *argv[]) {

  char *nombre_fichero = "estudiantes_p1.text";
  char *line = NULL;
  char *nombre_dir = NULL, *tipo_ex = NULL;

  size_t len = 0;
  FILE *file;
  file = fopen(nombre_fichero, "r");

  if (file) {

    while (getdelim(&line, &len, '\n', file) != -1) {
      nombre_dir = strtok(line, ESPACIO);
      tipo_ex = strtok(NULL, ESPACIO);
      printf("%s || %s\n", nombre_dir, tipo_ex);
    }

    fclose(file);
  }

  copiar("modelos/MODELOA.pdf", "prueba/a.pdf");

  return 0;
}
