#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
pid_t pids[3];
int n = 3;

/* Start children. */
  if ((pids[0] = fork()) < 0) {
    perror("fork");
    abort();
  } else if (pids[0] == 0) {
    exit(0);
  }

  if ((pids[1] = fork()) < 0) {
    perror("fork");  
    abort(); 
  } else if (pids[1] == 0) {
    abort();
  }

  if ((pids[2] = fork()) < 0) {
    perror("fork");  
    abort(); 
  } else if (pids[2] == 0) {
    int szam = 7/0;
    printf("%d",szam);
    exit(0);
  }



/* Wait for children to exit. */
int status;
pid_t pid;
while (n > 0) {
  pid = wait(&status);
  printf("Child with PID %ld exited with status 0x%x.\n", (long)pid, status);
  --n;  // TODO(pts): Remove pid from the pids array.
}

return 0;
}
