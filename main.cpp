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