/////////////////////////////
//                         //
//  SISTEMAS OPERACIONAIS  //
//       TRABALHO 2        //
//                         //
//  Talles Siqueia Ceolin  //
//        201610108        //
//                         //
/////////////////////////////
// versão com threads

#include "curl_code.h"
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

#define MAX_CLIQUES 7
#define TAMANHO_MAX 256 
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"
#define COLOR_B_RED   "\x1b[1;31m"
#define COLOR_B_GREEN "\x1b[1;32m"

// estrutura dos argumentos da thread
typedef struct ThreadArg {
	int id;
	char* paginaInicial;
	char* palavraProcurada;
} threadArg;

// printa página que está acessando
void printPaginaAtual(int threadID, int cliqueAtual,  char* url){
	if (cliqueAtual == 0){
		printf(COLOR_MAGENTA "Thread %d → " COLOR_YELLOW "Link Inicial:" COLOR_CYAN " Acessando página →  %s\n" COLOR_RESET, threadID, url);
	}else{
		printf(COLOR_MAGENTA "Thread %d → " COLOR_YELLOW "     %dº Link:" COLOR_CYAN " Acessando página →  %s\n" COLOR_RESET, threadID, cliqueAtual, url);
	}
	return;
}

// printa mensagem de game-over
void printPerdeuJogo(int threadID){
	printf(COLOR_MAGENTA "Thread %d → " COLOR_B_RED " A palavra não foi encontrada, número máximo de cliques foi atingido!\n" COLOR_RESET, threadID);	
	return;
}

// printa mensagem de jogo vencido
void printGanhouJogo(int threadID, char* palavraProcurada, int cliqueAtual){
	if (cliqueAtual == 1){
		printf(COLOR_MAGENTA "Thread %d → " COLOR_B_GREEN " Encontrou a palavra %s após %d clique!\n" COLOR_RESET, threadID, palavraProcurada, cliqueAtual);
	}else{
		printf(COLOR_MAGENTA "Thread %d → " COLOR_B_GREEN " Encontrou a palavra %s após %d cliques!\n" COLOR_RESET, threadID, palavraProcurada, cliqueAtual);
	}
	return;
}

// verifica se link direciona para fora da wikipedia ou para uma imagem
bool paginaInvalida(char* url){
	if(strstr(url, "https://pt.wikipedia.org/wiki/") == NULL){
		return true;
	}else if (strstr(url, ".svg") != NULL){
		return true;
	}else if (strstr(url, ".png") != NULL){
		return true;
	}else if (strstr(url, ".jpeg") != NULL){
		return true;
	}
	return false;
}

// verifica se palavra desejada está na página
bool encontrouPalavra(char* page_content, char* palavraProcurada){
	return strstr(page_content, palavraProcurada) != NULL;
}

void* seteCliques(char* url, char* palavraProcurada, int cliquesRestantes, int threadID){
	
	// controla número máximo de cliques
	if (cliquesRestantes < 0){
		printPerdeuJogo(threadID);
		return 0;
	}

	// print para visualizar quais páginas está acessando
	int cliqueAtual = MAX_CLIQUES - cliquesRestantes;
	printPaginaAtual(threadID, cliqueAtual, url);
	
	// page_content recebe o conteudo da pagina a partir do url
	CURL *curl_handle;
	char *page_content = download_page(curl_handle, url);
	
	// verifica se palavra desejada está na página
	if(encontrouPalavra(page_content, palavraProcurada)){
		printGanhouJogo(threadID, palavraProcurada, cliqueAtual);
		return 0;
	}else{
		
		// links: lista de links lidos. A funcao find_links ira tentar ler 50 links dentro da pagina.
		int links_readed;
		char **links = find_links(curl_handle, page_content, 50, &links_readed);
		
		// Verifica se o link sorteado não é exterior ao wikipedia
		int random;
		do{
			random = rand() % links_readed;
		}while (paginaInvalida(links[random]));		
		
		// acessa um link sorteado e repete a função
		seteCliques(links[random], palavraProcurada, cliquesRestantes - 1, threadID);
	}
}

void* threadStart (void* arg) {
	// Recebe argumentos da thread
	threadArg* input = arg;
	int id = input->id;
	char* paginaInicial = input->paginaInicial;
	char* palavraProcurada = input->palavraProcurada;
	
	// Função recursiva principal do jogo
	seteCliques(paginaInicial, palavraProcurada, MAX_CLIQUES, id);
	
	return 0;
}

int main(void){

	srand(time(NULL));

	// Define número de threads de acordo com o usuário
	int nThreads;
	printf(COLOR_B_GREEN "Quantas threads o jogo deve utilizar?\n\t" COLOR_RESET);
	scanf("%d", &nThreads);

	// Define a palavra a ser procurada
	char palavra[TAMANHO_MAX];
	printf(COLOR_B_GREEN "Qual palavra deseja procurar? (Ex: Apple)\n\t" COLOR_RESET);
	scanf("%s", palavra);
	
	// inicio do temporizador
	clock_t inicio = clock();
	
	// Cria vetor de threads e vetor de argumentos (usado para definir um índice para cada thread)
	pthread_t* threadArray = (pthread_t*) malloc(nThreads * sizeof(pthread_t));
	threadArg* args = (threadArg*) malloc(nThreads * sizeof(threadArg));
	for (int i = 0; i < nThreads; i++){
		args[i].id = i + 1;
		args[i].paginaInicial = "https://pt.wikipedia.org/wiki/Sistema_operativo";
		args[i].palavraProcurada = palavra;
		pthread_create(&threadArray[i], NULL, threadStart, &args[i]);
	}
		
	// Espera todas threads
	for (int i = 0; i < nThreads; i++){		
		pthread_join(threadArray[i], NULL);
	}
	
	// Limpeza da bibioteca curl
	curl_global_cleanup();
	
	// mostra tempo decorrido no programa
	clock_t fim = clock();
	double tempo = ((double) (fim - inicio)) / CLOCKS_PER_SEC;
	printf("Fim de jogo! Tempo decorrido: %f\n", tempo);
	
	return 0;
}
