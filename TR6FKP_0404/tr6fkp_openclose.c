#include <stdio.h>
#include <unistd.h>

int main(){
    FILE *f;
    f = fopen("tr6fkp.txt","r+");

    if (NULL == f){
        printf("Nem lehet a file-t megyitni");
    }
    else printf("Sikeres megnyitas");
    if (write(1, "This will be output to testfile.txt\n", 36) != 36) {
        write(2, "There was an error writing to testfile.txt\n", 43);
        return -1;
    }

    return 0;
}
