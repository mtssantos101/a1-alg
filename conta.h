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
void verConta(PConta conta);
PPConta alocarMemoriaEstrutura();
void limparTela();
void menu();
PConta acessarConta(PPConta contas, int *quantidade);
void verContas(PPConta contas, int quantidade);