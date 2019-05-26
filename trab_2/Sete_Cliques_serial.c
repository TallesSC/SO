/////////////////////////////
//                         //
//  SISTEMAS OPERACIONAIS  //
//       TRABALHO 2        //
//                         //
//  Talles Siqueia Ceolin  //
//        201610108        //
//                         //
/////////////////////////////
// versão serial 

#include "curl_code.h"
#include <stdbool.h>
#include <string.h>

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


// printa página que está acessando
void printPaginaAtual(int cliqueAtual,  char* url){
	if (cliqueAtual == 0){
		printf(COLOR_YELLOW "Link Inicial:" COLOR_CYAN " Acessando página →  %s\n" COLOR_RESET, url);
	}else{
		printf(COLOR_YELLOW "     %dº Link:" COLOR_CYAN " Acessando página →  %s\n" COLOR_RESET, cliqueAtual, url);
	}
	return;
}

// printa mensagem de game-over
void printPerdeuJogo(){
	printf(COLOR_B_RED "A palavra não foi encontrada, número máximo de cliques foi atingido!\n" COLOR_RESET);	
	return;
}

// printa mensagem de jogo vencido
void printGanhouJogo(char* palavraProcurada, int cliqueAtual){
	printf(COLOR_B_GREEN "Encontrou a palavra %s após %d cliques!\n" COLOR_RESET, palavraProcurada, cliqueAtual);
	return;
}


// verifica se palavra desejada está na página
bool encontrouPalavra(char* page_content, char* palavraProcurada){
	return strstr(page_content, palavraProcurada) != NULL;
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

bool seteCliques(char* url, char* palavraProcurada, int cliquesRestantes){
	
	// controla número máximo de cliques
	if (cliquesRestantes < 0){
		printPerdeuJogo();
		return false;
	}

	// print para visualizar quais páginas está acessando
	int cliqueAtual = MAX_CLIQUES - cliquesRestantes;
	printPaginaAtual(cliqueAtual, url);

	// page_content recebe o conteudo da pagina a partir do url
	CURL *curl_handle;
	char *page_content = download_page(curl_handle, url);

	// verifica se palavra desejada está na página
	if(encontrouPalavra(page_content, palavraProcurada)){
		printGanhouJogo(palavraProcurada, cliqueAtual);
		return true;
	}else{

		// links: lista de links lidos. A funcao find_links ira tentar ler 50 links dentro da pagina.
		int links_readed;
		char **links = find_links(curl_handle, page_content, 50, &links_readed);
		
		// Verifica se o link sorteado não é exterior ao wikipedia
		int random;
		do{
			random = rand() % links_readed;
		}while (paginaInvalida(links[random]));
		
		// acessa um link e repete a função
		return seteCliques(links[random], palavraProcurada, cliquesRestantes - 1);
	}
}

int main(void){
	clock_t inicio = clock();
	srand(time(NULL));

	// Define a palavra a ser procurada
	char palavraProcurada[TAMANHO_MAX];
	printf(COLOR_B_GREEN "Qual palavra deseja procurar? (Ex: Apple)\n\t" COLOR_RESET);
	scanf("%s", palavraProcurada);

	bool ganhou;
	do{
		printf(COLOR_MAGENTA "Começando um novo jogo com a palavra %s\n" COLOR_RESET, palavraProcurada);
		ganhou = seteCliques("https://pt.wikipedia.org/wiki/Sistema_operativo", palavraProcurada, MAX_CLIQUES);
	}while(!ganhou);

	curl_global_cleanup();
	
	// mostra tempo decorrido no programa
	clock_t fim = clock();
	float tempo = ((fim - inicio) * 1000) / CLOCKS_PER_SEC;
	printf("Fim de jogo! Tempo decorrido: %f", tempo);
	
	return 0;
}
