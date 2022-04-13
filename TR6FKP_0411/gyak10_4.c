#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#define MSGKEY 646464L



struct msgbuf1 {		
	long mtype;
	char mtext[512];
} sndbuf, *msgp;		

struct msqid_ds ds, *buf;




int main()
{
	int msgid;		
	key_t key;		
	int msgflg;		
	int rtn, msgsz;		
	
	key = MSGKEY;
	msgflg = 00666 | IPC_CREAT;
	msgid = msgget( key, msgflg);
 	if ( msgid == -1) {
                perror("\n Az msgget rendszerhívás sikertelen!");
                exit(-1);
        }


	msgp = &sndbuf;
	msgp->mtype = 1;   			
 	strcpy(msgp->mtext,"Pogonyi");
	msgsz = strlen(msgp->mtext) + 1;	

    rtn = msgsnd(msgid,(struct msgbuf *) msgp, msgsz, msgflg);

	strcpy(msgp->mtext,"Abel Kurt");
	msgsz = strlen(msgp->mtext) + 1;
	rtn = msgsnd(msgid,(struct msgbuf *) msgp, msgsz, msgflg);
    
if (msgp->mtext == "exit"){     
    exit(0);
}


	key_t kulcs;		
	int tipus;      
	int meret;		
	
	kulcs = MSGKEY;		
	msgflg = 00666 | IPC_CREAT | MSG_NOERROR;

	msgid = msgget(kulcs, msgflg);    
 	if ( msgid == -1) {
                perror("\n Az msgget rendszerhívás sikertelen!");
                exit(-1);
        }
	printf("\n Az üzenet ID: %d\n\n",msgid);

	msgp = &sndbuf;
	buf = &ds;
	meret = 20;
	tipus = 0;
	rtn = msgctl(msgid,IPC_STAT,buf);
	
	rtn = msgrcv(msgid,(struct msgbuf *)msgp, meret, tipus, msgflg);
	rtn = msgctl(msgid,IPC_STAT,buf);  

do {
    printf("\n Válasszon:");
    printf("\n 0. Üzenet darabszám");
    printf("\n 1. 1 üzenet kiolvasása");
    printf("\n 2. Üzenetsor megszüntetése");
    printf("\n 3. Kilépés\n");
    scanf("%d", &msgid);
  }while(msgid < 0 && msgid > 1);

  switch(msgid)
  {
    case 0:
        printf("\n Az üzenetek száma: %ld\n",buf->msg_qnum);
        break;

    case 1:
        printf("\n A kiküldött üzenet: %s\n", msgp->mtext);
        break;

    case 2:
        rtn = msgctl(msgid, IPC_RMID, NULL);
        printf("\n Üzenetsor megszüntetve\n");
        break;

    case 3:
        exit(0);      
  }
}