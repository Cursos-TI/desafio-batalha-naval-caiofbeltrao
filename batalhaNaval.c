#include <stdio.h>

int main() {
    int TAMANHO = 10;   // Tamanho do tabuleiro (10x10)
    int NAVIO = 3;      // Tamanho fixo de cada navio
    int AGUA = 0;       // Representa água
    int NAVIO_POS = 3;  // Representa parte de navio
    int tabuleiro[TAMANHO][TAMANHO];  // Matriz que representa o tabuleiro
    int i, j;

    // 1️⃣ Inicializa o tabuleiro com água (0)
    for (i = 0; i < TAMANHO; i++) {
        for (j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // 2️⃣ Declaração dos navios (vetores unidimensionais)
    int navio_horizontal[NAVIO] = {NAVIO_POS, NAVIO_POS, NAVIO_POS};
    int navio_vertical[NAVIO]   = {NAVIO_POS, NAVIO_POS, NAVIO_POS};

    // 3️⃣ Coordenadas iniciais fixas dos navios
    int linha_horizontal = 2;  // linha do navio horizontal
    int coluna_horizontal = 4; // coluna inicial do navio horizontal
    int linha_vertical = 5;    // linha inicial do navio vertical
    int coluna_vertical = 7;   // coluna do navio vertical

    // 4️⃣ Validação simples dos limites (opcional no nível básico)
    if (coluna_horizontal + NAVIO > TAMANHO || linha_vertical + NAVIO > TAMANHO) {
        printf("Erro: navio fora dos limites do tabuleiro!\n");
        return 1;
    }

    // 5️⃣ Posiciona o navio horizontal
    for (i = 0; i < NAVIO; i++) {
        tabuleiro[linha_horizontal][coluna_horizontal + i] = navio_horizontal[i];
    }

    // 6️⃣ Posiciona o navio vertical (somente se não sobrepuser)
    int sobrepoe = 0;
    for (i = 0; i < NAVIO; i++) {
        if (tabuleiro[linha_vertical + i][coluna_vertical] != AGUA) {
            sobrepoe = 1;
            break;
        }
    }

    if (sobrepoe) {
        printf("Erro: os navios se sobrepõem!\n");
        return 1;
    }

    for (i = 0; i < NAVIO; i++) {
        tabuleiro[linha_vertical + i][coluna_vertical] = navio_vertical[i];
    }

    // 7️⃣ Exibe o tabuleiro
    printf("\n=== TABULEIRO BATALHA NAVAL ===\n\n");
    for (i = 0; i < TAMANHO; i++) {
        for (j = 0; j < TAMANHO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
