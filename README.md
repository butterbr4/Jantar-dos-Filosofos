# Relatório: Problema do Jantar dos Filósofos

## Introdução

O problema do jantar dos filósofos é um problema clássico de sincronização em ciência da computação, proposto por Edsger Dijkstra em 1965. Ele descreve cinco filósofos sentados em uma mesa circular, onde cada filósofo tem um prato de espaguete e um garfo à sua esquerda e à sua direita. Os filósofos podem alternar entre dois estados: pensar e comer. Para comer, um filósofo precisa pegar os dois garfos adjacentes. O problema consiste em encontrar uma solução que permita que todos os filósofos comam sem entrar em impasse (deadlock) ou passar fome (starvation).

## Lógica do Código

O código utiliza a biblioteca `pthread` para criar uma thread para cada filósofo. Cada filósofo é representado por uma estrutura que contém seu identificador e estado atual (pensar, fome ou comer). Um mutex é usado para controlar o acesso aos recursos compartilhados (garfos), e uma condição é associada a cada filósofo para sinalizar quando ele pode comer.

A função `filosofo` é a função principal executada por cada thread de filósofo. Ela faz com que o filósofo pense por um tempo, tente pegar os garfos, coma e depois devolva os garfos. As funções `agarraGarfo` e `deixaGarfo` são responsáveis por controlar o acesso aos garfos e atualizar o estado dos filósofos.

A função `testar` é usada para verificar se um filósofo pode comer. Um filósofo pode comer se estiver com fome e seus vizinhos não estiverem comendo. Se um filósofo pode comer, seu estado é atualizado para comer, e a condição associada a ele é sinalizada.

### Solução para Deadlocks e Starvation

A solução para evitar deadlocks e starvation é garantir que um filósofo só possa comer se ambos os vizinhos não estiverem comendo. Isso é feito na função `testar`. Além disso, quando um filósofo termina de comer e devolve os garfos, a função `deixaGarfo` testa se os vizinhos podem comer, garantindo que eles não passem fome.

## Resultados

O programa funciona corretamente, permitindo que todos os filósofos comam sem entrar em impasse ou passar fome. A saída do programa mostra o estado de cada filósofo e as ações realizadas (pegar garfos, comer e devolver garfos).

## Problemas Enfrentados

Os principais desafios ao implementar a solução foram:

1. Garantir que os filósofos não entrem em deadlock ao tentar pegar os garfos simultaneamente.
2. Evitar que os filósofos passem fome, garantindo que todos tenham a chance de comer.
3. Sincronizar o acesso aos recursos compartilhados (garfos) usando mutex e condições.


# Orientações para compilação e execução do código

## Compilação
Para compilar o código abra no terminal o diretorio que contenha o arquivo do código, e executo o seguinte comando:

```
gcc -o jantar_dos_filosofos jantar_dos_filosofos.c -lpthread
```

## Execução
Para execução ainda no mesmo diretório digite o seguinte comando no terminal:

```
./jantar_dos_filosofos
```
