#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
char *args[] = {"XY_child","c","programe",NULL};
execv("./XY_child", args);
wait(NULL);
return 0;
}
