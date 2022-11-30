//Marcos Paulo C.Tavares
//19200427
//23-11-2022

#include <stdio.h>
#include <stdlib.h>
  
// Inicialize um mutex para 1
int mutex = 1;
  
// Número de slots completos como 0
int full = 0;
  
// Número de slots vazios como tamanho
// de buffer
int empty = 10, x = 0;
  
// Função para produzir um item e
// adicioná-lo ao buffer
void producer()
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
    printf("\nProducer produces"
           "item %d",
           x);
  
    // Aumente o valor do mutex em 1
    ++mutex;
}
  
// Função para consumir um item e
// removê-lo de buffer
void consumer()
{
    // Diminuir o valor do mutex em 1
    --mutex;
  
    // Diminuir o número de completos
    // slots por 1
    --full;
  
    // Aumente o número de vazios
    // slots por 1
    ++empty;
    printf("\nConsumer consumes "
           "item %d",
           x);
    x--;
  
    // Aumente o valor do mutex em 1
    ++mutex;
}
  
// Driver Code
int main()
{
    int n, i;
    printf("\n1. Press 1 for Producer"
           "\n2. Press 2 for Consumer"
           "\n3. Press 3 for Exit");
  
// Usando '#pragma omp parallel for'
// pode dar valor errado devido a
// problemas de sincronização.
  
// 'crítico' especifica que o código é
// executado por apenas um thread em um
// tempo ou seja, apenas um thread entra
// a seção crítica em um determinado momento
#pragma omp critical
  
    for (i = 1; i > 0; i++) {
  
        printf("\nEnter your choice:");
        scanf("%d", &n);
  
        // Switch Cases
        switch (n) {
        case 1:
  
            // Se mutex for 1 e vazio
            // é diferente de zero, então é
            // possível produzir
            if ((mutex == 1)
                && (empty != 0)) {
                producer();
            }
  
            
            // Caso contrário, imprime o buffer
            // está cheio
            else {
                printf("Buffer is full!");
            }
            break;
  
        case 2:
  
            // Se o mutex for 1 e completo
            // é diferente de zero, então é
            // possível consumir

            if ((mutex == 1)
                && (full != 0)) {
                consumer();
            }
  

            // Caso contrário, imprime Buffer
            // está vazia
            else {
                printf("Buffer is empty!");
            }
            break;
  
        // Condição de saída
        case 3:
            exit(0);
            break;
        }
    }
}

