#include <stdio.h>
#include <stdlib.h>

#define MAX 5

// Estrutura da peça
typedef struct {
    char nome;
    int id;
} Peca;

// Estrutura da fila
typedef struct {
    Peca itens[MAX];
    int inicio;
    int fim;
    int total;
} Fila;

// Inicializa a fila
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

// Verifica se está vazia
int filaVazia(Fila *f) {
    return f->total == 0;
}

// Verifica se está cheia
int filaCheia(Fila *f) {
    return f->total == MAX;
}

// Gera uma peça automaticamente
Peca gerarPeca(int id) {
    Peca p;
    char tipos[] = {'I', 'O', 'T', 'L'};

    p.nome = tipos[rand() % 4];
    p.id = id;

    return p;
}

// Inserir peça (enqueue)
void enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("\nFila cheia!\n");
        return;
    }

    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;
    f->total++;
}

// Remover peça (dequeue)
void dequeue(Fila *f) {
    if (filaVazia(f)) {
        printf("\nFila vazia!\n");
        return;
    }

    Peca removida = f->itens[f->inicio];

    printf("\nPeca jogada: [%c %d]\n",
           removida.nome,
           removida.id);

    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
}

// Mostrar fila
void mostrarFila(Fila *f) {
    int i;

    printf("\nFila de pecas:\n");

    for (i = 0; i < f->total; i++) {
        int pos = (f->inicio + i) % MAX;

        printf("[%c %d] ",
               f->itens[pos].nome,
               f->itens[pos].id);
    }

    printf("\n");
}

int main() {
    Fila fila;
    int opcao;
    int proximoId = 0;

    inicializarFila(&fila);

    // Preenche a fila com 5 peças iniciais
    for (int i = 0; i < MAX; i++) {
        enqueue(&fila, gerarPeca(proximoId));
        proximoId++;
    }

    do {
        mostrarFila(&fila);

        printf("\n1 - Jogar peca (dequeue)\n");
        printf("2 - Inserir nova peca (enqueue)\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {

        case 1:
            dequeue(&fila);
            break;

        case 2:
            enqueue(&fila, gerarPeca(proximoId));
            proximoId++;
            break;

        case 0:
            printf("\nEncerrando...\n");
            break;

        default:
            printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}