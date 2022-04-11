#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
    int fd[2];
    pid_t wpid;
    int status = 0;
    if (pipe(fd) == -1) {
       fprintf(stderr, "Pipe faild");
    return 1;
    }

    pid_t p = fork();
    if (p < 0) {
        fprintf(stderr, "fork Failed");
        return 1;
    } else if (p>0){
        close(fd[1]);
        wpid = wait(&status);
        char input_str[30];
        read(fd[0],input_str,30);
        printf("Kapott string: %s",input_str);

    } else {
        close(fd[0]);
        char output_str[30] = "Pogonyi Abel TR6FKP\0";
        write(fd[1],output_str,strlen(output_str)+1);
        close(fd[1]);
        exit(0);
    }


    return 0;
}