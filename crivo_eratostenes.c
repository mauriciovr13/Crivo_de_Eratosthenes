#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 3

#ifndef bool            /* se BOOLEAN não definido, então compila  */
    #define bool           /* evita uma redefinição para o tipo Boolean */
    typedef enum {FALSE, TRUE} Bool;
   #endif 

typedef struct {
    int k;
    Bool vetor[21];
}Gambiarra;

void *PrintHello(void *threadid) {
   long tid;
   tid = (long)threadid;
   //sleep(15);
   printf("Hello World! It's me, thread #%ld!\n", tid);
   pthread_exit(NULL);
}

void *crivo(void *gambi){
    Gambiarra *gb = (Gambiarra *)gambi;
    int kAux = gb->k * gb->k;
    while(kAux < 21) {
        for (int i = kAux; i < 21; i++) {
            gb->vetor[i] = (i % gb->k == 0 ? TRUE : FALSE);
        }
        for (int i = gb->k+1; i < 21; i++) {
            if(gb->vetor[i] == FALSE){
                gb->k = i;
                printf("%d", i);
                break;
            }
        }
    }
    pthread_exit(NULL);
}


int main (int argc, char *argv[]) {
    
    Gambiarra gambi;
    gambi.k = 2;
    
    for (int i = 2; i < 21; i++) {
        gambi.vetor[i] = FALSE;
    }
    
    //criando 3 threads
    pthread_t threads[NUM_THREADS];
    
    int rc;
    long t;
    for(t = 0; t < NUM_THREADS; t++){
        rc = pthread_create(&threads[t], NULL, crivo, (void *)&gambi);
        gambi.k += 2;
        //rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    
    for (int i = 0; i < 21; i++) {
        if(gambi.vetor[i] == FALSE) printf("Primos %d \n", i);  
        
    }
    
    
    pthread_exit(NULL);
}

 
