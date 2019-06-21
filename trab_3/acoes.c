#include "acoes.h"

// códigos para printfs coloridos
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_B_CYAN  "\x1b[1;36m"
#define COLOR_B_RED   "\x1b[1;31m"

// tempo em segundos entre os printfs
#define SLEEP_TIME 1

// bolsista entra no DCE
void entraBolsista(){
    sleep(SLEEP_TIME);
    printf(COLOR_B_RED "Bolsista: " COLOR_GREEN "Voltei. Vou trabalhar...\n");
}

// bolsista termina o trabalho e sai do DCE
void saiBolsista(){
    sleep(SLEEP_TIME);
    printf(COLOR_B_RED "Bolsista: " COLOR_GREEN "Terminei. Fechei a porta. Vou tomar um cafézinho e já volto...\n");
}


// verifica os documentos da ficha recebida
void verificaDocumentos(int ficha){
    sleep(SLEEP_TIME);
    printf(COLOR_B_RED "Bolsista: " COLOR_YELLOW "Verificando os documentos da ficha %d.\n", ficha);
}

// entrega a carteirinha da ficha recebida
void entregaCarteirinha(int ficha){
    sleep(SLEEP_TIME);
    printf(COLOR_B_RED "Bolsista: " COLOR_GREEN "Tudo certo com os documentos. Entregando a carteirinha da ficha %d.\n", ficha);
}

// nova ficha entra no DCE
void entraFicha(int ficha){
    sleep(SLEEP_TIME);
    printf(COLOR_B_CYAN "Ficha  %d: " COLOR_YELLOW "Entrei. Trouxe meus documentos.\n", ficha);
    printf(COLOR_B_CYAN "Ficha  %d: " COLOR_YELLOW "Vou esperar pela minha carteirinha...\n", ficha);
}

// aluno recebe carteirinha
void recebeCarteirinha(int ficha){
    sleep(SLEEP_TIME);
    printf(COLOR_B_CYAN "Ficha  %d: " COLOR_GREEN "Recebi minha carteirinha!\n", ficha);
}


