# Trabalho 2 - Sistemas Operacionais A (ELC1080)

#### Dúvidas: bdalves@inf.ufsm.br (e-mail do monitor).
Obs.: Leia a descrição do trabalho e tente implementar o mesmo antes de entrar em contato com o monitor.

## Motivação:

O Gugacast é um programa onde convidados (e às vezes os ouvintes) contam histórias épicas da sua vida. Pode ser uma história engraçada, inusitada, com finais felizes, tristes… Aquele tipo de história que você conta em uma festa e vai aperfeiçoando ao longo dos anos. 

O programa é sempre dividido em atos, dentre estes atos, o primeiro é utilizado para os jogos e para as análises musicais do Rafael e o segundo para as histórias dos convidados ou e-mails dos ouvintes.
Fonte: https://wiki.gugacast.com/P%C3%A1gina_principal

Dentre os jogos criados pelo programa, existe um chamado de SETE CLIQUES PARA AS ESTRELAS. As regras para este jogo são as seguintes: O participante tem que sair de uma página específica da Wikipédia em português e chegar em outra página que contenha uma palavra específica com apenas sete cliques em links internos. Não vale voltar página ou usar links que vão para fora da Wikipédia.


#### Exemplo: 

Página de saída: Sistemas Operativos → https://pt.wikipedia.org/wiki/Sistema_operativo.
Palavra que deve ser encontrada: Sport Club Internacional.

Primeiro link: Bill Gates na página de Sistemas Operativos→ https://pt.wikipedia.org/wiki/Bill_Gates.
Segundo link: Movimento Escoteiro na página do Bill Gates→ https://pt.wikipedia.org/wiki/Escotismo.
Terceiro link: Ano de 1909 na página do Movimento Escoteiro→ https://pt.wikipedia.org/wiki/Escotismo.
Quarto link: Sport Club Internacional na página do Ano de 1909→ https://pt.wikipedia.org/wiki/Escotismo.

Sim, é possível chegar ao Inter através da página de Sistemas Operativos em menos de 7 cliques. É por razões inacreditáveis como essa que esse jogo é tão engraçado. 

	

## Descrição do trabalho


**Objetivo:** Crie um programa em C capaz de jogar o sete cliques para as estrelas. Seu programa deve utilizar threads para acessar múltiplas páginas do Wikipedia.

1. Inclua no programa Sete_Cliques.c (disponível em: https://github.com/Alves-Bruno/Trabalhos_ELC1080/tree/master/trab_2) uma função capaz de jogar o sete cliques para estrelas. Essa função deve acessar a página inicial, verificar se a palavra procurada se encontra na página. Se a palavra não estiver na página, um dos links internos é sorteado e outra página é acessada, a função deve fazer no máximo 7 acessos. Caso a palavra seja encontrada, a função retorna true. Compile o programa com o comando make. Talvez seja necessário instalar a biblioteca liburl, para isso, faça o comando: apt-get install libcurl4-gnutls-dev.

2. Utilize as funções download_page e find_links. Você pode fazer alterações nas mesmas, caso necessite.

3. Dica: utilize a função strstr para procurar uma palavra no conteúdo da página. Descrição da função: http://www.cplusplus.com/reference/cstring/strstr/

4. Faça com que seu programa teste vários caminhos diferentes para tentar uma solução, ou seja, faça com que o programa jogue várias vezes.

5. Utilize threads para melhorar o desempenho do programa. Sinta-se livre para escolher a melhor estratégia.

6. Crie dois programas: Sete_Cliques_serial.c e Sete_Cliques_threads.c. Faça uma comparação de desempenho entre as duas estratégias. Teste o desempenho do programa com 1, 2, 4 e 8 threads. Faça a medição dos tempos e calcule as médias dos mesmos (10 execuções para cada caso no mínimo). Dica: Faça com que seu programa Sete_Cliques_threads receba como argumento o número de threads que serão utilizadas.

7. Faça um relatório simples dos tempos encontrados. Utilize gráficos  e descreva o hardware utilizado e cenários testados.

8. Entregue uma pasta (trab2_nome_aluno.zip) com os códigos modificados e o relatório em formato PDF.






