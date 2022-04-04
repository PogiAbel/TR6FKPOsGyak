#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    // File megnyitas
    int f = open("tr6fkp.txt",O_RDWR);

    //Kiirando szoveg
    char string[] = "Pogonyi Abel Kurt, Programtervezo Informatika, TR6FKP";

    //Beolvasas ellenorzes
    if (f ==-1) 
    {
        printf("Sikertelen");                
    }

    printf("Beirt: %d",write(f,string,strlen(string)));

    //File elejere megy
    int offset = lseek(f,0,SEEK_SET);
    printf("\nFile %d. byte-hoz menes",offset);

    //Kiolvas
     char ch[60];   
    int olvas = read(f,ch,53);
    printf("\nBeolvasott:%s %d",ch,olvas);

    return 0;
}