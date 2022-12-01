/*
Nome: Victor Manuel De Barros Garcia
Matricula: 20102283
Sistemas Operacionais
BS - INF0601N - 2022-2
*/

#include <stdio.h>
#include <stdlib.h>
// Adicionei esse biblioteca
#include <locale.h>

/*
Mutex é usado como um primitivo de sincronização em situações
onde o recurso tem que ser compartilhado com múltiplas thread simultaneamente.
Os objetos mutex nomeados são usados para fazer a sincronização interprocessos,
porque vários aplicativos podem acessar o mesmo objeto mutex.
*/
// Inicialize um mutex para 1
int mutex = 1;

// Número de slots completos como 0
int full = 0;

// Número de slots vazios como tamanho de buffer
int empty = 10, x = 0;

// Função para produzir um item e adicioná-lo ao buffer
void produtor(void)
{
    // Diminuir o valor do mutex em 1
    --mutex;

    // Aumentar o número de completos
    // slots por 1
    ++full;

    // Diminuir o número de vazios
    // slots por 1
    --empty;

    // Item produzido
    x++;
    printf("\nProdutor produz o "
           "item %d",
           x);

    // Aumente o valor do mutex em 1
    ++mutex;
}

// Função para consumir um item e removê-lo de buffer
void consumidor(void)
{
    // Diminuir o valor do mutex em 1
    --mutex;

    // Diminuir o número de completos
    // slots por 1
    --full;

    // Aumente o número de vazios
    // slots por 1
    ++empty;
    printf("\nConsumidor consome o "
           "item %d",
           x);
    x--;

    // Aumente o valor do mutex em 1
    ++mutex;
}

int main()
{
    int n, i;
    printf("\nEscolha 1 para Produtor"
           "\nEscolha 2 para Consumidor"
           "\nEscolha 3 para sair do programa");

// Usando '#pragma omp parallel for'
// pode dar valor errado devido a
// problemas de sincronização.

// 'crítico' especifica que o código é
// executado por apenas um thread em um
// tempo ou seja, apenas um thread entra
// a seção crítica em um determinado momento
#pragma omp critical

    for (i = 1; i > 0; i++)
    {

        printf("\nEscolha uma das opcoes:");
        scanf("%d", &n);

        // Switch Cases
        switch (n)
        {
        case 1:

            // Se mutex for 1 e vazio
            // é diferente de zero, então é
            // possível produzir
            if ((mutex == 1) && (empty != 0))
            {
                produtor();
            }

            // Caso contrário, imprime o buffer
            // está cheio
            else
            {
                printf("Buffer esta vazio");
            }
            break;

        case 2:

            // Se o mutex for 1 e completo
            // é diferente de zero, então é
            // possível consumir

            if ((mutex == 1) && (full != 0))
            {
                consumidor();
            }

            // Caso contrário, imprime Buffer
            // está vazia
            else
            {
                printf("Buffer esta vazio");
            }
            break;

        // Condição de saída
        case 3:
            exit(0);
            break;
        }
    }
}