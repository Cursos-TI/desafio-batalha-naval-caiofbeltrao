#include <stdio.h>
#include <stdlib.h>  // abs, EXIT_SUCCESS / EXIT_FAILURE
#include <string.h>  // memset

#define TAM 10     // Tamanho do tabuleiro (10x10)
#define HABIL 5    // Tamanho das matrizes de habilidade (5x5)
#define AGUA 0     // Representa água
#define NAVIO 3    // Representa navio
#define AREA 5     // Representa área afetada pela habilidade

// Prototipos
void inicializarTabuleiro(int tabuleiro[TAM][TAM]);
void exibirTabuleiro(int tabuleiro[TAM][TAM]);
int posicionarNavioHorizontal(int tabuleiro[TAM][TAM], int linha, int colunaInicial);
int posicionarNavioVertical(int tabuleiro[TAM][TAM], int linhaInicial, int coluna);
void aplicarCone(int tabuleiro[TAM][TAM], int origemLinha, int origemColuna);
void aplicarCruz(int tabuleiro[TAM][TAM], int origemLinha, int origemColuna);
void aplicarOctaedro(int tabuleiro[TAM][TAM], int origemLinha, int origemColuna);

// Inicializa com zeros
void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = AGUA;
}

// Exibe o tabuleiro
void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Retorna 1 se conseguiu posicionar, 0 caso contrário.
// Verifica limites e sobreposição.
int posicionarNavioHorizontal(int tabuleiro[TAM][TAM], int linha, int colunaInicial) {
    if (linha < 0 || linha >= TAM) return 0;
    if (colunaInicial < 0 || colunaInicial + 2 >= TAM) return 0; // tamanho 3 -> colunaInicial+2
    // verifica sobreposição
    for (int j = 0; j < 3; j++)
        if (tabuleiro[linha][colunaInicial + j] != AGUA) return 0;
    // posiciona
    for (int j = 0; j < 3; j++)
        tabuleiro[linha][colunaInicial + j] = NAVIO;
    return 1;
}

int posicionarNavioVertical(int tabuleiro[TAM][TAM], int linhaInicial, int coluna) {
    if (coluna < 0 || coluna >= TAM) return 0;
    if (linhaInicial < 0 || linhaInicial + 2 >= TAM) return 0; // tamanho 3 -> linhaInicial+2
    // verifica sobreposição
    for (int i = 0; i < 3; i++)
        if (tabuleiro[linhaInicial + i][coluna] != AGUA) return 0;
    // posiciona
    for (int i = 0; i < 3; i++)
        tabuleiro[linhaInicial + i][coluna] = NAVIO;
    return 1;
}

// === HABILIDADES ===
// As funções constroem a matriz 5x5 (HABIL) dinamicamente e só escrevem
// no tabuleiro quando o índice calculado está dentro dos limites.
// Além disso, não sobrescrevem navios (mantêm NAVIO).

void aplicarCone(int tabuleiro[TAM][TAM], int origemLinha, int origemColuna) {
    int habilidade[HABIL][HABIL];
    int centro = HABIL / 2; // 2 para HABIL=5
    // inicializa
    for (int i = 0; i < HABIL; i++)
        for (int j = 0; j < HABIL; j++)
            habilidade[i][j] = 0;

    // Monta o cone (triângulo apontando para baixo) - top no i=0
    for (int i = 0; i < HABIL; i++) {
        for (int j = 0; j < HABIL; j++) {
            if (j >= (centro - i) && j <= (centro + i))
                habilidade[i][j] = 1;
        }
    }

    // Aplica no tabuleiro (AREA = 5), checando limites
    for (int i = 0; i < HABIL; i++) {
        for (int j = 0; j < HABIL; j++) {
            if (habilidade[i][j] != 1) continue;
            int lin = origemLinha + i - centro;
            int col = origemColuna + j - centro;
            if (lin < 0 || lin >= TAM || col < 0 || col >= TAM) continue;
            if (tabuleiro[lin][col] == AGUA) tabuleiro[lin][col] = AREA;
        }
    }
}

void aplicarCruz(int tabuleiro[TAM][TAM], int origemLinha, int origemColuna) {
    int habilidade[HABIL][HABIL];
    int centro = HABIL / 2;
    for (int i = 0; i < HABIL; i++)
        for (int j = 0; j < HABIL; j++)
            habilidade[i][j] = (i == centro || j == centro) ? 1 : 0;

    for (int i = 0; i < HABIL; i++) {
        for (int j = 0; j < HABIL; j++) {
            if (habilidade[i][j] != 1) continue;
            int lin = origemLinha + i - centro;
            int col = origemColuna + j - centro;
            if (lin < 0 || lin >= TAM || col < 0 || col >= TAM) continue;
            if (tabuleiro[lin][col] == AGUA) tabuleiro[lin][col] = AREA;
        }
    }
}

void aplicarOctaedro(int tabuleiro[TAM][TAM], int origemLinha, int origemColuna) {
    int habilidade[HABIL][HABIL];
    int centro = HABIL / 2;
    for (int i = 0; i < HABIL; i++)
        for (int j = 0; j < HABIL; j++)
            habilidade[i][j] = (abs(i - centro) + abs(j - centro) <= centro) ? 1 : 0;

    for (int i = 0; i < HABIL; i++) {
        for (int j = 0; j < HABIL; j++) {
            if (habilidade[i][j] != 1) continue;
            int lin = origemLinha + i - centro;
            int col = origemColuna + j - centro;
            if (lin < 0 || lin >= TAM || col < 0 || col >= TAM) continue;
            if (tabuleiro[lin][col] == AGUA) tabuleiro[lin][col] = AREA;
        }
    }
}

// === Programa principal ===
int main(void) {
    int tab1[TAM][TAM];
    int tab2[TAM][TAM];
    int tab3[TAM][TAM];

    int origemLinha = TAM / 2;   // 5
    int origemColuna = TAM / 2;  // 5

    // --- TAB 1: CONE ---
    inicializarTabuleiro(tab1);
    // posiciona navios: se retornar 0, imprime mensagem mas continua
    if (!posicionarNavioHorizontal(tab1, 2, 2))
        printf("[Aviso] Não foi possível posicionar navio horizontal no Tab1 (2,2)\n");
    if (!posicionarNavioVertical(tab1, 5, 7))
        printf("[Aviso] Não foi possível posicionar navio vertical no Tab1 (5,7)\n");
    // aplico o cone um pouco acima do centro para visual ficar parecido com "top origin"
    aplicarCone(tab1, origemLinha - 2, origemColuna);
    printf("=== TABULEIRO 1: HABILIDADE CONE ===\n");
    exibirTabuleiro(tab1);
    printf("\n");

    // --- TAB 2: CRUZ ---
    inicializarTabuleiro(tab2);
    if (!posicionarNavioHorizontal(tab2, 3, 1))
        printf("[Aviso] Não foi possível posicionar navio horizontal no Tab2 (3,1)\n");
    if (!posicionarNavioVertical(tab2, 6, 6))
        printf("[Aviso] Não foi possível posicionar navio vertical no Tab2 (6,6)\n");
    aplicarCruz(tab2, origemLinha, origemColuna);
    printf("=== TABULEIRO 2: HABILIDADE CRUZ ===\n");
    exibirTabuleiro(tab2);
    printf("\n");

    // --- TAB 3: OCTAEDRO ---
    inicializarTabuleiro(tab3);
    if (!posicionarNavioHorizontal(tab3, 1, 5))
        printf("[Aviso] Não foi possível posicionar navio horizontal no Tab3 (1,5)\n");
    if (!posicionarNavioVertical(tab3, 6, 3))
        printf("[Aviso] Não foi possível posicionar navio vertical no Tab3 (6,3)\n");
    aplicarOctaedro(tab3, origemLinha, origemColuna);
    printf("=== TABULEIRO 3: HABILIDADE OCTAEDRO ===\n");
    exibirTabuleiro(tab3);
    printf("\n");

    return 0;
}
