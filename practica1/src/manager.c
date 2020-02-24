#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>

#define NUM_PROC 2
#define LEER 0
#define ESCRIBIR 1

pid_t g_pid[3];

void manejador(int);

int main(int argc, char const *argv[]) {

  if (argc != 2) {
    fprintf(stderr, "[MANAGER] Es necesario especificar el fichero de datos\n");
    return EXIT_FAILURE;
  }

  pid_t pa_pid, pids[NUM_PROC], tmp_pid;
  int status = 0, i;
  int tuberia[2];
  char media[2] = {0};
  FILE *fd_log;
  fd_log = fopen("log.txt", "a");

  fprintf(fd_log, "******** Log del sistema ********\n");

  signal(SIGINT, manejador);

  pa_pid = fork();
  g_pid[0] = pa_pid;
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
  fprintf(fd_log, "Creación de directorios finalizada.\n");

  pipe(tuberia);

  for (i=0; i < NUM_PROC; i++) {
    if ((pids[i] = fork()) == 0) {
      g_pid[i+1] = pids[i];
      switch (i) {
        case 0:
          printf("[MANAGER] Creando proceso [PB]\n");
          execl("./exec/pb", argv[1], NULL);
          fprintf(stderr, "[MANAGER] ERROR en execl\n");
          return EXIT_FAILURE;
        break;
        case 1:
          printf("[MANAGER] Creando proceso [PC]\n");
          dup2(tuberia[ESCRIBIR], STDOUT_FILENO);
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

  for (i = 0; i < NUM_PROC; i++) {
    tmp_pid = wait(&status);
    if (tmp_pid == pids[0]) {
      fprintf(fd_log, "Copia de modelos de examen, finalizada.\n");
      printf("[MANAGER] Proceso [PB] finaliza\n");
    } else if (tmp_pid == pids[1]){
      fprintf(fd_log, "Creación de archivos con nota necesaria para alcanzar la nota de corte, finalizada.\n");
      printf("[MANAGER] Proceso [PC] finaliza\n");
    }
  }

  read(tuberia[LEER], media, sizeof(media));
  fprintf(fd_log, "La nota media de la clase es: %s\n", media);

  fclose(fd_log);
  return EXIT_SUCCESS;
}

void manejador(int signal) {
  int i;
  printf("[MANAGER] Todos muertos");
  for (i=0; i < 3; i++) {
    kill(g_pid[i], SIGKILL);
  }
  printf("[MANAGER] Todos muertos");
}
