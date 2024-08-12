/*
 * [Resumo]
 * Algoritmo de Fila com implementação em uma
 * Lista de ordem de serviços para a Atividade enviada no Teams
 * Pelo professor Fabrício
 * 
 * [Autor]
 * Lucas Pereira Nunes

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SERVICES 100

// Estrutura para armazenar os detalhes do serviço
typedef struct {
    char cliente[50];
    char tipo_servico[50];
    char data_entrada[20];
} Servico;

// Estrutura da fila de atendimento de serviços
typedef struct {
    Servico servicos[MAX_SERVICES];
    int frente, fundo;
} FilaAtendimento;

// Função para inicializar a fila
void inicializarFila(FilaAtendimento *fila) {
    fila->frente = -1;
    fila->fundo = -1;
}

// Função para verificar se a fila está vazia
int filaVazia(FilaAtendimento *fila) {
    return (fila->frente == -1 && fila->fundo == -1);
}

// Função para verificar se a fila está cheia
int filaCheia(FilaAtendimento *fila) {
    return (fila->fundo + 1) == MAX_SERVICES;
}

// Função para adicionar um novo serviço na fila de atendimento
void adicionarServico(FilaAtendimento *fila, Servico novoServico) {
    if (filaCheia(fila)) {
        printf("Erro: A fila de atendimento esta cheia!\n");
        return;
    }
    if (filaVazia(fila)) {
        fila->frente = 0;
        fila->fundo = 0;
    } else {
        fila->fundo++;
    }
    fila->servicos[fila->fundo] = novoServico;
}

// Função para remover o próximo serviço da fila para ser atendido
void removerServico(FilaAtendimento *fila) {
    if (filaVazia(fila)) {
        printf("Erro: A fila de atendimento esta vazia!\n");
        return;
    }
    if (fila->frente == fila->fundo) {
        fila->frente = -1;
        fila->fundo = -1;
    } else {
        fila->frente++;
    }
}

// Função para mostrar a lista de serviços na fila
void mostrarFila(FilaAtendimento *fila) {
    if (filaVazia(fila)) {
        printf("A fila de atendimento esta vazia.\n");
        return;
    }
    printf("Lista de servicos na fila de atendimento:\n");
    int i = fila->frente;
    while (i <= fila->fundo) {
        printf("Cliente: %s, Tipo de Servico: %s, Data de Entrada: %s\n",
               fila->servicos[i].cliente, fila->servicos[i].tipo_servico,
               fila->servicos[i].data_entrada);
        i++;
    }
}

// Função para mostrar o próximo serviço na fila sem remover
void mostrarProximoServico(FilaAtendimento *fila) {
    if (filaVazia(fila)) {
        printf("Erro: A fila de atendimento esta vazia!\n");
        return;
    }
    printf("Proximo servico na fila de atendimento:\n");
    printf("Cliente: %s, Tipo de Servico: %s, Data de Entrada: %s\n",
           fila->servicos[fila->frente].cliente,
           fila->servicos[fila->frente].tipo_servico,
           fila->servicos[fila->frente].data_entrada);
}

// Função para imprimir o menu do programa ao usuário
void menu(){
    printf("Escolha\n1 - Enfilera\n2 - Retira\n3 - Mostrar Fila\n4 - Mostrar proximo serviço\n0 - Sair\n-->");
}

// Função principal do Programa
int main(){
    FilaAtendimento fi;
    inicializarFila(&fi);

    int op;
    
    Servico novoservico;

    do{
        menu();
        scanf("%d", &op);
        getchar();

        switch(op){
            case 1:
                printf("Insira o Nome do Cliente.\n");
                fgets(novoservico.cliente, sizeof(novoservico.cliente), stdin);
                novoservico.cliente[strcspn(novoservico.cliente, "\n")] = '\0';
                printf("Insira o tipo de Servico.\n");
                fgets(novoservico.tipo_servico, sizeof(novoservico.tipo_servico), stdin);
                novoservico.tipo_servico[strcspn(novoservico.tipo_servico, "\n")] = '\0';
                printf("Insira a Data de Entrada.\n");
                fgets(novoservico.data_entrada, sizeof(novoservico.data_entrada), stdin);
                novoservico.data_entrada[strcspn(novoservico.data_entrada, "\n")] = '\0';
                adicionarServico(&fi, novoservico);
                break;
            case 2:
                removerServico(&fi);
                break;
            case 3:
                mostrarFila(&fi);
                break;
            case 4:
                mostrarProximoServico(&fi);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                puts("Opção inválida");
                break;
        }
    }while(op!=0);
}