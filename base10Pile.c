//Algoritmo que converte um número na base 10 para qualquer base entre 2 e 16

#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura de nó para a lista encadeada
typedef struct Node {
    int item;
    struct Node *next;
} Node;

// Definição da estrutura da pilha
typedef struct {
    Node *top;
} Stack;

Node* createNode(int item);
void initializeStack(Stack *stack);
int isEmpty(Stack *stack);
void push(Stack *stack, int item);
int pop(Stack *stack);
int top(Stack *stack);
void convertToBase(int number, int base);

int main() {
    int number;
    int base;

    printf("Digite o numero na base 10: ");
    scanf("%d", &number);

    printf("Digite a base para a conversao: ");
    scanf("%d", &base);

    if (base < 2 || base > 16) {
        printf("Erro: A base deve estar entre 2 e 16\n");
        return 1;
    }

    convertToBase(number, base);

    return 0;
}

// Função para criar um novo nó
Node* createNode(int item) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Erro ao alocar memoria\n");
        exit(1);
    }
    newNode->item = item;
    newNode->next = NULL;
    return newNode;
}

// Função para inicializar a pilha
void initializeStack(Stack *stack) {
    stack->top = NULL;
}

// Função para verificar se a pilha está vazia
int isEmpty(Stack *stack) {
    return stack->top == NULL;
}

// Função para empilhar um elemento na pilha
void push(Stack *stack, int item) {
    Node *newNode = createNode(item);
    newNode->next = stack->top;
    stack->top = newNode;
}

// Função para desempilhar um elemento da pilha
int pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Erro: a pilha esta vazia\n");
        exit(1);
    }
    int item = stack->top->item;
    stack->top = stack->top->next;
    return item;
}

// Função para acessar o elemento no topo da pilha
int top(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Erro: a pilha esta vazia\n");
        exit(1);
    }
    return stack->top->item;
}

// Função para converter um número da base 10 para uma base qualquer
void convertToBase(int number, int base) {
    Stack stack;
    initializeStack(&stack);
    int i = 0;

    while (number > 0) {
        int remainder = number % base;
        push(&stack, remainder);
        number /= base;
    }

    printf("O numero na base %d e: ", base);
    while (!isEmpty(&stack)) {
        if (top(&stack) >= 10){
            for (i = 10; i <= base; i++){
                if (i == top(&stack)){
                    printf("%c", top(&stack) + 55);
                }                
            }
        }
        if (top(&stack) <= 9){
            printf("%c", top(&stack) + '0');
        }
        pop(&stack);
    }
    printf("\n");
}
