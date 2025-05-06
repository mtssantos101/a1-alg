#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lancamentos.h"

void fazerLancamento() {
    Lancamento l;
    FILE *arq = fopen("lancamentos.txt", "a");
    if (!arq) {
        printf("Erro ao abrir arquivo de lançamentos.\n");
        return;
    }

    printf("\nNúmero da conta: ");
    scanf("%d", &l.contaNumero);
    getchar();

    printf("Data (AAAA-MM-DD): ");
    fgets(l.data, sizeof(l.data), stdin);
    l.data[strcspn(l.data, "\n")] = '\0';

    printf("Valor: ");
    scanf("%f", &l.valor);
    getchar();

    printf("Descrição: ");
    fgets(l.descricao, sizeof(l.descricao), stdin);
    l.descricao[strcspn(l.descricao, "\n")] = '\0';

    fprintf(arq, "%d;%s;%.2f;%s\n", l.contaNumero, l.data, l.valor, l.descricao);
    fclose(arq);

    printf("Lançamento salvo com sucesso!\n");
}

void listarLancamentos() {
    FILE *arq = fopen("lancamentos.txt", "r");
    if (!arq) {
        printf("Nenhum lançamento encontrado.\n");
        return;
    }

    Lancamento l;
    printf("\n**** Lançamentos ****\n");
    while (fscanf(arq, "%d;%10[^;];%f;%99[^\n]\n", &l.contaNumero, l.data, &l.valor, l.descricao) == 4) {
        printf("Conta: %d | Data: %s | Valor: R$%.2f | Desc: %s\n", l.contaNumero, l.data, l.valor, l.descricao);
    }
    fclose(arq);
}

void excluirLancamento() {
    char data[11];
    printf("\nDigite a data do lançamento a excluir (AAAA-MM-DD): ");
    fgets(data, sizeof(data), stdin);
    data[strcspn(data, "\n")] = '\0';

    FILE *arq = fopen("lancamentos.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!arq || !temp) {
        printf("Erro ao abrir arquivos.\n");
        return;
    }

    Lancamento l;
    int removido = 0;

    while (fscanf(arq, "%d;%10[^;];%f;%99[^\n]\n", &l.contaNumero, l.data, &l.valor, l.descricao) == 4) {
        if (strcmp(l.data, data) != 0) {
            fprintf(temp, "%d;%s;%.2f;%s\n", l.contaNumero, l.data, l.valor, l.descricao);
        } else {
            removido = 1;
        }
    }

    fclose(arq);
    fclose(temp);
    remove("lancamentos.txt");
    rename("temp.txt", "lancamentos.txt");

    if (removido)
        printf("Lançamento removido com sucesso.\n");
    else
        printf("Nenhum lançamento encontrado com essa data.\n");
}
