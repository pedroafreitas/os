/*
---------------------------->>> Simulando um Monitor <<<----------------------------
Para simular um monitor precisamos levar em consideração três questões principais:

    1. Como garantir que as váriaveis locais não serão acessadas por outros procedimentos
fora do monitor?
    2. Como garantir que o usuário pode apenas acessar a interface sem conhecer os 
detalhes do monitor?
    3. Como consturir os limites do monitor para que MUTEX possa acontecer?

Para solucionarmos esses problemas vamos utilizar dois arquivos: um header para 
guardar os protótipos do monitor e um arquivo de implementação. Ao implementar o
monitor é preciso declarar suas variáveis como static. Também precisaremos usar o
lock do muter para limitá-lo.

Nosso monitor vai manter um contador, cujo valor pode ser incrementado ou decrementado
e transformado. Teremos uma função para inicialização e de recuperação do valor do contador.

No arquivo monitor.h encontram-se os protótipos dessas funções.

No arquivo monitor.c encontram-se as funções do monitor e suas variáveis internas.

Para garantir que apenas uma thread por executar qualquer função do monitor faremos:

    1. Executar mutex_lock();
    2. Executar procedimentos da função;
    3. Executar mutex_unlock();

No arquivo main.c primeiro inicializa-se o monitor com monitorInit(0) - o contador é 
inicializado com 0. Realiza-se dois locks no mutex para proteger a variável Access, a
qual permite que o número gerado aleatoriamente seja acessado pelo mutex.

    1. Cada thread de "aAumenta", incrementa o valor do contador REPS vezes. 
    2. Cada thread de "Diminui", incrementa o valor do contador REPS vezes. 
    3. Cada thread de "Troca",  muda o valor do contador REPS/2.
    4. Cada thread de "Exibe", imprime o valor do contador REPS/2 vezes.

Todos esses processo possuem o mesmo número de threads.

O objetivo do programa é sincronizar as quatro operações sobre o contador

---------------------------->>> Simulando um Monitor <<<----------------------------
*/

#include  <stdio.h>
#include  <time.h>
#include  <stdlib.h>
#include  <pthread.h>

#include  "monitor.h"

#define   REPS         40
#define   INC           5
#define   DEC           4
#define   THREADS       3

pthread_mutex_t   Access;                       
pthread_mutex_t   RandNumber;                 


void  *Aumenta(void *voidPTR){
     int  *intPTR = (int *) voidPTR;
     int  ID      = *intPTR;
     int  value, i;

     for (i = 0; i < REPS; i++) {  
          sched_yield();                  //espara um pouco
          value = counterInc();                
          pthread_mutex_lock(&Access);          
               printf("   (%d): Contador aumentou"
                      "(value = %d)\n", ID, value);
          pthread_mutex_unlock(&Access);
     }
     pthread_exit(NULL);
}

void  *Diminui(void *voidPTR)
{
     int  *intPTR = (int *) voidPTR;
     int  ID      = *intPTR;
     int  value, i;

     for (i = 0; i < REPS; i++) {
          sched_yield();
          value = counterDec();
          pthread_mutex_lock(&Access);
               printf("   (%d): Contador diminuiu"
                      "(value = %d)\n", ID, value);
          pthread_mutex_unlock(&Access);
     }
     pthread_exit(NULL);
}

void  *Troca(void *voidPTR)
{
     int  *intPTR = (int *) voidPTR;
     int  ID      = *intPTR;
     int  value, i;

     for (i = 0; i < REPS/2; i++) {
          sched_yield();
          pthread_mutex_lock(&RandNumber);
               value = rand() % INC;
          pthread_mutex_unlock(&RandNumber);
          counterSet(value);
          pthread_mutex_lock(&Access);
               printf("*** (%d): Trocou para: %d ***\n",
                      ID, value);
          pthread_mutex_unlock(&Access);
     }
     pthread_exit(NULL);
}

void  *Exibe(void *voidPTR)
{
     int  *intPTR = (int *) voidPTR;
     int  ID      = *intPTR;
     int  value, i;

     for (i = 0; i < REPS/2; i++) {
          sched_yield();
          value = counterGet();
          pthread_mutex_lock(&Access);
               printf("### (%d): Contador: %d ###\n",
                      ID, value);
          pthread_mutex_unlock(&Access);
     }
     pthread_exit(NULL);
}


int  main(){
     pthread_t  incID[THREADS], decID[THREADS];
     pthread_t  ResetID, DisplayID;
     size_t    incStatus[THREADS], decStatus[THREADS];
     size_t    ResetStatus, DisplayStatus;
     int       incArg[THREADS], decArg[THREADS];
     int       ResetArg, DisplayArg;
     int       i;
     
     srand((unsigned) time(NULL));

     pthread_mutex_init(&Access, NULL);
     pthread_mutex_init(&RandNumber, NULL);
     monitorInit(0);

     ResetArg = 0;
     pthread_create(NULL, 0, Troca,  (void *) &ResetArg,
                0,  &ResetID);
     DisplayArg = 1;
     pthread_create(NULL, Exibe,  &DisplayArg,
                0,  &DisplayID);

     for (i = 0; i < THREADS; i++) {
          incArg[i] = i + 2;
          decArg[i] = incArg[i] + THREADS;
          pthread_create(NULL, Aumenta, &(incArg[i]),
                     0,  &(incID[i]));
          pthread_create(NULL, Diminui, &(decArg[i]),
                     0, &(decID[i]));
     }

     for (i = 0; i < THREADS; i++) {
          pthread_join(incID[i], &(incStatus[i]));
          pthread_join(decID[i], &(decStatus[i]));
     }
     pthread_join(ResetID, &ResetStatus);
     pthread_join(DisplayID, &DisplayStatus);

     printf("Parent exits ...\n");

     return 0;
}