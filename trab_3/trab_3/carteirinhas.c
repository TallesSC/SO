/////////////////////////////
//                         //
//  SISTEMAS OPERACIONAIS  //
//       TRABALHO 3        //
//                         //
//  Talles Siqueia Ceolin  //
//        201610108        //
//                         //
/////////////////////////////
// compilar com "make"
// executar com ./carteirinhas "número de fichas"

#include "acoes.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h> 

#define LOTACAO_MAX 5
int numFichas;
typedef int semaphore;
semaphore full = 0;     
semaphore empty = LOTACAO_MAX;
semaphore mutex = 1;

// estrutura de argumento das threads
typedef struct ThreadArg {
	int id;
} threadArg;

void* bolsista (void* arg) {

	return 0;
}

void* aluno (void* arg) {
    // Recebe estrutura de argumentos
    threadArg* args = arg;
    int id = args->id;

	return 0;
}

int main(int argc, char const *argv[]){
    
    // Lê número de fichas através da linha de comando e guarda em variável global
    sscanf (argv[1],"%d",&numFichas);
   
    // Cria vetor de threads (fichas) e de argumentos
	pthread_t* fichas_threads = (pthread_t*) malloc(LOTACAO_MAX * sizeof(pthread_t));
    threadArg* threadArgs = (threadArg*) malloc(LOTACAO_MAX * sizeof(threadArg));
	for (int i = 0; i < LOTACAO_MAX; i++){
        threadArgs[i].id = i + 1;
		pthread_create(&fichas_threads[i], NULL, aluno, &threadArgs[i]);
    }

    // Cria thread do bolsista
    pthread_t bolsista_thread;
    pthread_create(&bolsista_thread, NULL, bolsista, NULL);
	
    // Join das threads
    pthread_join(bolsista_thread, NULL);
    for (int i = 0; i < LOTACAO_MAX; i++)		
		pthread_join(fichas_threads[i], NULL);

    return 0;
}

