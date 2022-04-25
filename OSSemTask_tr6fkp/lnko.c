#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SHMKEY 69905L //az osztott memóriaszegmes kulcsa

int lnko(int a, int b){  //euklideszi algoritmus a legnagyobb közös osztó meghatározására
    int c;
    while (b != 0){
        c = b;
        b = a%b;
        a = c;
    }
    return a;
}

int main() {
    
    FILE *input = fopen("input.txt", "r");
    char *line = malloc(1000*sizeof(char));
    char lines[15][20*sizeof(char)];
    char *token = malloc(1000*sizeof(char));
    char file_content[15][20*sizeof(char)];
    
    //ellenőrizzük a fájlmegnyitás sikerességét, sikertelen megnyitás esetén leállunk
    if(!input){
        printf("Input fájl megnyitása sikertelen!\n");
        return -1;
    }else{
        printf("Input fájl megnyitása sikeres!\n");
    }
    
    //beolvassuk a file tartalmát soronként egy lines nevű stringeket tartalmazó kétdimenziós tömbbe
    int line_counter = 0;
    while(fgets(line, 20*sizeof(char), input) != NULL){
        if (strlen(line) > 0 && line[strlen(line)-1] == '\n') line[strlen(line)-1] = '\0'; // a sor végén ottmaradt \n sortörést töröljük
        strcpy(lines[line_counter], line);
        line_counter++;
    }
    
    //a lines tömb stringjeit parseoljuk egy újabb stringeket tartalmazó kétdimenziós tömbbe, hogy a fájlból beolvasott számok egy tömb egyenkénti elemeiként legyenek tárolva
    int counter=0;
    for(int i=0; i<line_counter; i++){
        line=lines[i];
        token=strtok(line, " ");
        while(token != NULL){
            if (strlen(token) > 0 && line[strlen(token)-1] == '\n') token[strlen(token)-1] = '\0';
            strcpy(file_content[counter], token);
            counter++;
            token=strtok(NULL, " ");
        }
    }
    
    //az osztott memóriaszegmens struktúrája
    struct file_contents{
        int num;
        int nums[counter];
        int gcd[(int)(counter-1)/2];
    } *segm;
    
    int shmid;                                                   // a memóriaszegmnes azonosítója
    key_t key = SHMKEY;                                          // kulcs a memóriához
    int size = 512;                                              // a memóriaszegmens mérete byte-ban
    int shmflag;                                                // flag a jellemzőkhöz
    
    
    shmflag =0;
    if((shmid=shmget(key, size, shmflag)) < 0){
        shmflag = 00666 | IPC_CREAT;
        if((shmid=shmget(key, size, shmflag)) < 0){
            perror("Nem sikerült létrehozni az osztott memóriaszegmenst!\n");
            exit(-1);
        }else{
            printf("Az osztott memóriaszegmens létrejött! (ID: %d)\n", shmid);
        }
    }else{
        printf("A megadott KEY-jel már létezik osztott memóriaszegmens! %d\n", shmid);
        exit(-1);
    }
    
    shmflag =   00666 | SHM_RND;
    segm = (struct file_contents *)shmat(shmid, NULL, shmflag);
    if (segm == (void *)-1 ){
        perror("A memóriaszegmensre csatlakozás sikertelen!\n");
        exit(-1);
    }else{
        printf("A memóriaszegmensre csatlakozás sikeres!\n");
    }
    
    (segm->num) = file_content[0][0] - '0'; //char típus int típussá alakítva kerül a shm-be.
    for(int i=0;i<=counter-1; i++){
        (segm->nums[i]) = atoi(file_content[i+1]); //char típus int típussá alakítva kerül a shm-be.
    }
    
    //létrehozunk egy gyermekprocesszt, ami a szülő másolata lesz, de hogy ne csináljon végig minden ezutáni parancsot
    //a gyermekprocessz által végrehajtandó parancsokat egy feltételbe zárva gyakorlatilag a processzt is "bezárjuk"
    pid_t pid = fork();
    if ( pid == 0 ){
        printf("CHILD: Gyermekprocessz létrejött! (PID: %d)\n", pid);
        
        shmflag =   00666 | SHM_RND;
        segm = (struct file_contents *)shmat(shmid, NULL, shmflag); //az előzőleg létrehozott struktúrát rákapcsoljuk az osztott memóriaszegmensre
        if (segm == (void *)-1 ){
            perror("CHILD: A memóriaszegmensre csatlakozás sikertelen!\n");
            exit(-1);
        }else{
            printf("CHILD: A memóriaszegmensre csatlakozás sikeres!\n");
        }
        
        //kiszámoljuk a lnko-kat, majd kiírjuk őket a memóriaszegmensre
        int p = 0;
        for (int i = 0; i < (segm->num); i++){
            printf("CHILD: lnko(%d, %d) = %d\n", segm->nums[p], segm->nums[p+1], lnko(segm->nums[p],segm->nums[p+1]));
            segm->gcd[i] = lnko(segm->nums[p],segm->nums[p+1]);
            p=p+2;
        }
        exit(0); //lelőjük a gyermekprocesszt
    }
    pid = wait(NULL); //a szülő bevárja a(z összes) gyermekprocesszt, annak megszűnéséig várakozik
    printf("A %d PID-jű gyermekprocessz megszűnt!\n", pid);
    
    //visszamásoljuk az eredményeket egy tömbbe a memóriaszegmensről
    int lnko[segm->num];
    for(int i=0; i < (segm->num); i++){
        lnko[i]=segm->gcd[i];
    }
    int amount = segm->num;
    
    //töröljük a memóriaszegmenst
    shmctl(shmid, IPC_RMID, NULL);
    printf("Az %d ID-jű memóriaszegmens törölve!\n", shmid);
    
    //megnyitjuk az output fájlt; irási jogosultsággal, ami annyit tesz, hogy ha még nem létezik, akkor létrehozódik, ha már létezik a tartalma felülíródik
    FILE *output = fopen("output.txt", "w");
    
    //ellenőrizzük sikerült-e megnyitni
    if(!output){
        printf("Output fájl megnyitása sikertelen!\n");
        return -1;
    }else{
        printf("Output fájl megnyitása sikeres!\n");
    }
    
    //kiírjuk a fájlba az eredményeket soronként
    int p=1;
    for(int i = 0; i < amount; i++){
            sprintf(line, "%s %s %d\n", file_content[p], file_content[p+1], lnko[i]);
            fputs(line, output);
            p=p+2;
    }
    
    printf("Tartalom kiírva output.txt fájlba! A fájlok bezárásra kerülnek, majd a program leáll!\n");
    
    //bezárjuk a fájlokat és a dinamikusan foglalt memóriákat felszabadítjuk
    free(token);
    fclose(input);
    fclose(output);
    return EXIT_SUCCESS;
}