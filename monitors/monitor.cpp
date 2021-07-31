#include  <thread.h>
#include  <synch.h>

#include  "monitor.h"

static  int  count;             //Contador estático
static  mutex_t  MonitorLock;   //Mutex

void  monitorInit(int  n){
     count = n;
     mutex_init(&MonitorLock, USYNC_THREAD, (void *) NULL);
}

int  counterInc(void){
     int  value;

     mutex_lock(&MonitorLock);          
          value = (++count);            
     mutex_unlock(&MonitorLock);        
     return  value;                     
}

int  counterDec(void){
     int  value;

     mutex_lock(&MonitorLock);
          value = (--count);
     mutex_unlock(&MonitorLock);
     return  value;
}

void  counterSet(int  n){
     mutex_lock(&MonitorLock);
          count = n;
     mutex_unlock(&MonitorLock);
}

//Por causa do uso de threads o valor retornado do contador não é confiável.
int  counterGet(void){
     int  value;

     mutex_lock(&MonitorLock);
          value = count;
     mutex_unlock(&MonitorLock);
     return  value;
}