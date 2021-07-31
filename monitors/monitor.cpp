#include  <thread.h>
#include  <synch.h>

#include  "monitor.h"

static  int  c;                 //Contador estático
static  mutex_t  MonitorLock;   //Mutex

void  monitorInit(int  n){
    c = n;
    mutex_init(&MonitorLock, USYNC_THREAD, (void *) NULL);
}

/*
É necessário salvar imediatamente o valor do contador para evitar que outra 
thread no momento em que a função foi chamada faça uma operação no contador
 e assim faça que a função retorne um valor inesperado.
*/
int  counterInc(void){
    int  aux;

    mutex_lock(&MonitorLock);          
        aux = (++c);            
    mutex_unlock(&MonitorLock);        
    return  aux;                     
}

int  counterDec(void){
     int  aux;

    mutex_lock(&MonitorLock);
        aux = (--c);
    mutex_unlock(&MonitorLock);
    return  aux;
}

void  counterSet(int  n){
    mutex_lock(&MonitorLock);
    c = n;
    mutex_unlock(&MonitorLock);
}

//Por causa do uso de threads o valor retornado do contador não é confiável.
int  counterGet(void){
    int  aux;

    mutex_lock(&MonitorLock);
        aux = c;
    mutex_unlock(&MonitorLock);
    return  aux;
}