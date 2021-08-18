/*
Basics:

1. Create 
2. 


*/
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* myturn(void * arg) {
    for(int i = 0; i < 8; i++) {
        sleep(1);
        printf("(%d) My turn!\n", i + 1);
    }
    return NULL;
}

void yourturn() {
    for(int i = 0; i < 5; i++) {
        sleep(1);
        printf("(%d) Your turn!\n", i + 1);
    }
}
int main(){
    pthread_t newthread;
    int v = 0;

    pthread_create(&newthread, NULL, myturn, &v);
    //myturn();
    yourturn();
    pthread_join(newthread, NULL); //It'll wait until a thread is done and it will continue
}