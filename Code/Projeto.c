#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

struct Carro
{
    char nome[50];
    int preco;
    int potencia;
    int quilometragem;
};

void encontrarMelhorCarro(struct Carro carros[], int n, int maxPreco)
{
    int dp[n + 1][maxPreco + 1];
    int selecionados[n];

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= maxPreco; j++)
        {
            dp[i][j] = 0;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= maxPreco; j++)
        {
            if (carros[i - 1].preco <= j)
            {
                int escolherCarro = carros[i - 1].potencia + dp[i - 1][j - carros[i - 1].preco];
                int naoEscolherCarro = dp[i - 1][j];

                if (escolherCarro > naoEscolherCarro ||
                    (escolherCarro == naoEscolherCarro && carros[i - 1].preco < carros[selecionados[i - 1]].preco))
                {
                    dp[i][j] = escolherCarro;
                    selecionados[i] = i - 1; // Marca o �ndice do carro como selecionado
                }
                else
                {
                    dp[i][j] = naoEscolherCarro;
                    selecionados[i] = selecionados[i - 1]; // Mant�m o carro selecionado anteriormente
                }
            }
            else
            {
                dp[i][j] = dp[i - 1][j];
                selecionados[i] = selecionados[i - 1]; // Mant�m o carro selecionado anteriormente
            }
        }
    }

    int potenciaMaxima = dp[n][maxPreco];
    int j = maxPreco;
    int valorTotal = 0;

    printf("Pot�ncia m�xima: %d\n", potenciaMaxima);
    printf("Carros selecionados:\n");

    for (int i = n; i >= 1; i--)
    {
        if (selecionados[i] != selecionados[i - 1])
        {
            printf("%s (Pot�ncia: %d, Quilometragem: %d, Pre�o: %d)\n", carros[i - 1].nome, carros[i - 1].potencia, carros[i - 1].quilometragem, carros[i - 1].preco);
            valorTotal += carros[i - 1].preco;
            j -= carros[i - 1].preco;
        }
    }

    printf("Valor total dos carros selecionados: %d\n", valorTotal);
}

int main()
{
    setlocale(LC_ALL, "Portuguese_Brazil");

    int n;
    printf("Digite o n�mero de carros: ");
    scanf("%d", &n);

    struct Carro carros[n];

    for (int i = 0; i < n; i++)
    {
        printf("Digite o nome do carro %d: ", i + 1);
        scanf("%s", carros[i].nome);
        printf("Digite o pre�o do carro %d: ", i + 1);
        scanf("%d", &carros[i].preco);
        printf("Digite a pot�ncia do carro %d: ", i + 1);
        scanf("%d", &carros[i].potencia);
        printf("Digite a quilometragem do carro %d: ", i + 1);
        scanf("%d", &carros[i].quilometragem);
    }

    int maxPreco;
    printf("Digite o valor m�ximo de pre�o: ");
    scanf("%d", &maxPreco);

    encontrarMelhorCarro(carros, n, maxPreco);

    return 0;
}
