/////////////////////////////
//                         //
//  SISTEMAS OPERACIONAIS  //
//       TRABALHO 3        //
//                         //
//  Talles Siqueia Ceolin  //
//        201610108        //
//                         //
/////////////////////////////

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define LOTACAO_MAX 5
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"
#define COLOR_B_RED   "\x1b[1;31m"
#define COLOR_B_GREEN "\x1b[1;32m"

void* threadStart (void* arg) {

    int num_fichas = *((int *) arg);
    
    printf("%d", num_fichas);
    //free(arg);

	return 0;
}

int main(int argc, char const *argv[]){
    
    // Lê número de fichas através da linha de comando
    int num_fichas;
    sscanf (argv[1],"%d",&num_fichas);
    int *numFichasArg = (int*) malloc(sizeof(*numFichasArg));
    *numFichasArg = num_fichas;

    // cria thread do bolsista
    pthread_t bolsista_thread;
    pthread_create(&bolsista_thread, NULL, threadStart, numFichasArg);
   
    // Cria vetor de threads (fichas)
	pthread_t* fichas_threads = (pthread_t*) malloc(LOTACAO_MAX * sizeof(pthread_t));
	for (int i = 0; i < LOTACAO_MAX; i++)
		pthread_create(&fichas_threads[i], NULL, threadStart, numFichasArg);
	
    // join das threads
    pthread_join(bolsista_thread, NULL);
    for (int i = 0; i < LOTACAO_MAX; i++)		
		pthread_join(fichas_threads[i], NULL);

    return 0;
}

