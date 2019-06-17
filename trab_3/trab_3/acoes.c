#include "acoes.h"

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"
#define COLOR_B_RED   "\x1b[1;31m"
#define COLOR_B_GREEN "\x1b[1;32m"


// bolsista entra no DCE
void entraBolsista(){
    printf(COLOR_B_RED "Bolsista: " COLOR_YELLOW "Voltei. Vou trabalhar...\n");
}

// bolsista termina o trabalho e sai do DCE
void saiBolsista(){
    printf(COLOR_B_RED "Bolsista: " COLOR_GREEN "Terminei. Fechei a porta. Vou tomar um cafézinho e já volto...\n");
}

// verifica os documentos da ficha recebida
void verificaDocumentos(int ficha){
    printf(COLOR_B_RED "Bolsista: " COLOR_YELLOW "Verificando os documentos da ficha %d.\n", ficha);
}

// entrega a carteirinha da ficha recebida
void entregaCarteirinha(int ficha){
    printf(COLOR_B_RED "Bolsista: " COLOR_GREEN "Tudo certo com os documentos. Entregando a carteirinha da ficha %d.\n", ficha);
}

// nova ficha entra no DCE
void entraFicha(int ficha){
    printf(COLOR_B_RED "Ficha %d: " COLOR_YELLOW "Entrei. Trouxe meus documentos.\n", ficha);
    printf(COLOR_B_RED "Ficha %d: " COLOR_YELLOW "Vou esperar pela minha carteirinha...\n", ficha);
}

void recebeCarteirinha(int ficha){
    printf(COLOR_B_RED "Ficha %d: " COLOR_YELLOW "Recebi minha carteirinha!\n", ficha);
}


