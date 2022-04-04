#include <stdio.h>
#include <signal.h>
#include <unistd.h>
void handleSignals(int sig){
    printf("Signal: %d\n",sig);
}

int main(){
    signal(SIGINT, handleSignals);
    for (int i = 0; ;i++)
    {
        printf("Fo szal\n");
        sleep(1);
    }
    

    return 0;
}