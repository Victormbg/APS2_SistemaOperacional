/*
Nome: Victor Manuel De Barros Garcia
Matricula: 20102283
Sistemas Operacionais
BS - INF0601N - 2022-2
*/

#include <pthread.h>
#include <stdio.h>
#include <windows.h>
#include <unistd.h>

#define FALSE 0
#define TRUE 1

// Declaracao das variaveis de condicao:
pthread_mutex_t mutex;

// Buffer
#define BUFFERVAZIO 0
#define BUFFERCHEIO 1
int buffer;
int estado = BUFFERVAZIO;

void produtor(int id)
{
    int i = 0;
    int item;
    int aguardar;

    printf("Inicio produtor %d \n", id);
    while (i < 3)
    {
        // produzir item
        item = i + (id * 1000);

        do
        {
            pthread_mutex_lock(&mutex);
            aguardar = FALSE;
            if (estado == BUFFERCHEIO)
            {
                aguardar = TRUE;
                pthread_mutex_unlock(&mutex);
            }
        } while (aguardar == TRUE);

        // inserir item
        printf("Produtor %d inserindo item %d\n", id, item);
        buffer = item;
        estado = BUFFERCHEIO;

        pthread_mutex_unlock(&mutex);
        i++;
        sleep(2);
    }
    printf("Produtor %d terminado \n", id);
}

void consumidor(int id)
{
    int item;
    int aguardar;

    printf("Inicio consumidor %d \n", id);
    while (1)
    {
        // retirar item da fila
        do
        {
            pthread_mutex_lock(&mutex);
            aguardar = FALSE;
            if (estado == BUFFERVAZIO)
            {
                aguardar = TRUE;
                pthread_mutex_unlock(&mutex);
            }
        } while (aguardar == TRUE);
        item = buffer;
        estado = BUFFERVAZIO;
        pthread_mutex_unlock(&mutex);

        // processar item
        printf("Consumidor %d consumiu item %d\n", id, item);

        sleep(2);
    }
    printf("Consumidor %d terminado \n", id);
}

int main()
{
    int n, i;
    pthread_t prod1;
    pthread_t cons1;
    printf("Programa Produtor-Consumidor\n");
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
            printf("INICIO");
            printf("Iniciando variaveis de sincronizacao.\n");
            pthread_mutex_init(&mutex, NULL);
            printf("Disparando threads produtores\n");
            pthread_create(&prod1, NULL, produtor, 1);
            printf("Disparando threads consumidores\n");
            pthread_create(&cons1, NULL, consumidor, 1);
            pthread_join(prod1, NULL);
            //pthread_join(cons1, NULL);

            printf("FIM");
            break;
        case 2:
            printf("Iniciando variaveis de sincronizacao.\n");
            pthread_mutex_init(&mutex, NULL);
            printf("Disparando threads produtores\n");
            pthread_create(&prod1, NULL, (void *)produtor, 1);
            printf("Disparando threads consumidores\n");
            pthread_create(&cons1, NULL, (void *)consumidor, 1);
            pthread_join(cons1, NULL);
            pthread_join(prod1, NULL);
            break;
        // Condição de saída
        case 3:
            exit(0);
            break;
        }
    }
}