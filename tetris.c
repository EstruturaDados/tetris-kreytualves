#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

typedef struct {
    char nome;
    int id;
} Peca;

typedef struct {
    Peca itens[TAM_FILA];
    int inicio;
    int fim;
    int qtd;
} Fila;

typedef struct {
    Peca itens[TAM_PILHA];
    int topo;
} Pilha;

int proximoId = 0;

/* Gera uma nova peça */
Peca gerarPeca() {
    Peca p;
    char tipos[] = {'I', 'O', 'T', 'L'};

    p.nome = tipos[rand() % 4];
    p.id = proximoId++;

    return p;
}

/* FILA */

void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->qtd = 0;
}

int filaCheia(Fila *f) {
    return f->qtd == TAM_FILA;
}

int filaVazia(Fila *f) {
    return f->qtd == 0;
}

void enqueue(Fila *f, Peca p) {
    if (!filaCheia(f)) {
        f->itens[f->fim] = p;
        f->fim = (f->fim + 1) % TAM_FILA;
        f->qtd++;
    }
}

Peca dequeue(Fila *f) {
    Peca p = {'?', -1};

    if (!filaVazia(f)) {
        p = f->itens[f->inicio];
        f->inicio = (f->inicio + 1) % TAM_FILA;
        f->qtd--;
    }

    return p;
}

/* PILHA */

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int pilhaCheia(Pilha *p) {
    return p->topo == TAM_PILHA - 1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

void push(Pilha *p, Peca valor) {
    if (!pilhaCheia(p)) {
        p->itens[++p->topo] = valor;
    }
}

Peca pop(Pilha *p) {
    Peca valor = {'?', -1};

    if (!pilhaVazia(p)) {
        valor = p->itens[p->topo--];
    }

    return valor;
}

/* Exibir estruturas */

void mostrarEstado(Fila *fila, Pilha *pilha) {
    int i, pos;

    printf("\n===== ESTADO ATUAL =====\n");

    printf("Fila: ");
    for (i = 0; i < fila->qtd; i++) {
        pos = (fila->inicio + i) % TAM_FILA;
        printf("[%c %d] ", fila->itens[pos].nome, fila->itens[pos].id);
    }

    printf("\nPilha (Topo -> Base): ");
    for (i = pilha->topo; i >= 0; i--) {
        printf("[%c %d] ", pilha->itens[i].nome, pilha->itens[i].id);
    }

    printf("\n\n");
}

/* Mantém a fila sempre cheia */
void completarFila(Fila *fila) {
    while (fila->qtd < TAM_FILA) {
        enqueue(fila, gerarPeca());
    }
}

/* Troca peça da frente da fila com topo da pilha */
void trocarAtual(Fila *fila, Pilha *pilha) {
    if (filaVazia(fila) || pilhaVazia(pilha)) {
        printf("Troca impossivel!\n");
        return;
    }

    Peca temp = fila->itens[fila->inicio];
    fila->itens[fila->inicio] = pilha->itens[pilha->topo];
    pilha->itens[pilha->topo] = temp;

    printf("Troca realizada!\n");
}

/* Troca os 3 primeiros da fila com os 3 da pilha */
void trocaMultipla(Fila *fila, Pilha *pilha) {

    if (fila->qtd < 3 || pilha->topo < 2) {
        printf("Nao ha pecas suficientes para a troca!\n");
        return;
    }

    Peca tempFila[3];
    Peca tempPilha[3];

    int i;

    for (i = 0; i < 3; i++) {
        int pos = (fila->inicio + i) % TAM_FILA;
        tempFila[i] = fila->itens[pos];
    }

    for (i = 0; i < 3; i++) {
        tempPilha[i] = pilha->itens[pilha->topo - i];
    }

    for (i = 0; i < 3; i++) {
        int pos = (fila->inicio + i) % TAM_FILA;
        fila->itens[pos] = tempPilha[i];
    }

    for (i = 0; i < 3; i++) {
        pilha->itens[pilha->topo - i] = tempFila[i];
    }

    printf("Troca multipla realizada!\n");
}

int main() {

    srand(time(NULL));

    Fila fila;
    Pilha pilha;

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    completarFila(&fila);

    int opcao;

    do {

        mostrarEstado(&fila, &pilha);

        printf("1 - Jogar peca\n");
        printf("2 - Reservar peca\n");
        printf("3 - Usar peca reservada\n");
        printf("4 - Trocar atual\n");
        printf("5 - Troca multipla\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {

            case 1:
                if (!filaVazia(&fila)) {
                    Peca p = dequeue(&fila);
                    printf("Peca jogada: [%c %d]\n", p.nome, p.id);
                    completarFila(&fila);
                }
                break;

            case 2:
                if (!filaVazia(&fila) && !pilhaCheia(&pilha)) {
                    push(&pilha, dequeue(&fila));
                    completarFila(&fila);
                } else {
                    printf("Pilha cheia!\n");
                }
                break;

            case 3:
                if (!pilhaVazia(&pilha)) {
                    Peca p = pop(&pilha);
                    printf("Peca usada: [%c %d]\n", p.nome, p.id);
                } else {
                    printf("Pilha vazia!\n");
                }
                break;

            case 4:
                trocarAtual(&fila, &pilha);
                break;

            case 5:
                trocaMultipla(&fila, &pilha);
                break;

            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}