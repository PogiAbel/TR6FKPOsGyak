#include <stdio.h>
#include <signal.h>
#include <unistd.h>
void handleSignals(int sig){
    if(sig == 3){
        printf("Signal: %d\n",sig);
    } else if(sig == SIGINT){
        printf("Signal: %d\n",sig);
    }
}

int main(){
    signal(SIGINT, handleSignals);
    int pid =1;
    for (int i = 0; ;i++)
    {
        printf("Fo szal\n");
        sleep(1);
    }

    return 0;
}