#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
pid_t p;
p = fork();
if(p==0){
char* argument_list[] = {"ls", "-l", NULL};
execvp("ls", argument_list);
}
else{

}
wait(NULL);

return 0;
}
