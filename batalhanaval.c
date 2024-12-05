//feito por leandra, joao pedro, karem, rafaela, gabriela, lucas

#include <stdio.h>
#include <string.h>

#define TAMANHO_CAMPO 5
#define TAMANHO_STRING 20

char nome_jogador_1[TAMANHO_STRING];
char nome_jogador_2[TAMANHO_STRING];
int campo_jogador_1[TAMANHO_CAMPO][TAMANHO_CAMPO];
int campo_jogador_2[TAMANHO_CAMPO][TAMANHO_CAMPO];
int pontuacao_jogador_1 = 0;
int pontuacao_jogador_2 = 0;

//////////////////////////////////////////////////////////

void inicializarCampo(int campo[TAMANHO_CAMPO][TAMANHO_CAMPO]) {
    for (int i = 0; i < TAMANHO_CAMPO; i++) {
        for (int j = 0; j < TAMANHO_CAMPO; j++) {
            campo[i][j] = 0;
        }
    }
}

//////////////////////////////////////////////////////////

void nomeador(char nome_jogador[]) {
    printf("Informe o nome do jogador: ");
    fgets(nome_jogador, TAMANHO_STRING, stdin);
    nome_jogador[strcspn(nome_jogador, "\n")] = '\0'; // Remove o '\n' no final do nome
}

//////////////////////////////////////////////////////////

/* dentro dessa função, é feita a inclusão de barcos dentro da matriz, os valores vão de 1 a 4, a função utiliza constantes pré definidas
para manipulação dos valores*/
int selecionarbarcos(int campo_jogador[TAMANHO_CAMPO][TAMANHO_CAMPO], char nome_jogador[TAMANHO_STRING]) { 
    int x;
    int y;
    int contador = 4;
    int contador_de_vida = 1;

    for (int k = 0; k < contador; k++) {
        printf("\n%s, digite o local do barco de valor %d, uma linha e uma coluna:\n", nome_jogador, contador_de_vida);
        printf("Linha: ");
        scanf("%d", &x);
        printf("Coluna: ");
        scanf("%d", &y);
        
        while (x < 0 || x >= TAMANHO_CAMPO || y < 0 || y >= TAMANHO_CAMPO) {
            printf("\nCoordenadas invalidas! Tente novamente (0 a %d para x e y): \n", TAMANHO_CAMPO - 1);
            printf("Linha: ");
            scanf("%d", &x);
            printf("Coluna: ");
            scanf("%d", &y);
        }
        
        while (campo_jogador[x][y] != 0) {
            printf("\nEste local já está ocupado, tente novamente.\n");
            printf("Linha: ");
            scanf("%d", &x);
            printf("Coluna: ");
            scanf("%d", &y);
        }
        
        /* o primeiro for, tem função de inserir os barcos de forma, contabilizando a quantidade de barcos e a sua respectiva vida,
        o primeiro while tem foco em comparação, onde ele compara as variáveis x e y, se forem maiores que zero ou maiores/iguais ao
        tamanho máximo do campo, será informado como invalidas as coordenadas, já o segundo impede que sejam posicionados dois barcos na
        mesma coordenada*/

        campo_jogador[x][y] = contador_de_vida;
        contador_de_vida++;
    }
    
    return 0;
}

//////////////////////////////////////////////////////////

int validaJogada(char nome_jogador[TAMANHO_STRING], char nome_inimigo[TAMANHO_STRING], int campo_inimigo[TAMANHO_CAMPO][TAMANHO_CAMPO], int pontuacao_jogador) {
    int x, y;
    printf("\n%s, eh sua vez de atacar!\n", nome_jogador);
    printf("Por favor, informe as coordenadas de ataque (x y): \n");
    printf("Linha: ");
    scanf("%d", &x);
    printf("Coluna: ");
    scanf("%d", &y);

    while (x < 0 || x >= TAMANHO_CAMPO || y < 0 || y >= TAMANHO_CAMPO) {
        printf("\nCoordenadas invalidas! Tente novamente (0 a %d para x e y): \n", TAMANHO_CAMPO - 1);
        printf("Linha: ");
        scanf("%d", &x);
        printf("Coluna: ");
        scanf("%d", &y);
    }

    if (campo_inimigo[x][y] != 0) {
        printf("\nAcerto! %s afundou um navio de %s!\n", nome_jogador, nome_inimigo);
        printf("Barco de valor %d.\n", campo_inimigo[x][y]);
        pontuacao_jogador += campo_inimigo[x][y];
        campo_inimigo[x][y] = 0; 
    } else {
        printf("\nÁgua! Nenhum navio nessa posição.\n");
    }
    
    printf("\nPontuacao de %s = %d\n", nome_jogador, pontuacao_jogador);

    return pontuacao_jogador;
    /* dentro dessa função, as jogadas são validadas, o while faz a função de validação de coordenadas, onde caso sejam menores
    que zero, ou maiores que o limite máximo do campo\matriz, ele retornará a jogada como inválida, já o if serve como validador de 
    acerto, onde se o campo digitado pelo jogar for maior que 0, contará como um acerto, e a pontuação sobe conforme o o barco atingido*/
}

//////////////////////////////////////////////////////////

void exibirPlacar(int pontuacao_jogador_1, int pontuacao_jogador_2, char nome_jogador_1[TAMANHO_STRING], char nome_jogador_2[TAMANHO_STRING]) {
    for (int i = 0; i < 26; i++) {
        printf("-");
    }

    printf("\nFim de jogo!\n");
    printf("%s acertou %d navio(s).\n", nome_jogador_1, pontuacao_jogador_1);
    printf("%s acertou %d navio(s).\n", nome_jogador_2, pontuacao_jogador_2);

    if (pontuacao_jogador_1 > pontuacao_jogador_2) {
        printf("Parabéns, %s! Você venceu!\n", nome_jogador_1);
    } else {
        printf("Parabéns, %s! Você venceu!\n", nome_jogador_2);
    }
    
    for (int i = 0; i < 26; i++) {
        printf("-");
    }
    /* dentro dessa função, é feita a exibição do placar, onde os devidos pontos feitos de cada jogador são mostrados*/
}

//////////////////////////////////////////////////////////

int main() {
    inicializarCampo(campo_jogador_1);
    inicializarCampo(campo_jogador_2);
    
    nomeador(nome_jogador_1);
    nomeador(nome_jogador_2);
    
    selecionarbarcos(campo_jogador_1, nome_jogador_1);
    selecionarbarcos(campo_jogador_2, nome_jogador_2);
    
    int n = 1;
    while (pontuacao_jogador_1 < 10 && pontuacao_jogador_2 < 10) {
        for (int i = 0; i < 26; i++) {
            printf("-");
        }
        printf("\nRodada %d\n", n);
        for (int i = 0; i < 26; i++) {
            printf("-");
        }
        
        pontuacao_jogador_1 = validaJogada(nome_jogador_1, nome_jogador_2, campo_jogador_2, pontuacao_jogador_1);
        
        if (pontuacao_jogador_1 < 10) {
            pontuacao_jogador_2 = validaJogada(nome_jogador_2, nome_jogador_1, campo_jogador_1, pontuacao_jogador_2);
            n++;
        }
    }

    exibirPlacar(pontuacao_jogador_1, pontuacao_jogador_2, nome_jogador_1, nome_jogador_2);
    /* dentro dessa função, é feita a comparação de pontuação, o while roda enquanto ambos jogadores tiverem pontuação inferior a 10, e
    o if serve para validar se a jogada do jogador 2 será feita, uma vez que se o jogador 1 fizer uma pontuação maior ou igual a 10, ele
    irá direto para o placar, caso o jogador 2 ganhe, é feito a saída do laço do while e feito o chamado da função de exibição de placar*/
    
    return 0;
}