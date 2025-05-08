#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Lancamento{
    int id;
    int id_conta;
    char data[11]; //"YYYY-MM-DD"
    float valor;
    char tipo; //'C' crédito, 'D' débito
    int efetivado; //0 futuro, 1 efetivado
}Lancamento, PLancamento;

Lancamento criaLancamento();
int removerLancamentosPorData(const char *dataRemover);
void listaLancamentosOrdenado();