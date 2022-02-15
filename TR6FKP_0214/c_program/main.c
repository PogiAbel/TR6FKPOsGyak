#include <stdio.h>
#include <stdlib.h>


main(){

FILE *fp;
char buff[255];
char c;
char* stringg = "Pogonyi Abel Kurt\nTR6FKP\nProgramtervezo Informatika";

fp = fopen("pogonyi.txt","w");
if(fp == NULL) exit(-1);

if(fprintf(fp,stringg)>0) printf("Sikeres iras.\n");
fclose(fp);

printf("Waiting for input:");
scanf("%s",c);
return ;
}
