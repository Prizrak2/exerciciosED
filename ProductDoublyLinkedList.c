#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 100

typedef struct Product {
    char name[MAX_CHAR];
    float price;
    char size[4];
} Product;

typedef struct Node {
    Product *products;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct {
    Node* head;
    Node* tail;
} DoublyLinkedList;

DoublyLinkedList* createList();
void insertProduct(DoublyLinkedList* list, Product* products);
void searchProduct(DoublyLinkedList* list, char* name);
void removeProduct(DoublyLinkedList* list, char* name);
void printList(DoublyLinkedList* list);
void menu();
void saveToFile(DoublyLinkedList* list, const char* filename);
void loadFromFile(DoublyLinkedList* list, const char* filename);

int main() {
    DoublyLinkedList* list = createList();
    int op;
    loadFromFile(list, "produtos.txt");

    //menu de opções
    do {
        menu();
        scanf("%d", &op);
        getchar();

        Product* newProduct;
        char name[MAX_CHAR];

        switch(op) {
            case 1:
            //inserir
                newProduct = (Product*)malloc(sizeof(Product));
                printf("Insira o Nome do Produto a ser Criado:\n");
                fgets(newProduct->name, sizeof(newProduct->name), stdin);
                newProduct->name[strcspn(newProduct->name, "\n")] = '\0';

                printf("Insira o Preco do Produto a ser Criado:\n");
                scanf("%f", &newProduct->price);
                getchar();

                printf("Insira o Tamanho do Produto a ser Criado:\n");
                fgets(newProduct->size, sizeof(newProduct->size), stdin);
                newProduct->size[strcspn(newProduct->size, "\n")] = '\0';

                insertProduct(list, newProduct);

                saveToFile(list, "produtos.txt");
                break;
            case 2:
            //remover
                printf("Insira o nome do Produto a ser removido:\n");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                removeProduct(list, name);
                saveToFile(list, "produtos.txt");
                break;
            case 3:
            //imprimir lista
                printList(list);
                break;
            case 4:
            //consultar
                printf("Insira o nome do Produto a ser consultado:\n");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                searchProduct(list, name);
                break;
            case 0:
            //sair
                printf("Saindo...\n");
                break;
            default:
                puts("Opção inválida");
                break;
        }
    } while (op != 0);

    // Liberar memória
    Node* current = list->head;
    Node* next;
    while (current != NULL) {
        next = current->next;
        free(current->products);
        free(current);
        current = next;
    }
    free(list);
    return 0;
}

DoublyLinkedList* createList() {
    //criar lista
    DoublyLinkedList* list = (DoublyLinkedList*)malloc(sizeof(DoublyLinkedList));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void insertProduct(DoublyLinkedList* list, Product* products) {
    //função de inserir produto na lista
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->products = products;
    newNode->next = NULL;
    newNode->prev = NULL;

    if (list->head == NULL) {
        // lista está vazia
        list->head = newNode;
        list->tail = newNode;
    } else {
        Node* current = list->head;
        Node* prev = NULL;

        while (current != NULL && strcmp(current->products->name, products->name) < 0) {
            prev = current;
            current = current->next;
        }

        if (prev == NULL) {
            // insere na cabeça se for o primeiro elemento
            newNode->next = list->head;
            list->head->prev = newNode;
            list->head = newNode;
        } else if (current == NULL) {
            // Insere na cauda se for o ultimo elemento
            prev->next = newNode;
            newNode->prev = prev;
            list->tail = newNode;
        } else {
            // Insere no meio em casos padrão
            prev->next = newNode;
            newNode->prev = prev;
            newNode->next = current;
            current->prev = newNode;
        }
    }
}

void searchProduct(DoublyLinkedList* list, char* name){
    if (list->head == NULL) {
        // lista esta vazia
        printf("A lista esta vazia!\n");
        return;
    } else {
        Node* current = list->head;
        int found = 0;

        //percorre toda a lista e imprime todos os produtos correspondentes com o nome
        while (current != NULL){
            if(strcmp(current->products->name, name) == 0){
                printf("Name: %s, Price: %.2f, Size: %s\n", current->products->name, current->products->price, current->products->size);
                found = 1;
            }
            current = current->next;
        }

        if (!found) {
            printf("Produto nao encontrado!\n");
        }
        puts("");
    }
}

void removeProduct(DoublyLinkedList* list, char* name){
    //função de remover produto da lista
    if (list->head == NULL) {
        // lista esta vazia
        printf("A lista esta vazia!\n");
    } else {
        Node* current = list->head;

        while (current != NULL){
            if(strcmp(current->products->name, name) == 0){
                //se for o unico elemento:
                if(current->prev == NULL && current ->next == NULL){
                    list->head = NULL;
                    list->tail = NULL;
                //se for o ultimo elemento:
                } else if (current->next == NULL){
                    list->tail = current->prev;
                    list->tail->next = NULL;
                //se for o primeiro elemento:
                } else if (current->prev == NULL){
                    list->head = current->next;
                    list->head->prev = NULL;
                //se for um caso padrão:
                } else {
                    current->next->prev = current->prev;
                    current->prev->next = current->next;
                }
                //libera memória
                free(current->products);
                free(current);
                printf("Produto removido com sucesso!\n");
                return;
            } else {
                current = current->next;
            }
        }
        printf("Produto nao encontrado!\n");
    }
}

void printList(DoublyLinkedList* list) {
    //função de imprimir a lista de forma ordenada e desordenada simultaneamente
    Node* current = list->head;
    Node* currentTail = list->tail;
    printf("           Lista Ordenada              |            Lista Desordenada\n");
    while (current != NULL || currentTail != NULL) {
        printf("Name: %s, Price: %.2f, Size: %s  |  Name: %s, Price: %.2f, Size: %s\n",
                current->products->name, current->products->price, current->products->size,
                currentTail->products->name, currentTail->products->price, currentTail->products->size);
        current = current->next;
        currentTail = currentTail->prev;
    }
    printf("\n");
}

void menu(){
    //menu
    printf("Escolha:\n");
    printf("1 - Adicionar Produto\n");
    printf("2 - Remover Produto\n");
    printf("3 - Listar Produtos\n");
    printf("4 - Consultar Produto\n");
    printf("0 - Sair\n-->");
}

void saveToFile(DoublyLinkedList* list, const char* filename) {
    //função de salvar no arquivo
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Erro ao abrir arquivo para escrita");
        return;
    }

    Node* current = list->head;
    //percorre a lista e insere no arquivo
    while (current != NULL) {
        fprintf(file, "%s\n%f\n%s\n", current->products->name, current->products->price, current->products->size);
        current = current->next;
    }

    fclose(file);
    printf("Produtos salvos com sucesso no arquivo %s\n", filename);
}

void loadFromFile(DoublyLinkedList* list, const char* filename) {
    //função de carregar o arquivo
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erro ao abrir arquivo para leitura");
        return;
    }

    char name[MAX_CHAR];
    float price;
    char size[4];

    //percorre o arquivo e insere na lista
    while (fscanf(file, "%99[^\n]\n%f\n%3[^\n]\n", name, &price, size) == 3) {
        Product* newProduct = (Product*)malloc(sizeof(Product));
        strcpy(newProduct->name, name);
        newProduct->price = price;
        strcpy(newProduct->size, size);

        insertProduct(list, newProduct);
    }

    fclose(file);
    printf("Produtos carregados com sucesso do arquivo %s\n", filename);
}