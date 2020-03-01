#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include "constantes.h"

pid_t g_pid[3];
const char *fichero_datos;

void manejador(int);
void cambiar_programa(const char *path, const char *file);
void crear_y_esperar_pa(FILE *fd_log);
void crear_y_esperar_pb_y_pc(int tuberia[2], FILE *fd_log);
void crear_y_esperar_pd();
void esperar_pb_pc();
void recibir_media(int tuberia[2], FILE *fd_log);

int main(int argc, char const *argv[]) {

  signal(SIGINT, manejador);

  if (argc != 2) {
    fprintf(stderr, "[MANAGER] Es necesario especificar el fichero de datos\n");
    return EXIT_FAILURE;
  }

  int tuberia[2];
  FILE *fd_log;
  fd_log = fopen(N_LOG, "a");
  fichero_datos = argv[1];

  fprintf(fd_log, "******** Log del sistema ********\n");

  crear_y_esperar_pa(fd_log);

  crear_y_esperar_pb_y_pc(tuberia, fd_log);

  recibir_media(tuberia, fd_log);

  fclose(fd_log);

  return EXIT_SUCCESS;
}

void cambiar_programa(const char *path, const char *file) {
  execl(path, file, NULL);
  fprintf(stderr, "[MANAGER] ERROR en execl\n");
  exit(EXIT_FAILURE);
}

void crear_y_esperar_pd(){
  int status;
  pid_t pd_pid = fork();
  if (pd_pid == -1) {
    fprintf(stderr, "[MANAGER] Error creando el proceso [PD]\n");
    exit(EXIT_FAILURE);
  } else if (pd_pid == 0) {
    cambiar_programa(RUTA_PD, fichero_datos);
  } else if (pd_pid > 0) {
    waitpid(pd_pid, &status, 0);
    if (status == EXIT_FAILURE) {
      exit(EXIT_FAILURE);
    }
    printf("[MANAGER] Finalizado [PD]. Todo los directorios borrados \n");
  }
}

void crear_y_esperar_pa(FILE *fd_log) {

  int status;

  pid_t pa_pid = fork();
  g_pid[0] = pa_pid;
  if (pa_pid == -1) {
    fprintf(stderr, "[MANAGER] Error creando el proceso A\n");
		exit(EXIT_FAILURE);
  } else if (pa_pid == 0) {
    cambiar_programa(RUTA_PA, fichero_datos);
  } else if (pa_pid > 0) {
      waitpid(pa_pid, &status, 0);
      if (status == EXIT_FAILURE) {
        exit(EXIT_FAILURE);
      }
      printf("[MANAGER] Proceso [PA] finaliza\n");
      fprintf(fd_log, "Creación de directorios finalizada.\n");
  }

}

void crear_y_esperar_pb_y_pc(int tuberia[2], FILE *fd_log) {

  int i, status;
  pid_t pids[NUM_PROC], tmp_pid;
  pipe(tuberia);

  for (i=0; i < NUM_PROC; i++) {
    if ((pids[i] = fork()) == 0) {
      g_pid[i+1] = pids[i];
      switch (i) {
        case 0:
          printf("[MANAGER] Creando proceso [PB]\n");
          cambiar_programa(RUTA_PB, fichero_datos);
        break;
        case 1:
          printf("[MANAGER] Creando proceso [PC]\n");
          dup2(tuberia[ESCRIBIR], STDOUT_FILENO);
          cambiar_programa(RUTA_PC, fichero_datos);
        break;
      }
    } else if(pids[i] > 0) {
    } else {
      fprintf(stderr, "[MANAGER] Error creado [PB] y [PC]\n");
      exit(EXIT_FAILURE);
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
}

void recibir_media(int tuberia[2], FILE *fd_log){
  char media[2] = {0};

  read(tuberia[LEER], media, sizeof(media));
  fprintf(fd_log, "La nota media de la clase es: %s\n", media);
}

void manejador(int signal) {
  int i;
  printf("\n[MANAGER] Eliminando procesos ...\n");
  for (i=0; i < 3; i++) {
    if (g_pid[i] != 0) {
      kill(g_pid[i], SIGKILL);
    }
  }

  printf("[MANAGER] Todos muertos, llamando a [PD] para que limpie ...\n");
  crear_y_esperar_pd();

  exit(EXIT_SUCCESS);
}
