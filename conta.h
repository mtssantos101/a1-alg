#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct conta {
    char nomeUser[100];
    int id; 
    char tipo;
    float saldo;
} Conta, *PConta, **PPConta;


PPConta filePush(int *quantidade);
PConta criarConta();
void verConta(PPConta conta, int *quantidade);
PPConta alocarMemoriaEstrutura();
void limparTela();
void menu();