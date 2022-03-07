#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(){
char *args[] = {"XY_child","c","programe",NULL};
execv("./XY_child", args);

return 0;
}
