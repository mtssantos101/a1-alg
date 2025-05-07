#ifndef LANCAMENTOS_H
#define LANCAMENTOS_H

typedef struct {
    int contaNumero;
    char data[11];
    float valor;
    char descricao[100];
} Lancamento;

void fazerLancamento();
void listarLancamentos();
void excluirLancamento();

#endif
