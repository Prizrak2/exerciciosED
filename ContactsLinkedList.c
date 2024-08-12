#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Contato { 
    char nome[50]; 
    char telefone[15]; 
    struct Contato* prox; 
} Contato; 

void inicializarLista(Contato **contato){
    *contato = malloc(sizeof(Contato));
    if(!(*contato)){
        printf("Erro ao inicializar Lista");
        return;
    }
    (*contato)->prox = NULL;
}

int estaVazia(Contato *contato){
    return (contato->prox == NULL);
}

void inserir(Contato* contato, char* nome, char* telefone) {
    Contato* aux = contato;
    while (aux->prox)
        aux = aux->prox;

    aux->prox = malloc(sizeof(Contato));
    if (!(aux->prox)) {
        printf("Erro ao alocar memória para novo contato");
        return;
    }
    strcpy(aux->prox->nome, nome);
    strcpy(aux->prox->telefone, telefone);
    aux->prox->prox = NULL;
}

void mostrarContatos(Contato *contato){
    if (estaVazia(contato)){
        printf("A lista esta vazia");
        return;
    }
    int i = 1;
    Contato *novo = contato;
    while (novo->prox){
        novo = novo->prox;
        printf("Contato %d:\nNome: %s \nTelefone: %s\n\n", i, novo->nome, novo->telefone);
        i++;
    }
}

void remover(Contato *contato, char* nome){
    Contato* aux = contato;
    while (strcmp(aux->prox->nome, nome) != 0){
        aux = aux->prox;
        if (!aux->prox){
            printf("Contato nao encontrado!\n");
            return;
        }
    }
    Contato* temp = aux->prox;
    aux->prox = aux->prox->prox;
    free(temp);
}

void op(){
    Contato* contato;
    inicializarLista(&contato);
    int op = -1;
    char nome[50], telefone[15];
    while (op){
        printf("1 - Adicionar Contato\n2 - Remover Contato\n3 - Mostrar Contatos\n0 - Sair\nInsira a Opcao Desejada:\n");
        scanf("%d", &op);
        getchar();
        
        switch (op){
        case 1:
            printf("Insira o Nome do Contato:\n");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = '\0';
            printf("Insira o Telefone do Contato:\n");
            fgets(telefone, sizeof(telefone), stdin);
            telefone[strcspn(telefone, "\n")] = '\0';
            inserir(contato, nome, telefone);
        break;
        case 2:
            printf("Insira o Nome do Contato que deseja Remover:\n");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = '\0';
            remover(contato, nome);
        break;
        case 3:
            mostrarContatos(contato);
        break;
        case 0:
            printf("Saindo...");
        break;
        default:
            printf("Opcao Invalida!");
        break;
        }
    }
}

int main(){
    op();

    return 0;
}