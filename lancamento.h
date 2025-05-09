#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Lancamento{
    int id;
    int id_conta;
    char data[11]; //"YYYY-MM-DD"
    float valor;
    int acao; //1 deposito, 2 pagamento
    char tipo; //'C' crédito, 'D' débito
    int efetivado; //0 futuro, 1 efetivado
}Lancamento, PLancamento;

Lancamento criaLancamento();
int atualizarSaldoConta(int idConta, float valorLancamento, char tipo);
int removerLancamentosPorData(char *dataRemover);

void listaLancamentosOrdenado();