#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 3
#define TAM_VETOR 20

#ifndef bool            /* se BOOLEAN não definido, então compila  */
    #define bool           /* evita uma redefinição para o tipo Boolean */
    typedef enum {FALSE, TRUE} Bool;
   #endif 

Bool vetor[TAM_VETOR];


void *crivo(void *k){
    long kAux = (long)k;
    long kQuad = kAux * kAux;
    while(kQuad < 21) {
        for (int i = kQuad; i < TAM_VETOR; i++) {

            //vetor[i] = (i % k == 0 ? TRUE : FALSE);
            if (vetor[i] || i % kAux == 0){
                vetor[i] = TRUE;
            }
        }
        for (int i = kAux+1; i < TAM_VETOR; i++) {
            if(!vetor[i]){
                kAux = i;
                break;
            }
        }
        kQuad = kAux*kAux;
    }
    pthread_exit(NULL);
}


int main (int argc, char *argv[]) {
    
    for (int i = 2; i < TAM_VETOR; i++) {
        vetor[i] = FALSE;
    }

    long k = 2;
    
    //criando 3 threads
    pthread_t threads[NUM_THREADS];
    
    int rc;
    for(int t = 0; t < NUM_THREADS; t++){
        rc = pthread_create(&threads[t], NULL, crivo, (void *)k);
        k += 2;
        //rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    for (int i = 0; i < NUM_THREADS; i++){
        pthread_join(threads[i], NULL);
    }
    
    printf("Primos:\n");
    for (int i = 2; i < TAM_VETOR; i++) {
        if(!vetor[i]) printf("%d \n", i);  
        
    }
 
    pthread_exit(NULL);
}

 
