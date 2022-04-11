#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
    int fd,fd1;
    int status = 0;
    char input[30];
    char * myfifo = "/myfifo";

    pid_t p = fork();
    if (p < 0) {
        fprintf(stderr, "fork Failed");
        return 1;
    } else if (p>0){
        
        mkfifo(myfifo, 0666);
        wait(&status);
        fd = open(myfifo, O_RDONLY);
        read(fd, input, 80);
        printf("Kapot uzenet:%s",input);


    } else {
        fd1 = open(myfifo,O_WRONLY);
        char out_text[] = "Pogonyi TR6FKP\0";
        write(fd1,out_text,strlen(out_text)+1);
        close(fd1);

    }




    return 0;
}