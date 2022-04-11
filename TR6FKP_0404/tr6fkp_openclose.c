#include <stdio.h>
<<<<<<< HEAD
#include <unistd.h>

int main(){
    FILE *f;
    f = fopen("tr6fkp.txt","r+");
=======
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    // File megnyitas
    int f = open("tr6fkp.txt",O_RDWR);
>>>>>>> 5bbb63ab8860f84b51459cca15ab41bb415a43b9

    //Kiirando szoveg
    char string[] = "Pogonyi Abel Kurt, Programtervezo Informatika, TR6FKP";

    //Beolvasas ellenorzes
    if (f ==-1) 
    {
        printf("Sikertelen");                
    }
    else printf("Sikeres megnyitas");
    if (write(1, "This will be output to testfile.txt\n", 36) != 36) {
        write(2, "There was an error writing to testfile.txt\n", 43);
        return -1;
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
