#include <stdio.h>
#include <stdlib.h>


int main(){

 char command[20];

    do{
    printf("Adja meg a parancsot: ");
    scanf("%s", command);
    
    system(command);
    }
   while(command!="^c");
  
  return 0;
}
