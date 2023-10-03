#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

struct Carro
{
    char nome[50];
    double preco;
    int potencia; // Limitada de 1 a 10
    double quilometragem;
};

void encontrarMelhorCarro(struct Carro carros[], int n, double maxPreco)
{
    int maxPrecoInt = (int)maxPreco;
    double ***dp = malloc((n + 1) * sizeof(double **));
    int ***selecionados = malloc((n + 1) * sizeof(int **));

    for (int i = 0; i <= n; i++)
    {
        dp[i] = malloc((n + 1) * sizeof(double *));
        selecionados[i] = malloc((n + 1) * sizeof(int *));
        for (int j = 0; j <= n; j++)
        {
            dp[i][j] = malloc((maxPrecoInt + 1) * sizeof(double));
            selecionados[i][j] = malloc((maxPrecoInt + 1) * sizeof(int));
        }
    }

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            for (int k = 0; k <= maxPrecoInt; k++)
            {
                dp[i][j][k] = 0.0;
                selecionados[i][j][k] = 0;
            }
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            for (int k = 1; k <= maxPrecoInt; k++)
            {
                if (carros[i - 1].preco <= k)
                {
                    double escolherCarro = carros[i - 1].potencia + dp[i - 1][j - 1][k - (int)(carros[i - 1].preco)];
                    double naoEscolherCarro = dp[i - 1][j][k];

                    if (escolherCarro > naoEscolherCarro)
                    {
                        dp[i][j][k] = escolherCarro;
                        selecionados[i][j][k] = 1; // Marca o carro como selecionado
                    }
                    else
                    {
                        dp[i][j][k] = naoEscolherCarro;
                        selecionados[i][j][k] = 0; // Não selecionado
                    }
                }
                else
                {
                    dp[i][j][k] = dp[i - 1][j][k];
                    selecionados[i][j][k] = 0; // Não selecionado
                }
            }
        }
    }

    double melhorPotencia = 0.0;
    int melhorKilometragem = 0;
    int melhorPreco = 0;

    for (int i = n; i >= 1; i--)
    {
        for (int j = 1; j <= n; j++)
        {
            for (int k = maxPrecoInt; k >= 1; k--)
            {
                if (selecionados[i][j][k])
                {
                    double potenciaAtual = dp[i][j][k];
                    int quilometragemAtual = j;
                    int precoAtual = k;

                    if (potenciaAtual > melhorPotencia ||
                        (potenciaAtual == melhorPotencia && quilometragemAtual < melhorKilometragem) ||
                        (potenciaAtual == melhorPotencia && quilometragemAtual == melhorKilometragem && precoAtual < melhorPreco))
                    {
                        melhorPotencia = potenciaAtual;
                        melhorKilometragem = quilometragemAtual;
                        melhorPreco = precoAtual;
                    }
                }
            }
        }
    }

    printf("Melhor combinação:\n");
    for (int i = n, j = melhorKilometragem, k = melhorPreco; i >= 1; i--)
    {
        if (selecionados[i][j][k])
        {
            printf("%s (Potência: %d, Quilometragem: %.2lf, Preço: %.2lf)\n", carros[i - 1].nome, carros[i - 1].potencia, carros[i - 1].quilometragem, carros[i - 1].preco);
            j -= 1;
            k -= (int)carros[i - 1].preco;
        }
    }

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            free(dp[i][j]);
            free(selecionados[i][j]);
        }
        free(dp[i]);
        free(selecionados[i]);
    }
    free(dp);
    free(selecionados);
}

int main()
{
    setlocale(LC_ALL, "Portuguese_Brazil");

    int n;
    printf("Digite o número de carros: ");
    scanf("%d", &n);

    struct Carro carros[n];

    for (int i = 0; i < n; i++)
    {
        printf("Digite o nome do carro %d: ", i + 1);
        scanf("%s", carros[i].nome);
        printf("Digite o preço do carro %d: ", i + 1);
        scanf("%lf", &carros[i].preco);

        // Solicita a potência, limitando-a entre 1 e 10
        do {
            printf("Digite a potência do carro %d (entre 1 e 10): ", i + 1);
            scanf("%d", &carros[i].potencia);
        } while (carros[i].potencia < 1 || carros[i].potencia > 10);

        printf("Digite a quilometragem do carro %d: ", i + 1);
        scanf("%lf", &carros[i].quilometragem);
    }

    double maxPreco;
    printf("Digite o valor máximo de preço: ");
    scanf("%lf", &maxPreco);

    encontrarMelhorCarro(carros, n, maxPreco);

    return 0;
}
