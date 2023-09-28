#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar um carro
struct Carro {
    double quilometragem;
    double valor;
    int indice; // Índice original do carro
};

// Função para calcular o melhor carro com base na programação dinâmica (top-down)
struct Carro melhorCarro(int n, struct Carro carros[]) {
    struct Carro melhor = {1e9, 1e9, -1}; // Inicialize com valores muito altos

    for (int i = 0; i < n; i++) {
        if (carros[i].quilometragem < melhor.quilometragem || (carros[i].quilometragem == melhor.quilometragem && carros[i].valor < melhor.valor)) {
            melhor = carros[i];
            melhor.indice = i; // Atualiza o índice do melhor carro
        }
    }

    return melhor;
}

int main() {
    int n;
    printf("Digite o número de carros: ");
    scanf("%d", &n);

    struct Carro carros[n];

    printf("Digite a quilometragem e o valor de cada carro:\n");
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &carros[i].quilometragem, &carros[i].valor);
        carros[i].indice = i; // Armazena o índice original do carro
    }

    struct Carro melhor = melhorCarro(n, carros);

    if (melhor.indice != -1) {
        printf("O melhor carro tem quilometragem %.2lf e valor %.2lf (Carro %d)\n", melhor.quilometragem, melhor.valor, melhor.indice);
    } else {
        printf("Nenhum carro atende aos critérios.\n");
    }

    return 0;
}
