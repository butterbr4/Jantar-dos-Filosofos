# Relatório: O Problema do Jantar dos Filósofos

## Introdução

O Problema do Jantar dos Filósofos é um clássico problema de sincronização em sistemas operacionais e concorrência. Ele descreve uma situação em que um grupo de filósofos está sentado em uma mesa redonda, onde cada filósofo alterna entre pensar e comer. Entre cada par de filósofos, há um garfo compartilhado. O objetivo é evitar que ocorram deadlocks (interbloqueios) e starvation (inanição) durante o jantar.

## Lógica do Código

O código implementado em C aborda o Problema do Jantar dos Filósofos utilizando threads e mutexes para sincronizar as ações dos filósofos. Aqui está uma explicação da lógica do código:

1. Definição das constantes e das estruturas de dados: São definidos o número de filósofos (N) e os estados possíveis de um filósofo (PENSAR, FOME e COMER). Também é definida a estrutura `Filosofo` que contém o identificador do filósofo e o seu estado.

2. Declaração das variáveis globais: São declaradas as variáveis globais `filosofos` (um array de `Filosofo`), `mutex` (um mutex para controlar o acesso à região crítica) e `cond` (um array de variáveis de condição para sincronizar os filósofos).

3. Implementação das funções `filosofo`, `agarraGarfo`, `deixaGarfo` e `testar`:
   - `filosofo`: É a função executada por cada thread de filósofo. Ela entra em um loop infinito onde o filósofo alterna entre pensar, agarrar garfos e deixar garfos.
   - `agarraGarfo`: O filósofo tenta agarrar os garfos. Se não conseguir, ele aguarda até que possa comer.
   - `deixaGarfo`: O filósofo deixa os garfos após comer, e notifica os filósofos vizinhos para que possam tentar agarrar os garfos.
   - `testar`: Verifica se o filósofo pode comer (se ele está com fome e os vizinhos não estão comendo). Se sim, o filósofo come.

4. Função `main`: É a função principal do programa. Ela inicializa as variáveis, cria as threads para os filósofos e aguarda a finalização das threads.

## Solução de Deadlocks e Starvation

O código implementado apresenta soluções para evitar deadlocks e starvation:

1. Utilização de mutex: O mutex `mutex` é usado para garantir que apenas um filósofo por vez possa acessar a região crítica (os garfos). Isso evita que dois filósofos peguem o mesmo garfo ao mesmo tempo.

2. Uso de variáveis de condição: As variáveis de condição `cond` são usadas para sincronizar os filósofos e permitir que eles esperem quando não conseguem agarrar os garfos. Essas variáveis são notificadas quando os garfos são deixados pelos filósofos vizinhos.

3. Ordem de aquisição dos garfos:

 Para evitar o deadlock, foi definida uma ordem fixa para a aquisição dos garfos. Cada filósofo sempre pega primeiro o garfo da sua esquerda e depois o garfo da sua direita. Essa ordem é importante para prevenir o deadlock em situações onde todos os filósofos tentam pegar o garfo da sua direita ao mesmo tempo.

4. Liberação dos garfos: Para evitar a inanição (starvation), um filósofo só deixa os garfos após comer, o que garante que todos os filósofos terão a oportunidade de comer.

## Resultados

O código implementado demonstrou uma solução funcional para o Problema do Jantar dos Filósofos, evitando deadlocks e starvation. Durante a execução, cada filósofo alterna entre os estados de pensar, ter fome, comer e deixar os garfos.

Os resultados podem variar dependendo do ambiente de execução, como o sistema operacional e a capacidade de processamento. No entanto, a solução implementada garante que todos os filósofos tenham a oportunidade de comer e evita situações em que um filósofo fique indefinidamente faminto ou bloqueado.

É importante destacar que, mesmo com a implementação correta, podem ocorrer situações de contenção em que os filósofos precisam esperar por um garfo. Essa contenção pode resultar em um desempenho menor em termos de tempo de resposta e utilização de recursos.

Em resumo, o código soluciona o Problema do Jantar dos Filósofos usando mutexes e variáveis de condição para garantir a sincronização correta entre os filósofos, evitando deadlocks e starvation.
