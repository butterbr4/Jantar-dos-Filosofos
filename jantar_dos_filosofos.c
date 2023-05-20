#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 5 // Número de filósofos
#define PENSAR 0 // Estado de pensar
#define FOME 1 // Estado de fome
#define COMER 2 // Estado de comer
#define ESQUERDA (filosofo->id + 4) % N // Índice do filósofo à esquerda
#define DIREITA (filosofo->id + 1) % N // Índice do filósofo à direita

typedef struct {
    int id; // Identificador do filósofo
    int estado; // Estado atual do filósofo (pensar, fome, comer)
} Filosofo;

Filosofo filosofos[N]; // Array de filósofos
pthread_mutex_t mutex; // Mutex para controlar o acesso aos recursos compartilhados
pthread_cond_t cond[N]; // Condições para cada filósofo

void *filosofo(void *arg);
void agarraGarfo(Filosofo *filosofo);
void deixaGarfo(Filosofo *filosofo);
void testar(Filosofo *filosofo);

// Função principal executada por cada thread de filósofo
void *filosofo(void *arg)
{
    Filosofo *filosofo = (Filosofo *)arg;
    while (1)
    {
        sleep(1); // Filósofo pensa por um tempo
        agarraGarfo(filosofo); // Filósofo tenta pegar os garfos
        sleep(1); // Filósofo come por um tempo
        deixaGarfo(filosofo); // Filósofo devolve os garfos
    }
}

// Função para tentar pegar os garfos
void agarraGarfo(Filosofo *filosofo)
{
    pthread_mutex_lock(&mutex); // Bloqueia o mutex
    filosofo->estado = FOME; // Filósofo está com fome
    printf("Filosofo %d tem fome.\n", filosofo->id + 1);
    testar(filosofo); // Testa se o filósofo pode comer
    if (filosofo->estado != COMER)
    {
        pthread_cond_wait(&cond[filosofo->id], &mutex); // Espera até que possa comer
    }
    pthread_mutex_unlock(&mutex); // Libera o mutex
    sleep(1);
}

// Função para devolver os garfos
void deixaGarfo(Filosofo *filosofo)
{
    pthread_mutex_lock(&mutex); // Bloqueia o mutex
    filosofo->estado = PENSAR; // Filósofo volta a pensar
    printf("Filosofo %d deixou os garfos %d e %d.\n", filosofo->id + 1, ESQUERDA + 1, filosofo->id + 1);
    printf("Filosofo %d esta a pensar.\n", filosofo->id + 1);
    testar(&filosofos[ESQUERDA]); // Testa se o filósofo à esquerda pode comer
    testar(&filosofos[DIREITA]); // Testa se o filósofo à direita pode comer
    pthread_mutex_unlock(&mutex); // Libera o mutex
}

// Função para testar se um filósofo pode comer
void testar(Filosofo *filosofo)
{
    if (filosofo->estado == FOME && filosofos[ESQUERDA].estado != COMER && filosofos[DIREITA].estado != COMER)
    {
        filosofo->estado = COMER; // Filósofo começa a comer
        sleep(2);
        printf("Filosofo %d agarrou os garfos %d e %d.\n", filosofo->id + 1, ESQUERDA + 1, filosofo->id + 1);
        printf("Filosofo %d esta a comer.\n", filosofo->id + 1);
        pthread_cond_signal(&cond[filosofo->id]); // Sinaliza que o filósofo está comendo
    }
}

int main()
{
    int i;
    pthread_t thread_id[N]; // Array de threads para os filósofos

    pthread_mutex_init(&mutex, NULL); // Inicializa o mutex
    for (i = 0; i < N; i++)
    {
        filosofos[i].id = i;
        filosofos[i].estado = PENSAR; // Inicializa o estado dos filósofos como "pensar"
        pthread_cond_init(&cond[i], NULL); // Inicializa as condições
    }

    for (i = 0; i < N; i++)
    {
        pthread_create(&thread_id[i], NULL, filosofo, &filosofos[i]); // Cria as threads dos filósofos
        printf("Filosofo %d esta a pensar.\n", i + 1);
    }

    for (i = 0; i < N; i++)
    {
        pthread_join(thread_id[i], NULL); // Aguarda as threads terminarem (nunca ocorre neste caso)
    }

    return 0;
}
