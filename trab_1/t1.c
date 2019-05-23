/////////////////////////////
//                         //
//  SISTEMAS OPERACIONAIS  //
//       TRABALHO 1        //
//                         //
//  Talles Siqueia Ceolin  //
//        201610108        //
//                         //
/////////////////////////////

#include <stdio.h>
#include <stdbool.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAXCHAR 1000

int sorteiaLinha(int linhasMAX);
int contaLinhasBanco();
char* sortDica(int linhas);
void criaDicaDoDia(char* caminho, int linhas);
void distribuiDicas(char* caminho, int linhas, bool first);

// Seleciona uma linha aleatória
int sorteiaLinha(int linhasMAX){
    int random = rand() % linhasMAX;
    return random;
}

// Conta número de linhas(dicas) do banco de dicas
int contaLinhasBanco(){
    FILE* arq = NULL;
    char* arqNome = "banco_de_dicas.txt";
    arq = fopen(arqNome, "r");

    // Erro na leitura
    if (arq == NULL){
        printf("Não foi possível abrir %s", arqNome);
        exit(EXIT_FAILURE);
    }

    int linhas = 0;
    char str[MAXCHAR];
    while(fgets(str,MAXCHAR,arq) != NULL){
        linhas++;
    }
    fclose(arq);

    return linhas;
}

// Seleciona uma dica aleatória do banco de dicas
char* sortDica(int linhas){
    FILE* arq = NULL;
    char* arqNome = "banco_de_dicas.txt";
    arq = fopen(arqNome, "r");
    
    // Erro na leitura
    if (arq == NULL){
        printf("Não foi possível abrir %s", arqNome);
        exit(EXIT_FAILURE);
    }

    // Pega dica sorteada do banco e retorna como string(char*)
    char* dica = (char*) malloc(MAXCHAR*sizeof(char)); ;
    int linhaSorteada = sorteiaLinha(linhas); 
    int linhaAtual = 0;
    while(fgets(dica, MAXCHAR, arq) != NULL){
        if (linhaAtual == linhaSorteada){
            break;
        }
        linhaAtual++;
    }

    fclose(arq);

    return dica;
}

// Cria dica do dia a partir do caminho recebido
void criaDicaDoDia(char* caminho, int linhas){
    FILE* arq = NULL;

    // Concatena em uma string o caminho + nome do arquivo de dica
    char* dica = "/dica_do_dia.txt";
    char* name = malloc(strlen(caminho) + strlen(dica) + 200);
    strcpy(name, caminho);
    strcat(name, dica);

    // Erro na leitura
    arq = fopen(name, "w");
    if(arq == NULL){
        printf("Não foi possível criar o arquivo.\n");
        exit(EXIT_FAILURE);
    }

    // Escreve dica sorteada no arquivo
    fputs(sortDica(linhas), arq);
    fclose(arq);

    return;
}

/* Função principal onde navega os diretórios e chama as funções de 
criar dica do dia e fazer os prints de saída */
void distribuiDicas(char* caminho, int linhas, bool first){
    
    // Flag para printar apenas no início da primeira iteração
    if (first){
        printf("digraph G {\n");
    }

    DIR* dir;
    struct dirent* item;

    // Cria arquivo de dica
    criaDicaDoDia(caminho, linhas);

    // Prints dos PIDs
    int pid = getpid();
    int ppid = getppid();
    printf("\t %d -> %d;\n", ppid, pid);
    printf("\t %d [label=\"%s, %d\"];\n", pid, caminho, pid);

    // Verifica erro de abertura do diretório
    if (!(dir = opendir(caminho)))
        return;

    // Navegação pelos diretórios
    while ((item = readdir(dir)) != NULL) {    
        // Verifica se arquivo encontrado é uma pasta(diretório)
        if (item->d_type == DT_DIR) {
            // Verifica se pasta não é do sistema(oculta)
            if (strcmp(item->d_name, ".") == 0 || strcmp(item->d_name, "..") == 0){
                continue;
            } 
            // Escreve na string 'path' o caminho atual + diretório atual
            char path[1024];
            snprintf(path, sizeof(path), "%s/%s", caminho, item->d_name);
            // Chamada recursiva para navegar no diretório encontrado
            if (fork() == 0){
                distribuiDicas(path, linhas, false);
                return;
            }
        }
        wait(NULL);
    }
    closedir(dir);

    // Flag para printar "}" apenas no fim da primeira iteração
    if (first){
        printf("}\n");
    }

}

int main (void){
    srand(time(NULL));

    distribuiDicas("./home/estagiario", contaLinhasBanco(), true);

    return 0;
}