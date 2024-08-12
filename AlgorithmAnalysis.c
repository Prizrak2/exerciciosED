#include <stdio.h>
#include "stdlib.h"
#include <time.h>

int randomizador ();
void insertSort(int v[], int tam);
void trocar(int *a, int *b);
void bubbleSort(int *vetor, int n);
void selectionSort(int v[], int n);
void op(int v[], int tam);
void merge(int vetor[], int comeco, int meio, int fim);
void mergeSort(int vetor[], int comeco, int fim);

int main(void) {
  int tam = 0;

  printf("Insira o tamanho do vetor: ");
  scanf("%d", &tam);
  
  int v[tam];
  
  srand(time(NULL));
  
  op(v, tam);
  
  return 0;
}

int randomizador() { 
  return rand() % 101; 
}

void insertSort(int v[], int tam){
  int i = 0, j = 0;
  int chave = 0;

  for(i = 1; i <= tam-1; i++){
    chave = v[i];
    j = i - 1;
    while(j >= 0 && v[j] > chave){
      v[j+1] = v[j];
      j = j - 1;
    }
    v[j+1] = chave;
  }
}

void trocar(int *a, int *b){
  int aux = *a;
  *a = *b;
  *b = aux;
}

void bubbleSort(int *vetor, int n){
  int i, j;
  for(i = 0; i < n-1; i++){
    for(j = 0; j < n-i-1; j++){
      if(vetor[j] < vetor[j+1]){
        trocar(&vetor[j], &vetor[j+1]);
      }
    }
  }
}

void selectionSort(int v[], int n) {
    int i, j, min_index;

    for (i = 0; i < n - 1; i++) {
        min_index = i;
        for (j = i + 1; j < n; j++) {
            if (v[j] < v[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            trocar(&v[i], &v[min_index]);
        }
    }
}

void op(int v[], int tam){
  printf("\nEscolha o tipo de algoritmo de ordenacao que deseja usar:\n1 - BubbleSort\n2 - SelectionSort\n3 - InsertSort\n4 - MergeSort\n0 - Sair\n\nEscolha de 0-4: ");
  int op = 0;
  int i = 0;
  time_t time_began;
  time_t time_ended;
  scanf("%d", &op);
  
  while (op != 0)
  {
    switch (op){
      case 1: 
        for (i = 0; i < tam; i++) {
          v[i] = randomizador();
        }
        time_began = time(NULL);
        bubbleSort(v, tam);
        time_ended = time(NULL);
        printf("\nOrdenacao Conluida!");

        printf("\nO algoritmo de odernacao BubbleSort demorou %ld segundos para ser concluido\n", (time_ended - time_began));
      break;

      case 2:
        for (i = 0; i < tam; i++) {
          v[i] = randomizador();
        }
        time_began = time(NULL);
        selectionSort(v, tam);
        time_ended = time(NULL);
        printf("\nOrdenacao Conluida!");

        printf("\nO algoritmo de odernacao SelectionSort demorou %ld segundos para ser concluido\n", (time_ended - time_began));
      break;

      case 3:
        for (i = 0; i < tam; i++) {
          v[i] = randomizador();
        }
        time_began = time(NULL);
        insertSort(v, tam);
        time_ended = time(NULL);
        printf("\nOrdenacao Conluida!");

        printf("\nO algoritmo de odernacao InsertSort demorou %ld segundos para ser concluido\n", (time_ended - time_began));
      break;

      case 4:
        for (i = 0; i < tam; i++) {
          v[i] = randomizador();
        }
        time_began = time(NULL);
        mergeSort(v, 0, tam);
        time_ended = time(NULL);

        printf("\nOrdenacao Conluida!");

        printf("\nO algoritmo de odernacao MergeSort demorou %ld segundos para ser concluido\n", (time_ended - time_began));
      break;

      case 0:
      break;

      default:
        printf("Escolha inválida!");
      break;
    }
    printf("\nEscolha o tipo de algoritmo de ordenacao que deseja usar:\n1 - BubbleSort\n2 - SelectionSort\n3 - InsertSort\n4 - MergeSort\n0 - Sair\n\nEscolha de 0-4: ");
    scanf("%d", &op);
  }
}

void merge(int vetor[], int comeco, int meio, int fim) {
    int com1 = comeco, com2 = meio+1, comAux = 0, tam = fim-comeco+1;
    int *vetAux;
    vetAux = (int*)malloc(tam * sizeof(int));

    while(com1 <= meio && com2 <= fim){
        if(vetor[com1] < vetor[com2]) {
            vetAux[comAux] = vetor[com1];
            com1++;
        } else {
            vetAux[comAux] = vetor[com2];
            com2++;
        }
        comAux++;
    }

    while(com1 <= meio){ 
        vetAux[comAux] = vetor[com1];
        comAux++;
        com1++;
    }

    while(com2 <= fim) {
        vetAux[comAux] = vetor[com2];
        comAux++;
        com2++;
    }

    for(comAux = comeco; comAux <= fim; comAux++){
        vetor[comAux] = vetAux[comAux-comeco];
    }
    
    free(vetAux);
}

void mergeSort(int vetor[], int comeco, int fim){
    if (comeco < fim) {
        int meio = (fim+comeco)/2;

        mergeSort(vetor, comeco, meio);
        mergeSort(vetor, meio+1, fim);
        merge(vetor, comeco, meio, fim);
    }
}