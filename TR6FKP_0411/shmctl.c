#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SHMKEY 13

int main()
{
  int shmid;
  key_t kulcs;
  int meret = 512;
  int flag, rtn, sm;
  struct shmid_ds shmid_ds, *buf;

  buf = &shmid_ds;
  kulcs = SHMKEY;
  flag = 0;

  if((shmid = shmget(kulcs, meret, flag)) < 0)
  {
     perror("\n Sikertelen volt az shmget!\n");
     exit(-1);
  }

rtn = shmctl(shmid, IPC_STAT, buf);
printf("\n Méret: %ld", buf->shm_segsz);
printf("\n PID: %d\n", buf->shm_lpid);


  exit(0);
}