#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define N_TESTES_TAMANHO 3

#define N_TESTES 4

void countingSort(int V[], int n, int exp);
void radixSort(int V[], int n);
int PesquisaSequencial(int *V, int tamanho, int Chave);
int PesquisaBinaria(int *V, int tamanho, int Chave);

int main()
{
    int tamanhos[] = {100000, 200000, 300000};
    int chaves[N_TESTES];
    
    for (int t = 0; t < N_TESTES_TAMANHO; t++)
    {
        double somaTempoPreenchimentoVetor = 0.0,
               somaTempoOrdenacao = 0.0,
               somaTempoPesquisaSequencial = 0.0,
               somaTempoPesquisaBinaria = 0.0;
        int N = tamanhos[t];

        int *V = (int *)malloc(N * sizeof(int));
        if (V == NULL)
        {
            printf("ERRO: não há memória para o vetor!\n");
            return 1;
        }

        printf("==============================================================\n");
        printf("Tempo de preenchimento e ordenação do vetor com %d elementos\n", N);
        printf("==============================================================\n");

        // Alocação do vetor
        for (int i = 0; i < N_TESTES; i++)
        {
            clock_t tInicioVetor = clock();

            srand(129);

            for (int j = 0; j < N; j++)
                V[j] = rand();
            clock_t tFimVetor = clock();

            double TempoVetor = ((double)(tFimVetor - tInicioVetor)) / CLOCKS_PER_SEC;

            somaTempoPreenchimentoVetor += TempoVetor;
            printf("Tempo gasto vetor: %.3f segundos\n", TempoVetor);

            // Ordenação Radix Sort
            clock_t tInicioRadix = clock();
            radixSort(V, N);
            clock_t tFimRadix = clock();

            double TempoRadix = ((double)(tFimRadix - tInicioRadix)) / CLOCKS_PER_SEC;
            somaTempoOrdenacao += TempoRadix;
            printf("Tempo gasto ordenacao: %.3f segundos\n\n", TempoRadix);
        }

        printf("==============================\n");
        printf("Últimos 4 elementos ordenados:\n");
        printf("==============================\n");

        for (int i = 0; i < N_TESTES; i++)
        {
            chaves[i] = V[N - N_TESTES + i];
        }
        for (int i = 0; i < N_TESTES; i++)
        {
            printf("Chave %d = %d \n", i + 1, chaves[i]);
        }

        printf("\n====================================================\n");
        printf("Pesquisa Sequencial com %d elementos\n", N);
        printf("====================================================\n");

        // Pesquisa Sequencial
        for (int i = 0; i < N_TESTES; i++)
        {
            clock_t tInicioPesquisa = clock();
            int pos = PesquisaSequencial(V, N, chaves[i]);
            clock_t tFimPesquisa = clock();

            if (pos != -1)
                printf("Chave %d encontrada na posição %d\n", i + 1, pos);
            else
                printf("Chave %d não encontrada\n", i + 1);

            double TempoPesquisaSequencial = ((double)(tFimPesquisa - tInicioPesquisa)) / CLOCKS_PER_SEC;
            printf("Tempo gasto pesquisa sequencial para chave %d: %.6f segundos\n", i + 1, TempoPesquisaSequencial);

            somaTempoPesquisaSequencial += TempoPesquisaSequencial;
        }

        printf("\n====================================================\n");
        printf("Pesquisa Binária com %d elementos\n", N);
        printf("====================================================\n");

        // Pesquisa Binária
        for (int i = 0; i < N_TESTES; i++)
        {
            clock_t tInicioPesquisaBinaria = clock();
            int pos = PesquisaBinaria(V, N, chaves[i]);
            clock_t tFimPesquisaBinaria = clock();

            if (pos != -1)
                printf("Chave %d encontrada na posição %d\n", i + 1, pos);
            else
                printf("Chave %d não encontrada\n", i + 1);

            double TempoPesquisaBinaria = ((double)(tFimPesquisaBinaria - tInicioPesquisaBinaria)) / CLOCKS_PER_SEC;
            printf("Tempo gasto pesquisa binária para chave %d: %2.2e segundos\n", i + 1, TempoPesquisaBinaria);

            somaTempoPesquisaBinaria += TempoPesquisaBinaria;
        }

        printf("\n===========================\n");
        printf("Médias com %d elementos\n", N);
        printf("===========================\n");

        printf("Tempo médio em preenchimento do vetor: %.4f segundos\n", somaTempoPreenchimentoVetor / N_TESTES);
        printf("Tempo médio em ordenacao: %.4f segundos\n", somaTempoOrdenacao / N_TESTES);
        printf("Tempo médio em pesquisa sequencial: %.6f segundos\n", somaTempoPesquisaSequencial / N_TESTES);
        printf("Tempo médio em pesquisa binária: %.2e segundos\n", somaTempoPesquisaBinaria / N_TESTES);

        free(V);
    }
    return 0;
}

void countingSort(int V[], int n, int exp)
{
    int *saida = (int *)malloc(n * sizeof(int));
    int contagem[10] = {0};

    // Conta ocorrências dos dígitos
    for (int i = 0; i < n; i++)
        contagem[(V[i] / exp) % 10]++;

    // Soma acumulada
    for (int i = 1; i < 10; i++)
        contagem[i] += contagem[i - 1];

    // Monta vetor de saída
    for (int i = n - 1; i >= 0; i--)
    {
        int digito = (V[i] / exp) % 10;
        saida[contagem[digito] - 1] = V[i];
        contagem[digito]--;
    }

    // Copia de volta para o vetor original
    for (int i = 0; i < n; i++)
        V[i] = saida[i];

    free(saida);
}

void radixSort(int V[], int n)
{
    int maior = V[0];

    // Encontra o maior elemento
    for (int i = 1; i < n; i++)
    {
        if (V[i] > maior)
            maior = V[i];
    }

    // Ordena por cada dígito
    for (int exp = 1; maior / exp > 0; exp *= 10)
    {
        countingSort(V, n, exp);
    }
}

int PesquisaSequencial(int *V, int tamanho, int Chave)
{

    for (int i = 0; i < tamanho; i++)
    {
        if (V[i] == Chave)
            return i;
    }

    return -1; // O elemento não está no conjunto
}

int PesquisaBinaria(int *V, int tamanho, int Chave)
{

    int Esquerda = 0;
    int Direita = tamanho - 1;

    while (Esquerda <= Direita)
    {

        int Meio = Esquerda + (Direita - Esquerda) / 2;

        if (V[Meio] == Chave)
            return Meio;
        else if (V[Meio] < Chave)
            Esquerda = Meio + 1;
        else
            Direita = Meio - 1;
    }

    return -1; // O elemento não está no conjunto
}