#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar um carro
struct Carro {
    char nome[50];
    int preco;
    int potencia;
};

// Função para encontrar o melhor carro usando programação dinâmica
void encontrarMelhorCarro(struct Carro carros[], int n, int maxPreco) {
    // Crie uma matriz para armazenar os subproblemas resolvidos
    int dp[n + 1][maxPreco + 1];

    // Inicialize a matriz com zeros
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= maxPreco; j++) {
            dp[i][j] = 0;
        }
    }

    // Preencha a matriz dp usando programação dinâmica
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= maxPreco; j++) {
            if (carros[i - 1].preco <= j) {
                dp[i][j] = (carros[i - 1].potencia > dp[i - 1][j]) ?
                           carros[i - 1].potencia + dp[i - 1][j - carros[i - 1].preco] :
                           dp[i - 1][j];
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    // Recupere a potência máxima obtida
    int potenciaMaxima = dp[n][maxPreco];

    // Recupere os carros selecionados (opcional)
    printf("Potência máxima: %d\n", potenciaMaxima);
    printf("Carros selecionados:\n");

    int j = maxPreco;
    for (int i = n; i > 0 && potenciaMaxima > 0; i--) {
        if (dp[i][j] != dp[i - 1][j]) {
            printf("%s\n", carros[i - 1].nome);
            potenciaMaxima -= carros[i - 1].potencia;
            j -= carros[i - 1].preco;
        }
    }
}

int main() {
    int n;
    printf("Digite o número de carros: ");
    scanf("%d", &n);

    // Crie um array de carros com base na entrada do usuário
    struct Carro carros[n];

    for (int i = 0; i < n; i++) {
        printf("Digite o nome do carro %d: ", i + 1);
        scanf("%s", carros[i].nome);
        printf("Digite o preço do carro %d: ", i + 1);
        scanf("%d", &carros[i].preco);
        printf("Digite a potência do carro %d: ", i + 1);
        scanf("%d", &carros[i].potencia);
    }

    int maxPreco;
    printf("Digite o valor máximo de preço: ");
    scanf("%d", &maxPreco);

    encontrarMelhorCarro(carros, n, maxPreco);

    return 0;
}
