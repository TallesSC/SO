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
// executar com "./carteirinhas ~número_de_fichas~"

#include "acoes.h"
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>

#define LOTACAO_MAX 5

// estrutura de argumento das threads
typedef struct ThreadArg {
	int id; // número da ficha
    sem_t sem_fichas; // semáforo de controle das fichas
} threadArg;

int numFichas; // número de fichas (passado pelo terminal)
int contadorFichas; // contador para trocar as fichas
sem_t sem_dce;   // semáforo para esperar a sala encher 
threadArg thread_args[LOTACAO_MAX]; // vetor de semáforo para controlar cada ficha

// troca o número das fichas
void trocaFichas(){
    for (int i = 0; i < LOTACAO_MAX; i++){ 
        contadorFichas++;
        if (contadorFichas >= numFichas)
            contadorFichas = 1;
        thread_args[i].id = contadorFichas;
    }    
}

void* bolsista (void* arg) {
    
    while (true){
        sem_wait(&sem_dce); // espera entrar 5 fichas
        entraBolsista(); // bolsista entra, fecha a porta, ninguém mais entra
        for (int i = 0; i < LOTACAO_MAX; i++){ // faz a carteirinhna das 5 fichas presentes
            verificaDocumentos(thread_args[i].id);
            entregaCarteirinha(thread_args[i].id);
            sem_post(&(thread_args[i].sem_fichas)); // libera ficha para receber carteirinha
        }
        saiBolsista(); // bolsista encerra
        trocaFichas();        
        for (int i = 0; i < LOTACAO_MAX; i++) // libera a entrada de novos alunos 
            sem_post(&(thread_args[i].sem_fichas));            
    }
    
	return 0;
}

void* aluno (void* arg) {
    // Recebe estrutura de argumentos
    threadArg* args = arg;
    int id = args->id;
    int index;

    while (true){
        entraFicha(id);
        sem_post(&sem_dce); // avisa que entrou mais uma ficha
        for (int i = 0; i < LOTACAO_MAX; i++){
            if (thread_args[i].id == id){
               sem_wait(&(thread_args[i].sem_fichas)); // espera bolsista liberar a carteirinha
               index = i;
               recebeCarteirinha(id);
            }
        }
        sem_wait(&(thread_args[index].sem_fichas)); // espera bolsista fazer todas carteirinhas para sair
        id = thread_args[index].id;
    }   
    

	return 0;
}


int main(int argc, char const *argv[]){
    
     // Lê número de fichas através da linha de comando e guarda em variável global
    sscanf (argv[1],"%d",&numFichas);
    contadorFichas = 1; // inicializa contador

    // Inicia os semáforos
    sem_init(&sem_dce, 0, LOTACAO_MAX);
    for (int i = 0; i < LOTACAO_MAX; i++){
        thread_args[i].id = i + 1;
        contadorFichas++;
        sem_init(&(thread_args[i].sem_fichas), 0, 0);
    }
   
    // Cria thread do bolsista
    pthread_t bolsista_thread;
    pthread_create(&bolsista_thread, NULL, bolsista, NULL);

    // Cria vetor de threads (fichas) e de argumentos
	pthread_t* fichas_threads = (pthread_t*) malloc(LOTACAO_MAX * sizeof(pthread_t));
	for (int i = 0; i < LOTACAO_MAX; i++){
		pthread_create(&fichas_threads[i], NULL, aluno, &thread_args[i]);
    }
	
    // Join das threads
    pthread_join(bolsista_thread, NULL);
    for (int i = 0; i < LOTACAO_MAX; i++)		
		pthread_join(fichas_threads[i], NULL);

    return 0;
}

