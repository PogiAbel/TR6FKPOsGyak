#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{

	int fd, ret;
	char buf[32];

	buf[0]=0;
	pid_t cpid;
	ret=mkfifo("tr6fkp",00666);
	if (ret == -1) {
	     perror("mkfifo()");
	     exit(-1);
	 }
	 cpid = fork();
         if (cpid == -1) {
	   perror("fork");
	   exit(-1);
        } 
        if(cpid == 0){  /*gyerek processz*/
          fd=open("tr6fkp",O_RDWR);
	  if (fd == -1) {
	      perror("open() hiba!");
	      exit(-1);
	  }

	  strcpy(buf,"Pogonyi Abel Kurt\0");
	  printf("irok a fifoba: %s:%d\n",buf,strlen(buf));
	  write(fd,buf,strlen(buf));
	  close(fd);
	  sleep(300);
	  exit(0);
        }
        else {		/*szülő processz*/
	  wait(NULL);
	  fd=open("tr6fkp",O_RDWR);
	  if (fd == -1) {
	      perror("open() hiba!");
	      exit(-1);
	  }
	  ret=read(fd,buf,32); 
	  printf("read() olvasott %d byteot, ami a kovetkezo: %s\n",ret,buf);
	  unlink("tr6fkp");
	  exit(0);
        }	
}