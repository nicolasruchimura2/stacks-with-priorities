#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct Pessoa {
    char BI[15];
    char nome[50];
    char apelido[50];
    Data data_nascimento;
    struct Pessoa *prox;
} Pessoa;

Pessoa* criarPessoa(const char* BI, const char* nome, const char* apelido, int dia, int mes, int ano) {
    Pessoa* nova = (Pessoa*)malloc(sizeof(Pessoa));
    strcpy(nova->BI, BI);
    strcpy(nova->nome, nome);
    strcpy(nova->apelido, apelido);
    nova->data_nascimento.dia = dia;
    nova->data_nascimento.mes = mes;
    nova->data_nascimento.ano = ano;
    nova->prox = NULL;
    return nova;
}

int comparar(Pessoa *a, Pessoa *b) {
    int cmp = strcmp(a->nome, b->nome);
    if (cmp != 0) return cmp;
    
    else if (cmp == 0) {
        cmp = strcmp(a->apelido, b->apelido);
    }
    return cmp;
}

void inserirOrdenado(Pessoa **inicio, Pessoa *nova) {
    if(*inicio == NULL || comparar(nova, *inicio) < 0) {
        nova->prox = *inicio;
        *inicio = nova;
    } else {
        Pessoa *atual = *inicio;
        while(atual->prox != NULL && comparar(nova, atual->prox) >= 0) {
            atual = atual->prox;
        }
        nova->prox = atual->prox;
        atual->prox = nova;     
    }
}

void removerPessoa(Pessoa **inicio) {
    if (*inicio == NULL) {
        printf("Lista vazia, nada a remover.\n");    
        return;
    }

    Pessoa *temp = *inicio;
    *inicio = (*inicio)->prox;
    free(temp);
}

void mostrarLista(Pessoa *inicio) {
    Pessoa *atual = inicio;
    while(atual != NULL) {
        printf("BI: %s, Nome: %s, Apelido: %s, Data de Nascimento: %02d/%02d/%04d\n",
               atual->BI, atual->nome, atual->apelido,
               atual->data_nascimento.dia,
               atual->data_nascimento.mes,
               atual->data_nascimento.ano);
        atual = atual->prox;
    }
    printf("--------------------------\n");
}

int main() { 
    Pessoa *lista = NULL;

    inserirOrdenado(&lista, criarPessoa("12345678", "Joao", "Silva", 10, 5, 1990));
    inserirOrdenado(&lista, criarPessoa("87654321", "Ana", "Costa", 3, 8, 1985));
    inserirOrdenado(&lista, criarPessoa("87654321", "Ana", "Almeida", 5, 2, 1981));
    inserirOrdenado(&lista, criarPessoa("55555555", "Bruno", "Almeida", 20, 12, 1992));
    inserirOrdenado(&lista, criarPessoa("11111111", "Carla", "Costa", 1, 1, 1991));

    printf("Lista de Pessoas:\n");
    mostrarLista(lista);

    printf("Removendo a primeira pessoa da lista...\n");
    removerPessoa(&lista);
    mostrarLista(lista);

    // Liberar memória restante
    while (lista != NULL) {
        removerPessoa(&lista);
    }

    return 0;
}