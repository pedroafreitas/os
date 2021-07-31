/*

>>Semáforo Binário

A ideia do monitor é emular um semaforo binário.

1 = recurso disponível
0 = alguém usa o recurso

Se tiver mais de um recurso tentando entrar, espera
a variável ser diferente de 0 para pegar o recursos.

A integridade é garantida pelo monitor. Não é possível
modificar as variáveis internas do monitor diretamente.
É necessário chamar procedimentos.

--->>> O controle é dentro do monitor. É um ponto comum! <<<---
*/


/*
s = semáforo {

    s.queue = fila de tarefas
    s.counter = contador inteiro
}

down(s) - decrementa s.counter. Se s.counter negativo a tarefa 
solicitante solicitante é add à s.queue e sustepnsa. Se 
s.counter positivo retorna e a tarefa continua.

up(s) - incrementar s.counter. s.counter negativo ou nula 
indica tarefas suspensas. A primeira tarefa de s.queue é 
devolvida à fila de tarefas prontas.
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 100
#define NUM_STEPS 100000

int sum = 0;
pthread_mutex_t mutex; //Mutex criado

void *threadBody(void *id){
    int i;

    for(i = 0; i < NUM_STEPS; i++){
        pthread_mutex_lock (&mutex); //lock mutex
        sum += 1; //incremento
        pthread_mutex_unlock (&mutex);
    }

    pthread_exit(NULL);
}

int main (int argc, char *argv[]){
    pthread_t thread [NUM_THREADS];
    pthread_attr_t attr;
    long i, status;

    pthread_mutex_init (&mutex, NULL); //mutex livre por default

    pthread_attr_init (&attr);
    pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_JOINABLE);
    
    //CRIANDO THREADS
    for (i = 0; i < NUM_THREADS; i++){
        status = pthread_create (&thread[i], &attr, threadBody, (void *) i);
        if (status){
            perror ("ptread_create");
            exit(1);
        }
    }

    //Espera até as treads terminarem
    for (i = 0; i < NUM_THREADS; i++){
        status = pthread_join(thread[i], NULL);
        if (status){
            perror("pthread_join");
            exit(1);
        }
    }

    printf("Soma deveria ser %d e é %d\n", NUM_THREADS*NUM_STEPS, sum);


    pthread_attr_destroy (&attr);
    pthread_exit(NULL);
     
}