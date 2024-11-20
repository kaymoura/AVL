#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Estrutura do n� da �rvore AVL
typedef struct NoAVL {
    int valor;
    struct NoAVL* esquerda;
    struct NoAVL* direita;
    int altura;
} NoAVL;

// Fun��o para obter a altura de um n�
int obterAltura(NoAVL* no) {
    return (no == NULL) ? 0 : no->altura;
}

// Fun��o para obter o fator de balanceamento de um n�
int obterFatorBalanceamento(NoAVL* no) {
    return (no == NULL) ? 0 : obterAltura(no->esquerda) - obterAltura(no->direita);
}

// Fun��o para obter o m�ximo entre dois n�meros
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Fun��o para criar um novo n�
NoAVL* criarNo(int valor) {
    NoAVL* no = (NoAVL*)malloc(sizeof(NoAVL));
    no->valor = valor;
    no->esquerda = NULL;
    no->direita = NULL;
    no->altura = 1;
    return no;
}

// Rota��o simples � direita (RR)
NoAVL* rotacaoDireita(NoAVL* y) {
    NoAVL* x = y->esquerda;
    NoAVL* T2 = x->direita;
    x->direita = y;
    y->esquerda = T2;
    y->altura = max(obterAltura(y->esquerda), obterAltura(y->direita)) + 1;
    x->altura = max(obterAltura(x->esquerda), obterAltura(x->direita)) + 1;
    return x;
}

// Rota��o simples � esquerda (LL)
NoAVL* rotacaoEsquerda(NoAVL* x) {
    NoAVL* y = x->direita;
    NoAVL* T2 = y->esquerda;
    y->esquerda = x;
    x->direita = T2;
    x->altura = max(obterAltura(x->esquerda), obterAltura(x->direita)) + 1;
    y->altura = max(obterAltura(y->esquerda), obterAltura(y->direita)) + 1;
    return y;
}

// Fun��o para inserir um n� na �rvore AVL
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

// Fun��o para encontrar o menor valor em uma �rvore
NoAVL* menorValor(NoAVL* no) {
    NoAVL* atual = no;
    while (atual->esquerda != NULL)
        atual = atual->esquerda;
    return atual;
}

// Fun��o para remover um n� da �rvore AVL
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

// Fun��es de percursos
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

// Fun��o principal
int main() {
    NoAVL* raiz = NULL;
    srand(time(NULL));

    printf("Inserindo valores aleat�rios na �rvore AVL...\n");
    for (int i = 0; i < 10; i++) {
        int valor = rand() % 100;
        printf("Inserindo: %d\n", valor);
        raiz = inserir(raiz, valor);
    }

    printf("\nPercurso em Pr�-Ordem: ");
    preOrdem(raiz);
    printf("\n");

    printf("Percurso em In-Ordem: ");
    inOrdem(raiz);
    printf("\n");

    printf("Percurso em P�s-Ordem: ");
    posOrdem(raiz);
    printf("\n");

    printf("\nRemovendo valores da �rvore AVL...\n");
    for (int i = 0; i < 3; i++) {
        int valor = rand() % 100;
        printf("Removendo: %d\n", valor);
        raiz = remover(raiz, valor);
    }

    printf("\nPercurso em In-Ordem ap�s remo��o: ");
    inOrdem(raiz);
    printf("\n");

    return 0;
}
