#include <stdio.h>

int main(){
    FILE *f;
    f = fopen("tr6fkp.txt","r");

    if (NULL == f){
        printf("Nem lehet a file-t megyitni");
    }

    return 0;
}