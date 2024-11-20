#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Estrutura do nó da Árvore AVL
typedef struct NoAVL {
    int valor;
    struct NoAVL* esquerda;
    struct NoAVL* direita;
    int altura;
} NoAVL;

// Função para obter a altura de um nó
int obterAltura(NoAVL* no) {
    return (no == NULL) ? 0 : no->altura;
}

// Função para obter o fator de balanceamento de um nó
int obterFatorBalanceamento(NoAVL* no) {
    return (no == NULL) ? 0 : obterAltura(no->esquerda) - obterAltura(no->direita);
}

// Função para obter o máximo entre dois números
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Função para criar um novo nó
NoAVL* criarNo(int valor) {
    NoAVL* no = (NoAVL*)malloc(sizeof(NoAVL));
    no->valor = valor;
    no->esquerda = NULL;
    no->direita = NULL;
    no->altura = 1;
    return no;
}

// Rotação simples à direita (RR)
NoAVL* rotacaoDireita(NoAVL* y) {
    NoAVL* x = y->esquerda;
    NoAVL* T2 = x->direita;
    x->direita = y;
    y->esquerda = T2;
    y->altura = max(obterAltura(y->esquerda), obterAltura(y->direita)) + 1;
    x->altura = max(obterAltura(x->esquerda), obterAltura(x->direita)) + 1;
    return x;
}

// Rotação simples à esquerda (LL)
NoAVL* rotacaoEsquerda(NoAVL* x) {
    NoAVL* y = x->direita;
    NoAVL* T2 = y->esquerda;
    y->esquerda = x;
    x->direita = T2;
    x->altura = max(obterAltura(x->esquerda), obterAltura(x->direita)) + 1;
    y->altura = max(obterAltura(y->esquerda), obterAltura(y->direita)) + 1;
    return y;
}

// Função para inserir um nó na Árvore AVL
NoAVL* inserir(NoAVL* no, int valor) {
    if (no == NULL) return criarNo(valor);
    if (valor < no->valor)
        no->esquerda = inserir(no->esquerda, valor);
    else if (valor > no->valor)
        no->direita = inserir(no->direita, valor);
    else
        return no;

    no->altura = 1 + max(obterAltura(no->esquerda), obterAltura(no->direita));
    int fatorBalanceamento = obterFatorBalanceamento(no);

    if (fatorBalanceamento > 1 && valor < no->esquerda->valor)
        return rotacaoDireita(no);

    if (fatorBalanceamento < -1 && valor > no->direita->valor)
        return rotacaoEsquerda(no);

    if (fatorBalanceamento > 1 && valor > no->esquerda->valor) {
        no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    }

    if (fatorBalanceamento < -1 && valor < no->direita->valor) {
        no->direita = rotacaoDireita(no->direita);
        return rotacaoEsquerda(no);
    }

    return no;
}

// Função para encontrar o menor valor em uma árvore
NoAVL* menorValor(NoAVL* no) {
    NoAVL* atual = no;
    while (atual->esquerda != NULL)
        atual = atual->esquerda;
    return atual;
}

// Função para remover um nó da Árvore AVL
NoAVL* remover(NoAVL* raiz, int valor) {
    if (raiz == NULL) return raiz;

    if (valor < raiz->valor)
        raiz->esquerda = remover(raiz->esquerda, valor);
    else if (valor > raiz->valor)
        raiz->direita = remover(raiz->direita, valor);
    else {
        if ((raiz->esquerda == NULL) || (raiz->direita == NULL)) {
            NoAVL* temp = raiz->esquerda ? raiz->esquerda : raiz->direita;
            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else
                *raiz = *temp;
            free(temp);
        } else {
            NoAVL* temp = menorValor(raiz->direita);
            raiz->valor = temp->valor;
            raiz->direita = remover(raiz->direita, temp->valor);
        }
    }

    if (raiz == NULL) return raiz;

    raiz->altura = 1 + max(obterAltura(raiz->esquerda), obterAltura(raiz->direita));
    int fatorBalanceamento = obterFatorBalanceamento(raiz);

    if (fatorBalanceamento > 1 && obterFatorBalanceamento(raiz->esquerda) >= 0)
        return rotacaoDireita(raiz);

    if (fatorBalanceamento > 1 && obterFatorBalanceamento(raiz->esquerda) < 0) {
        raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
        return rotacaoDireita(raiz);
    }

    if (fatorBalanceamento < -1 && obterFatorBalanceamento(raiz->direita) <= 0)
        return rotacaoEsquerda(raiz);

    if (fatorBalanceamento < -1 && obterFatorBalanceamento(raiz->direita) > 0) {
        raiz->direita = rotacaoDireita(raiz->direita);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

// Funções de percursos
void preOrdem(NoAVL* raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->valor);
        preOrdem(raiz->esquerda);
        preOrdem(raiz->direita);
    }
}

void inOrdem(NoAVL* raiz) {
    if (raiz != NULL) {
        inOrdem(raiz->esquerda);
        printf("%d ", raiz->valor);
        inOrdem(raiz->direita);
    }
}

void posOrdem(NoAVL* raiz) {
    if (raiz != NULL) {
        posOrdem(raiz->esquerda);
        posOrdem(raiz->direita);
        printf("%d ", raiz->valor);
    }
}

// Função principal
int main() {
    NoAVL* raiz = NULL;
    srand(time(NULL));

    printf("Inserindo valores aleatórios na Árvore AVL...\n");
    for (int i = 0; i < 10; i++) {
        int valor = rand() % 100;
        printf("Inserindo: %d\n", valor);
        raiz = inserir(raiz, valor);
    }

    printf("\nPercurso em Pré-Ordem: ");
    preOrdem(raiz);
    printf("\n");

    printf("Percurso em In-Ordem: ");
    inOrdem(raiz);
    printf("\n");

    printf("Percurso em Pós-Ordem: ");
    posOrdem(raiz);
    printf("\n");

    printf("\nRemovendo valores da Árvore AVL...\n");
    for (int i = 0; i < 3; i++) {
        int valor = rand() % 100;
        printf("Removendo: %d\n", valor);
        raiz = remover(raiz, valor);
    }

    printf("\nPercurso em In-Ordem após remoção: ");
    inOrdem(raiz);
    printf("\n");

    return 0;
}
