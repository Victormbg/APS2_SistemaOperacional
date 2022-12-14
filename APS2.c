/*
Nome: Victor Manuel De Barros Garcia
Matricula: 20102283
Sistemas Operacionais
BS - INF0601N - 2022-2

TEMA: Problema do Produtor-Consumidor
• Dois processos compartilham um buffer de tamanho fixo
• O produtor insere informação no buffer
• O consumidor remove informação do buffer
*/
// Importando a biblioteca pthread para as funcoes do pthread
#include <pthread.h>
// Importando a biblioteca stdio para as funcoes de printf
#include <stdio.h>
// Importando a biblioteca windows para as funcoes do sleep no windows
#include <windows.h>
// Importando a biblioteca linux para as funcoes do sleep no linux
#include <unistd.h>

#define FALSE 0
#define TRUE 1
/*
Mutex é usado como um primitivo de sincronização em situações
onde o recurso tem que ser compartilhado com múltiplas thread simultaneamente.
Os objetos mutex nomeados são usados para fazer a sincronização interprocessos,
porque vários aplicativos podem acessar o mesmo objeto mutex.

Declaracao das variaveis de condicao (MUTEX):
*/
pthread_mutex_t mutex;

// Buffer (Uma área de armazenamento temporário é chamada de buffer) 
#define BUFFERVAZIO 0
#define BUFFERCHEIO 1
int buffer;
int estado = BUFFERVAZIO;

// Função para produzir um item e adicioná-lo ao buffer
void produtor(int id)
{
    int i = 0;
    int item;
    int aguardar;

    printf("Inicio produtor %d \n", id);
    while (i < 5)
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
    return;
}

// Função para consumir um item e removê-lo de buffer
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
    return;
}

int main()
{
    pthread_t prod1;
    pthread_t prod2;
    pthread_t prod3;
    pthread_t cons1;
    pthread_t cons2;

    printf("Iniciando o Programa Produtor-Consumidor....\n");

    printf("\nIniciando variaveis de sincronizacao.\n");
    pthread_mutex_init(&mutex, NULL);

    printf("Disparando threads produtores\n");
    pthread_create(&prod1, NULL, (void *)produtor, 1);
    pthread_create(&prod2, NULL, (void *)produtor, 2);
    pthread_create(&prod3, NULL, (void *)produtor, 3);

    printf("Disparando threads consumidores\n");
    pthread_create(&cons1, NULL, (void *)consumidor, 1);
    pthread_create(&cons2, NULL, (void *)consumidor, 2);

    pthread_join(prod1, NULL);
    pthread_join(prod2, NULL);
    pthread_join(prod3, NULL);

    printf("\nTerminado processo Produtor-Consumidor.\n\n");
}