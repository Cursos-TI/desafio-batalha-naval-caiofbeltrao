#include <stdio.h>

#define TAMANHO 10   // Tamanho do tabuleiro (10x10)
#define NAVIO 3      // Tamanho fixo dos navios
#define AGUA 0       // Representa água
#define NAVIO_POS 3  // Representa parte de navio

int main() {
    int tabuleiro[TAMANHO][TAMANHO]; // Matriz do tabuleiro
    int i, j;

    // 1️⃣ Inicializa o tabuleiro com água (0)
    for (i = 0; i < TAMANHO; i++) {
        for (j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // ===============================================================
    // 2️⃣ Definição das coordenadas iniciais dos 4 navios (fixas no código)
    // ===============================================================

    // Navio 1: horizontal
    int linha_h1 = 7, coluna_h1 = 1;

    // Navio 2: vertical
    int linha_v2 = 5, coluna_v2 = 6;

    // Navio 3: diagonal principal (↘) - linha e coluna aumentam simultaneamente
    int linha_d3 = 0, coluna_d3 = 0;

    // Navio 4: diagonal secundária (↙) - linha aumenta e coluna diminui
    int linha_d4 = 0, coluna_d4 = 9;

    // ===============================================================
    // 3️⃣ Função simples de validação e posicionamento
    // ===============================================================
    int valido = 1; // Flag para verificar se algum navio sai dos limites

    // --- Navio 1 (horizontal) ---
    if (coluna_h1 + NAVIO > TAMANHO) valido = 0;
    else {
        for (i = 0; i < NAVIO; i++) {
            if (tabuleiro[linha_h1][coluna_h1 + i] != AGUA) valido = 0;
        }
        if (valido)
            for (i = 0; i < NAVIO; i++)
                tabuleiro[linha_h1][coluna_h1 + i] = NAVIO_POS;
    }

    // --- Navio 2 (vertical) ---
    if (linha_v2 + NAVIO > TAMANHO) valido = 0;
    else {
        for (i = 0; i < NAVIO; i++) {
            if (tabuleiro[linha_v2 + i][coluna_v2] != AGUA) valido = 0;
        }
        if (valido)
            for (i = 0; i < NAVIO; i++)
                tabuleiro[linha_v2 + i][coluna_v2] = NAVIO_POS;
    }

    // --- Navio 3 (diagonal principal ↘) ---
    if (linha_d3 + NAVIO > TAMANHO || coluna_d3 + NAVIO > TAMANHO) valido = 0;
    else {
        for (i = 0; i < NAVIO; i++) {
            if (tabuleiro[linha_d3 + i][coluna_d3 + i] != AGUA) valido = 0;
        }
        if (valido)
            for (i = 0; i < NAVIO; i++)
                tabuleiro[linha_d3 + i][coluna_d3 + i] = NAVIO_POS;
    }

    // --- Navio 4 (diagonal secundária ↙) ---
    if (linha_d4 + NAVIO > TAMANHO || coluna_d4 - (NAVIO - 1) < 0) valido = 0;
    else {
        for (i = 0; i < NAVIO; i++) {
            if (tabuleiro[linha_d4 + i][coluna_d4 - i] != AGUA) valido = 0;
        }
        if (valido)
            for (i = 0; i < NAVIO; i++)
                tabuleiro[linha_d4 + i][coluna_d4 - i] = NAVIO_POS;
    }

    // ===============================================================
    // 4️⃣ Verificação final
    // ===============================================================
    if (!valido) {
        printf("Erro: coordenadas inválidas ou sobreposição de navios!\n");
        return 1;
    }

    // ===============================================================
    // 5️⃣ Exibe o tabuleiro
    // ===============================================================
    printf("\n=== TABULEIRO BATALHA NAVAL ===\n\n");

    for (i = 0; i < TAMANHO; i++) {
        for (j = 0; j < TAMANHO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
