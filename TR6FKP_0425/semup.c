#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define SEMKEY 0x12

	int semid, nsems, rtn;
	unsigned nsops;
	int semflg;
	struct sembuf sembuf, *sop;

int main()

{
	nsems = 1;
	semflg = 00666 | IPC_CREAT;
	semid = semget (SEMKEY, nsems, semflg);
	if (semid < 0 ) {perror("semget() hiba!\n"); exit(0);}
	else printf("Azonosító: %d\n",semid);
	printf ("\n");
	
	nsops = 1;		
	sembuf.sem_num = 0;	
	sembuf.sem_op = 1;	
	sembuf.sem_flg = 0666;	
	sop = &sembuf;		
	rtn = semop(semid, sop, nsops); 
	printf("Visszatérési érték: %d\n",rtn);
	
    return 0;
}
