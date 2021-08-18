#include  "monitor.h"

#include  <pthread.h>

static  int  c;                 //Contador estático
static  pthread_mutex_t  MonitorLock;   //Mutex

void  monitorInit(int  n){
    c = n;
    pthread_mutex_init(&MonitorLock, NULL);
}

/*
É necessário salvar imediatamente o valor do contador para evitar que outra 
thread no momento em que a função foi chamada faça uma operação no contador
 e assim faça que a função retorne um valor inesperado.
*/
int  counterInc(void){
    int  aux;

    pthread_mutex_lock(&MonitorLock);          
        aux = (++c);            
    pthread_mutex_unlock(&MonitorLock);        
    return  aux;                     
}

int  counterDec(void){
     int  aux;

    pthread_mutex_lock(&MonitorLock);
        aux = (--c);
    pthread_mutex_unlock(&MonitorLock);
    return  aux;
}

void  counterSet(int  n){
    pthread_mutex_lock(&MonitorLock);
    c = n;
    pthread_mutex_unlock(&MonitorLock);
}

//Por causa do uso de threads o valor retornado do contador não é confiável.
int  counterGet(void){
    int  aux;

    pthread_mutex_lock(&MonitorLock);
        aux = c;
    pthread_mutex_unlock(&MonitorLock);
    return  aux;
}