
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
pid_t child_pid, wpid;
int status = 0;

//Father code (before child processes start)

for (int id=0; id<3; id++) {
    if ((child_pid = fork()) == 0) {
        if(id==0){
	printf("child abort pid: %d\n",getpid());
	abort();
	}else if(id==1){
	printf("child exit pid:%d\n",getpid()); 
	exit(0);
	}else{
	printf("child 0 osztas pid:%d\n",getpid());
	// int i = 1/0;
	}
    }
}

while (( wpid = wait(&status)) > 0){
	printf("Status %d\n",status);
}


return 0;
}

