#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define N 300000

void countingSort(int V[], int n, int exp);
void radixSort(int V[], int n);
int PesquisaSequencial(int *V, int tamanho, int Chave);
int PesquisaBinaria(int *V, int tamanho, int Chave);

int main()
{
    clock_t tInicioVetor = clock();

    int *V = (int *)malloc(N * sizeof(int));

    if (V == NULL)
    {
        printf("ERRO: não há memória para o vetor!\n");
        return 1;
    }

    srand(129);

    for (int i = 0; i < N; i++)
        V[i] = rand();
    clock_t tFimVetor = clock();

    clock_t tInicioRadix = clock();
    radixSort(V, N);
    clock_t tFimRadix = clock();

    clock_t tInicioPesquisa = clock();
    int pos = PesquisaSequencial(V, N, 2147344243);
    clock_t tFimPesquisa = clock();

    /*PesquisaSequencial(V, N, 2147117830);
    PesquisaSequencial(V, N, 2147086986);
    PesquisaSequencial(V, N, 2147085461);
    PesquisaSequencial(V, N, 2147027534);
    */

    if (pos != -1)
        printf("Encontrado na posição %d\n", pos);
    else
        printf("Elemento não encontrado\n");
    double TempoVetor = ((double)(tFimVetor - tInicioVetor)) / CLOCKS_PER_SEC;
    double TempoRadix = ((double)(tFimRadix - tInicioRadix)) / CLOCKS_PER_SEC;
    double TempoPesquisa = ((double)(tFimPesquisa - tInicioPesquisa)) / CLOCKS_PER_SEC;

    printf("Tempo gasto vetor: %.3f segundos\n", TempoVetor);
    printf("Tempo gasto ordenacao: %.3f segundos\n", TempoRadix);
    printf("Tempo gasto pesquisa: %.5f segundos\n", TempoPesquisa);
    /*
    printf("Ultimos 20 elementos ordenados:\n");
    for (int i = N - 1; i > N - 20; i--)
    {
        printf("%d ", V[i]);
        printf("\n");
    }
    */

    free(V);
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

        int Meio = (Esquerda + Direita) / 2;

        if (V[Meio] == Chave)
            return Meio;
        else if (V[Meio] < Chave)
            Esquerda = Meio + 1;
        else
            Direita = Meio - 1;
    }

    return -1; // O elemento não está no conjunto
}