#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {

  pid_t pa_pid;
  int status = 0;

  pa_pid = fork();
  if (pa_pid == -1) {
    fprintf(stderr, "[MANAGER] Error creando el proceso A\n");
		return EXIT_FAILURE;
  } else if (pa_pid == 0) {
    execl("./exec/pa", "a", NULL);
    fprintf(stderr, "[MANAGER] ERROR en execl\n");
    return EXIT_FAILURE;
  }

  waitpid(pa_pid, &status, 0);

  if (status == EXIT_FAILURE) {
    return EXIT_FAILURE;
    /* limpiar todo */
  }

  printf("[MANAGER] Proceso <pa> finaliza\n");

  return EXIT_SUCCESS;
}
