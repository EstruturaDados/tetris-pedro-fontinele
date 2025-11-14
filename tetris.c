#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILA 5   // tamanho fixo da fila circular

/*
    Struct Peca
    -----------
    Representa uma peça do jogo Tetris Stack.
    A peça contém:
      - nome: tipo da peça (I, O, T, L)
      - id: identificador numérico único
*/
typedef struct {
    char nome;
    int id;
} Peca;

// Vetor representando a fila circular
Peca fila[MAX_FILA];
int inicio = 0;     // posição do primeiro elemento da fila
int fim = 0;        // posição de inserção
int quantidade = 0; // quantidade atual de elementos na fila

int contadorID = 0; // gera IDs únicos para as peças

// ------------------------ FUNÇÃO GERAR PEÇA ------------------------

/*
    gerarPeca()
    -----------
    Gera automaticamente uma peça nova.
    Os nomes das peças são escolhidos aleatoriamente.
*/
Peca gerarPeca() {
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'};
    int indice = rand() % 4;
    nova.nome = tipos[indice];
    nova.id = contadorID++;
    return nova;
}

// ------------------------ FUNÇÃO ENQUEUE ------------------------

/*
    enqueue()
    ---------
    Insere uma nova peça no final da fila, se houver espaço.
*/
void enqueue() {
    if (quantidade == MAX_FILA) {
        printf("\nA fila esta cheia! Nao e possivel inserir nova peça.\n");
        return;
    }

    fila[fim] = gerarPeca();
    fim = (fim + 1) % MAX_FILA;
    quantidade++;

    printf("\nPeca inserida com sucesso!\n");
}

// ------------------------ FUNÇÃO DEQUEUE ------------------------

/*
    dequeue()
    ---------
    Remove a peça da frente da fila, simulando "jogar a peça".
*/
void dequeue() {
    if (quantidade == 0) {
        printf("\nA fila esta vazia! Nao ha peças para jogar.\n");
        return;
    }

    Peca removida = fila[inicio];
    inicio = (inicio + 1) % MAX_FILA;
    quantidade--;

    printf("\nPeca [%c %d] jogada com sucesso!\n", removida.nome, removida.id);
}

// ------------------------ FUNÇÃO EXIBIR ------------------------

/*
    exibirFila()
    ------------
    Mostra todos os elementos da fila circular na ordem correta.
*/
void exibirFila() {
    printf("\n===== FILA DE PECAS =====\n");

    if (quantidade == 0) {
        printf("(Fila vazia)\n");
        return;
    }

    int i = inicio;
    for (int c = 0; c < quantidade; c++) {
        printf("[%c %d] ", fila[i].nome, fila[i].id);
        i = (i + 1) % MAX_FILA;
    }

    printf("\n");
}

// ------------------------ FUNÇÃO PRINCIPAL ------------------------

int main() {
    srand(time(NULL)); // inicializa gerador de números aleatórios

    // Inicializa fila com 5 peças, conforme requerido
    for (int i = 0; i < MAX_FILA; i++) {
        enqueue();
    }

    int opcao;

    while (1) {
        exibirFila();

        printf("\n===== MENU =====\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dequeue();
                break;

            case 2:
                enqueue();
                break;

            case 0:
                printf("\nEncerrando o programa...\n");
                return 0;

            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    }

    return 0;
}
