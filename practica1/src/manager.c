#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NUM_PROC 2
#define LEER 0
#define ESCRIBIR 1

int main(int argc, char const *argv[]) {

  if (argc != 2) {
    fprintf(stderr, "[MANAGER] Es necesario especificar el fichero de datos\n");
    return EXIT_FAILURE;
  }

  pid_t pa_pid, pids[NUM_PROC], tmp_pid;
  int status = 0, i;
  int tuberia[2];
  char media[2];

  pa_pid = fork();
  if (pa_pid == -1) {
    fprintf(stderr, "[MANAGER] Error creando el proceso A\n");
		return EXIT_FAILURE;
  } else if (pa_pid == 0) {
    execl("./exec/pa", argv[1], NULL);
    fprintf(stderr, "[MANAGER] ERROR en execl\n");
    return EXIT_FAILURE;
  }

  waitpid(pa_pid, &status, 0);

  if (status == EXIT_FAILURE) {
    return EXIT_FAILURE;
    /* limpiar todo */
  }

  printf("[MANAGER] Proceso [PA] finaliza\n");

  pipe(tuberia);

  for (i=0; i < NUM_PROC; i++) {
    if ((pids[i] = fork()) == 0) {
      switch (i) {
        case 0:
          printf("[MANAGER] Creando proceso [PB]\n");
          execl("./exec/pb", argv[1], NULL);
          fprintf(stderr, "[MANAGER] ERROR en execl\n");
          return EXIT_FAILURE;
        break;
        case 1:
          dup2(tuberia[ESCRIBIR], STDOUT_FILENO);
          printf("[MANAGER] Creando proceso [PC]\n");
          execl("./exec/pc", argv[1], NULL);
          fprintf(stderr, "[MANAGER] ERROR en execl\n");
          return EXIT_FAILURE;
        break;
      }
    } else if(pids[i] > 0) {
    } else {
      fprintf(stderr, "[MANAGER] Error creado [PA] y [PC]\n");
      return EXIT_FAILURE;
    }
  }

  read(tuberia[LEER], media, sizeof(media));
  printf("[MANAGER] La media es %s\n", media);

  for (i = 0; i < NUM_PROC; i++) {
    tmp_pid = wait(&status);
    if (tmp_pid == pids[0]) {
      printf("[MANAGER] Proceso [PB] finaliza\n");
    } else if (tmp_pid == pids[1]){
      printf("[MANAGER] Proceso [PC] finaliza\n");
    }
  }

  return EXIT_SUCCESS;
}
