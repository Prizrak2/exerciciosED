/*
 * [Resumo]
 * Algoritmo de Lista em vetor com implementação em uma
 * Sacola de uma padaria
 * Requisitado pelo Prof. Fabrício
 * 
 * [Autor]
 * Lucas Pereira Nunes

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 100

// Estrutura para armazenar os detalhes do Item
typedef struct {
    char item[50];
    int quantidade;
} Item;

// Estrutura da lista de Itens em vetor
typedef struct {
    Item itens[MAX_ITENS];
    int tamanho;
} Sacola;

// Função para inicializar a lista
void inicializarLista(Sacola *sacola) {
    sacola->tamanho = 0;
}

// Função para verificar se a lista está vazia
int listaVazia(Sacola *sacola) {
    return sacola->tamanho == 0;
}

// Função para verificar se a lista está cheia
int listaCheia(Sacola *sacola) {
    return sacola->tamanho == MAX_ITENS;
}

// Função para adicionar um novo Item na Sacola
void adicionarItem(Sacola *sacola, Item novoItem) {
    int encontrado = 0;
    if (listaCheia(sacola)) {
        printf("Erro: A Sacola esta Cheia!\n");
        return;
    }
    for (int i = 0; i < sacola->tamanho; i++) {
        if (strcmp(sacola->itens[i].item, novoItem.item) == 0) {
            encontrado = 1;
            sacola->itens[i].quantidade += novoItem.quantidade;
        }
    }
    if(!encontrado){
        sacola->itens[sacola->tamanho] = novoItem;
        sacola->tamanho++;
    }
}

// Função para remover um Item da sacola
void removerItem(Sacola *sacola, char *nomeItem, int quantidade) {
    if (listaVazia(sacola)) {
        printf("Erro: A Sacola esta vazia!\n");
        return;
    }
    int encontrado = 0;
    for (int i = 0; i < sacola->tamanho; i++) {
        if (strcmp(sacola->itens[i].item, nomeItem) == 0) {
            encontrado = 1;
            if (sacola->itens[i].quantidade >= quantidade) {
                sacola->itens[i].quantidade -= quantidade;
                if (sacola->itens[i].quantidade == 0) {
                    for (int j = i; j < sacola->tamanho - 1; j++) {
                        sacola->itens[j] = sacola->itens[j + 1];
                    }
                    sacola->tamanho--;
                }
            } else {
                printf("Erro: A quantidade especificada (%d) excede a quantidade de %s na sacola.\n", quantidade, nomeItem);
            }
            break;
        }
    }
    if (!encontrado) {
        printf("Item '%s' nao encontrado na sacola.\n", nomeItem);
    }
}

// Função para mostrar a lista de Itens na sacola
void mostrarLista(Sacola *sacola) {
    if (listaVazia(sacola)) {
        printf("A Sacola esta vazia.\n");
        return;
    }
    printf("Lista de Itens dentro da sacola:\n");
    for (int i = 0; i < sacola->tamanho; i++) {
        printf("%dx %s\n", sacola->itens[i].quantidade, sacola->itens[i].item);
    }
}

// Função para imprimir o menu do programa ao usuário
void menu() {
    printf("Escolha:\n1 - Adicionar Item a Sacola\n2 - Remover Item da Sacola\n3 - Mostrar Itens da Sacola\n0 - Sair\n-->");
}

// Função principal do Programa
int main() {
    Sacola sacola;
    inicializarLista(&sacola);

    int op;
    int quantidade;
    char nomeItem[50];
    
    Item novoItem;

    do {
        menu();
        scanf("%d", &op);
        getchar();

        switch(op) {
            case 1:
                printf("Insira o Nome do Item que queira adicionar na sacola:\n");
                fgets(novoItem.item, sizeof(novoItem.item), stdin);
                novoItem.item[strcspn(novoItem.item, "\n")] = '\0';
                printf("Insira a quantidade:\n");
                scanf("%d", &novoItem.quantidade);
                adicionarItem(&sacola, novoItem);
                break;
            case 2:
                printf("Insira o nome do Item que queira remover da sacola:\n");
                fgets(nomeItem, sizeof(nomeItem), stdin);
                nomeItem[strcspn(nomeItem, "\n")] = '\0';
                printf("Insira a quantidade de %s que deseja remover:\n", nomeItem);
                scanf("%d", &quantidade);
                getchar();
                removerItem(&sacola, nomeItem, quantidade);
                break;
            case 3:
                mostrarLista(&sacola);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                puts("Opção inválida");
                break;
        }
    } while (op != 0);
    return 0;
}
