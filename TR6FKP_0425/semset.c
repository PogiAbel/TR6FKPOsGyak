#include <stdlib.h>	
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define SEMKEY 0x12  

	int semid,	
	    nsems,	
	    semnum,	
	    rtn;	

	int semflg;	
	struct sembuf sembuf, *sop;
    	union semun;

	int cmd;	

int main()

{

    int arg;

	nsems = 1;	
	semflg = 00666 | IPC_CREAT;
	semid = semget (SEMKEY, nsems, semflg);
	if (semid < 0 ) {perror("semget() hiba!\n"); exit(0);}
	else printf("\n Az azonosító: %d\n",semid);

	printf ("Kérem a semval erteket: ");
	semnum = 0;	
	cmd = SETVAL;	
	scanf("%d", &arg);
	rtn = semctl(semid, semnum, cmd, arg); 
	printf("\nVisszatérési érték: %d\nSemval értéke: %d\n",rtn, arg);

    return 0;
}
