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
    sem_t sem_ficha; // semáforo de controle das fichas
} threadArg;

int numFichas; // número de fichas (passado pelo terminal)
int contadorFichas; // contador de quantas pessoas estão dentro do DCE
int fichasDentro[LOTACAO_MAX]; // vetor com os números das fichas que estão dentro do DCE
sem_t sem_dce;   // semáforo para esperar a sala encher 
sem_t sem_mutex; // semáforo para não usar o contadorFichas sem interferências  
threadArg* thread_args; // vetor de semáforo para controlar cada ficha

// função para ver se um valor está dentro do array
bool arrayContainValue(int val, int array[]){    
    for(int i = 0; i < LOTACAO_MAX; i++){
        if(array[i] == val)
            return true;
    }
    return  false;
}

// função da thread do bolsista
void* bolsista (void* arg) {

    while (true){
        
        sem_wait(&sem_dce); // espera entrar 5 fichas
        entraBolsista(); // bolsista entra, fecha a porta, ninguém mais entra

        for (int i = 0; i < LOTACAO_MAX; i++){
            int index = fichasDentro[i];                 // verifica quais números de ficha estão dentro do DCE
            verificaDocumentos(thread_args[index].id);
            entregaCarteirinha(thread_args[index].id);
            sem_post(&(thread_args[index].sem_ficha));   // libera ficha para receber carteirinha
        }
        
        saiBolsista(); // Bolsista sai e número de pessoa dentro do DCE zera
        contadorFichas = 0;

        sem_wait(&sem_mutex);
        for (int i = 0; i < numFichas; i++){
            if (arrayContainValue(thread_args[i].id,fichasDentro))  // verifica se não é uma das fichas já liberadas
                continue;
            sem_post(&(thread_args[i].sem_ficha));   // libera próximas fichas para entrarem
        }        
        sem_post(&sem_mutex);
        sleep(3);
    }
    
	return 0;
}

// função das threads das fichas(alunos)
void* aluno (void* arg) {
    // Recebe estrutura de argumentos
    threadArg* args = arg;
    int id = args->id;

    while (true){
        sem_wait(&sem_mutex);  // semáforo para controlar o contador de pessoas dentro
        if (contadorFichas >= LOTACAO_MAX){ // verifica se DCE já não está lotado
            sem_post(&sem_mutex);
            sem_wait(&(args->sem_ficha)); //      
        }else{
            entraFicha(id);                        
            fichasDentro[contadorFichas] = id;     
            contadorFichas++;                      
            if (contadorFichas < LOTACAO_MAX){
                sem_post(&sem_mutex); 
            }else if (contadorFichas == LOTACAO_MAX){
                sem_post(&sem_dce); // avisa que DCE está cheio
                sem_post(&sem_mutex);    
            }

            sem_wait(&(args->sem_ficha));
            recebeCarteirinha(id);
        }  
    }   

	return 0;
}


int main(int argc, char const *argv[]){
    
     // Lê número de fichas através da linha de comando e guarda em variável global
    sscanf (argv[1],"%d",&numFichas);
    contadorFichas = 0; // inicializa contador

    thread_args = (threadArg*) malloc(numFichas * sizeof(threadArg));

    // Inicia os semáforos
    sem_init(&sem_dce, 0, 0);
    sem_init(&sem_mutex, 0, 1);
    for (int i = 0; i < numFichas; i++){
        thread_args[i].id = i;
        sem_init(&(thread_args[i].sem_ficha), 0, 0);
    }
   

    // Cria thread do bolsista
    pthread_t bolsista_thread;
    pthread_create(&bolsista_thread, NULL, bolsista, NULL);

    // Cria vetor de threads (fichas) e de argumentos
	pthread_t* fichas_threads = (pthread_t*) malloc(numFichas * sizeof(pthread_t));
	for (int i = 0; i < numFichas; i++){
		pthread_create(&fichas_threads[i], NULL, aluno, &thread_args[i]);
    }
	
    // Join das threads
    pthread_join(bolsista_thread, NULL);
    for (int i = 0; i < numFichas; i++)		
		pthread_join(fichas_threads[i], NULL);

    return 0;
}

