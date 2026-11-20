#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
void h(int s){write(1,"Prijal som SIGUSR1\n",20);}
int main(){signal(SIGUSR1,h);
 printf("PID %d – čakám 20 s\n",getpid());sleep(20);printf("Koniec\n");
}
