#ifndef MONITOR_DOT_H
#define MONITOR_DOT_H

void  monitorInit(int  n);              //Inicialização
int   counterInc(void);                 //Incrementa contador      
int   counterDec(void);                 //Decrementa contador      
void  counterSet(int  n);               //Muda o contador para n    
int   counterGet(void);                 //Pega valor do contador       

#endif