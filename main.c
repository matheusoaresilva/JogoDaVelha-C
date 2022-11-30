//********** JOGO DA VELHA **********//
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

//Variavel Global
char jogo[3][3]; // Matriz do Jogo - Criou uma matriz 3x3.

int l, c; // l = Linha | c = Coluna. //Criou as vari�veis

//Fun��o 01:
int opcoes() {
    int escolha;

    printf("JOGO DA VELHA");
    printf("\n1- Jogar");
    printf("\n2- Pontua��o");
    printf("\n3- Grupo");
    printf("\n4- Sair\n\n");
    scanf("%d", &escolha);
    return escolha;
}

//Fun��o 02: Inicializar o tabuleiro.
void inicializarMatriz() {
    for (l = 0; l < 3; l++) {
        for (c = 0; c < 3; c++)
            jogo[l][c] = ' ';
    }
}

//Fun��o 04 - Imprimir o Tabuleiro do jogo;//
void tabuleiro() {
    printf("\n\n\t 0   1   2\n\n");
    for(l = 0; l < 3; l++) {
        for(c = 0; c < 3; c++) {
            if(c == 0)
                printf("\t");
            printf(" %c ", jogo[l][c]);
            if(c < 2)
                printf("|");
            if(c == 2)
                printf("   %d", l);
        }
        printf("\n");
        if(l < 2)
            printf("\t-----------\n");
    }
}

//Fun��o 06 - Funcao Para verificar se a posi��o � v�lida//
int verificaPosicaoLc(int l, int c) {
    if (l >= 0 && l < 3 && c >= 0 && c < 3 && jogo[l][c] == ' ')
        return 1;
    else
        return 0;
}

/*** Func�es Para Definir Vitoria ***/

//Fun��o 11 - Verifica cada linha da matriz e verifica se elas possuem os valores iguais.

int ganhouPorLinha(int l, char c) {
    if (jogo[l][0] == c && jogo[l][1] == c && jogo[l][2] == c)
        return 1;
    else
        return 0;
}


//Fun��o 07 - Verificar se o jogador venceu nas linhas.
int venceuLinha(char c) {
    int ganhou = 0;
    for (l = 0; l < 3; l++){
        ganhou += ganhouPorLinha(l, c); //ganhou = ganhou + ganhouPorLinha();
    }
    return ganhou;
}

//Fun��o 12 - Verifica cada coluna da matriz e verifica se elas possuem os valores iguais.
int ganhouPorColuna(int c, char j) {
    if (jogo[0][c] == j && jogo[1][c] == j && jogo[2][c] == j)
        return 1;
    else
        return 0;
}

//Fun��o 08 - Verificar se o jogador venceu nas Colunas;
int venceuColuna(char j) {
    int ganhou = 0;
    for (c = 0; c < 3; c++){
        ganhou += ganhouPorColuna(c, j); //ganhou = 0 + 1; ganhou = 1
    }
    return ganhou;
}

//Fun��o 09 - Verifica se os valores na diagonal principal da matriz s�o iguais.
int venceuDp(char c) {
    if (jogo[0][0] == c && jogo[1][1] == c && jogo[2][2] == c)
        return 1;
    else
        return 0;
}

//Fun��o 10 - Verifica se os valores na diagonal secund�ria da matriz s�o iguais.
int venceuDs(char c) {
    if (jogo[0][2] == c && jogo[1][1] == c && jogo[2][0] == c)
        return 1;
    else
        return 0;
}

// Fun��o 05 - Funcao para pedir e l� a posi��o escolhida da matriz.
void posicaoLc(char j) {
    int linha, coluna;

    printf("\nJogador %c digite linha e coluna: ", j);
    scanf("%d%d", &linha, &coluna);

    while (verificaPosicaoLc(linha, coluna) == 0) {
        printf("\nCoordenadas invalidas!\n\nJogador %c digite outra linha e coluna: ", j);
        scanf("%d%d", &linha, &coluna);
    }
    jogo[linha][coluna] = j;
}


//Fun��o 13 - Funcao Que Retorna a quantidade de posi��es vazias que ainda tem no c�digo//
int quantVazia() {
    int quantidade = 0;

    for (l = 0; l < 3; l++) {
        for (c = 0; c < 3; c++)
            if (jogo[l][c] == ' ')
                quantidade++;
    }
    return quantidade;
}

//Fun��o 03 - Funcao Para Iniciar Jogo
void jogar(int *qtdJogador1, int *qtdJogador2) {
    int jogador = 1, vitoriaX = 0, vitoriaO = 0;
    char jogador1 = 'X', jogador2 = 'O';

	/* Use-se o FILE para criar a vari�vel "*ponteiroArquivo" que ir� receber o caminho do arquivo atrav�s da fun��o "fopen"
	 */
    FILE *ponteiroArquivo;

    do {
     tabuleiro();
        if (jogador == 1) {
            posicaoLc(jogador1);
            jogador++;
            vitoriaX += venceuLinha(jogador1);
            vitoriaX += venceuColuna(jogador1);
            vitoriaX += venceuDp(jogador1);
            vitoriaX += venceuDs(jogador1);
        } else {
            posicaoLc(jogador2);
            jogador = 1;
            vitoriaO += venceuLinha(jogador2);
            vitoriaO += venceuColuna(jogador2);
            vitoriaO += venceuDp(jogador2);
            vitoriaO += venceuDs(jogador2);
        }
        system("CLS");
    } while (vitoriaX == 0 && vitoriaO == 0 && quantVazia() > 0);

 tabuleiro();

    if (vitoriaX == 1) {
        printf("\nParabens Jogador 1. Voce venceu!!!\n");
        *qtdJogador1 += 1;
    } else if (vitoriaO == 1) {
        printf("\nParabens Jogador 2. Voce venceu!!!\n");
        *qtdJogador2 += 1;
    }else{
        printf("\nJogo empatado!!!\n");
    }

    /* Arquivos Com Os Ranking | Contendo o Jogador 1 e 2 Mais a Quantidade de Vitorias Deles  */
    ponteiroArquivo = fopen("arquivo1.txt", "w");

    fprintf(ponteiroArquivo, "O Jogador 1 ganhou %d vezes\n", *qtdJogador1);
    fprintf(ponteiroArquivo, "O jogador 2 ganhou %d vezes", *qtdJogador2);

    fclose(ponteiroArquivo);
}



//Fun��o principal;
int main() {

    setlocale(LC_ALL, "Portuguese");

	int menu;
    int quantidadeJogador1 = 0, quantidadeJogador2 = 0;

	do {
        system("CLS"); //Limpando o console
        switch (opcoes()) {
        case 1:
            do {
                system("CLS");
                inicializarMatriz();
                jogar(&quantidadeJogador1, &quantidadeJogador2);

                printf("\nDigite 1 para jogar novamente ou outro numero para sair: ");
                scanf("%d", &menu);
            } while (menu == 1);
            break;
        case 2:
            system("CLS");
            printf(" PONTUA��O \n\n");
            printf("O jogador 1 ganhou %d\n", quantidadeJogador1);
            printf("O jogador 2 ganhou %d\n\n", quantidadeJogador2);
            break;
        case 3:
            system("CLS");
            printf(" GRUPO \n\n");
            printf("Gustavo C�sar Santos de Andrade\n");
            printf("Luan de Souza N�brega\n");
            printf("Manoel Erick Gon�alves Pereira\n");
            printf("Matheus Soares da Silva\n");
            printf("Roberto Soares de Farias Filho\n");
            break;
        case 4:
            exit(0);
            break;
        default:
        	printf("Digite uma op��oo valida!");
        }
        printf("\nDigite 1 para retornar: ");
        scanf("%d", &menu);
    } while (menu == 1);

    return 0;
}
