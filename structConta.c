#include "conta.h"

struct conta {
    char nomeUser[100];
    int numero;
    char tipo;
    float saldo;
};

int gerarID() {
    static int id = 0;
    return ++id;
};

PConta criarConta() {
    PConta conta = (PConta) malloc(sizeof(Conta));
    if (!conta) {
        printf("Memória cheia.\n");
        exit(1);
    }

    printf("**** Criar Conta ****\n");

    printf("\nDigite seu nome completo: ");
    fgets(conta->nomeUser, sizeof(conta->nomeUser), stdin);
    conta->nomeUser[strcspn(conta->nomeUser, "\n")] = '\0';

    printf("\nEscolha seu tipo de conta: ");
    printf("\n A - Conta corrente (Digite A)\n B - Conta salário (Digite B)\n");
    scanf(" %c", &conta->tipo); 
    getchar();

    conta->saldo = 0.0;
    conta->numero = gerarID();

    printf("\nConta criada com sucesso!\n");
    printf("Número: %d\nTitular: %s\nSaldo: R$%.2f\nTipo: %c\n",
           conta->numero, conta->nomeUser, conta->saldo, conta->tipo);

    return conta;
}

void verConta(PConta conta) {
    if (conta == NULL) {
        printf("\nNenhuma conta foi criada ainda.\n");
        return;
    }
    
    printf("\n**** Dados da Conta ****\n");
    printf("Titular: %s\n", conta->nomeUser);
    printf("Número: %d\n", conta->numero);
    printf("Saldo: R$%.2f\n", conta->saldo);
    printf("Tipo: %c\n", conta->tipo);
}
