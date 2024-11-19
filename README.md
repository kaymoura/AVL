# Árvore AVL - Implementação em C
Este repositório contém a implementação de uma Árvore AVL em C com operações como inserção(Aleatoria), remoção e percursos (Pré-Ordem, In-Ordem e Pós-Ordem), estrutura de dados autobalanceada baseada em árvores binárias de busca. A árvore é implementada com uma estrutura de nós, onde cada nó possui um valor (info), um ponteiro para o filho à esquerda (esq), um ponteiro para o filho à direita (dir) e um ponteiro para o pai (pai).

## Funcionalidades
### Estrutura do Nó AVL ( NoAVL)
 - Cada nó contém:
     - valor: O valor inteiro armazenado no nó.
     - esquerdae direita: Ponteiros para os nós filhos esquerdo e direito.
     - altura: Altura do nó na árvore para calcular o balanceamento.
  
 - Obter Altura ( obterAltura)
  Retorna a altura de um nó na árvore. A altura é usada para calcular o fator de balanceamento.

- Obter Fator de Balanceamento ( obterFatorBalanceamento)
  Calcula a diferença entre as alturas dos subárvores esquerda e direita de um nó.
     - Fator > 1 ou < -1 indica desbalanceamento, acionando rotações.

 - Rotação Simples à Direita ( rotacaoDireita)
   
  Corrige um desbalanceamento de tipo LL (quando o fator de balanceamento é maior que 1, e o nó desbalanceado fica à esquerda).

 - Rotação Simples à Esquerda ( rotacaoEsquerda)
   
  Corrige um desbalanceamento do tipo RR (quando o fator de balanceamento é menor que -1, e o nó desbalanceado fica à direita).

 - Inserção de Nós ( inserir)
      - Adicionado um novo nó à árvore mantendo as propriedades de uma árvore binária de busca.
      - Após a inserção, verifique e corrija desbalanceamentos (casos LL, RR, LR, RL) com rotações.
  
 - Percursos
      - Pré-Ordem ( preOrdem) : Percorrer a árvore na ordem: nó raiz → subárvore esquerda → subárvore direita.
      - Pós-Ordem ( posOrdem) : Percorrer a árvore na ordem: subárvore esquerda → subárvore direita → nó raiz.

## Como Usar

#### Pré-requisitos
Para rodar este código, você precisa de um compilador de C instalado, como o GCC ou o MinGW (para Windows). O código foi testado no Code::Blocks, mas deve funcionar em qualquer ambiente que suporte compilação C(Exemplo: [https://www.onlinegdb.com/online_c_compiler](https://www.onlinegdb.com/online_c_compiler) ).

#### Compilando o código
Clone o repositório para o seu ambiente local:

  git clone [https://github.com/kaymoura/AVL.git](https://github.com/kaymoura/AVL)

