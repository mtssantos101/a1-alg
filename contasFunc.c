#include "conta.h"
#define CAPACIDADE 5

PConta alocarMemoriaConta(){
    PConta conta = (PConta) malloc(sizeof(Conta));
    if (!conta) {
        printf("Memória cheia.\n");
        exit(1);
    }
    return conta;
}

PPConta alocarMemoriaEstrutura(){
    PPConta contas = (PPConta) malloc(CAPACIDADE * sizeof(PConta));
    if (!contas) {
        printf("Erro ao alocar memória para o vetor de contas\n");
        exit(1);
    }
    return contas;
}

void realocarEstrutura(PPConta contas, int* capacidade){
    contas = (PPConta) realloc(contas, *capacidade * sizeof(PConta));
       if (!contas) {
           printf("Erro ao realocar memória para o vetor de contas\n");
           exit(1);
       }
}

PPConta filePush(int* quantidade) {
    FILE *fptr;
    char linha[200];
    int i = 0;  

    PPConta contas = alocarMemoriaEstrutura();

    fptr = fopen("contas.txt", "r");
    if (fptr == NULL) {
        printf("Erro ao abrir o arquivo\n");
        free(contas);
        *quantidade = 0;
        return NULL;
    }

    while (fgets(linha, sizeof(linha), fptr)) {
        if (i == CAPACIDADE) {
            int newCapacidade = i*2;
            realocarEstrutura(contas, &newCapacidade);
        }

        PConta conta = alocarMemoriaConta();
        
        if (sscanf(linha, " %[^\n,], %d, %c, %f", conta->nomeUser, &conta->numero, &conta->tipo, &conta->saldo) == 4) {
            contas[i++] = conta;
        } else {
            free(conta); 
        }
    }

    fclose(fptr);
    *quantidade = i;
    return contas;
}

int gerarID() {
    static int id = 0;
    return ++id;
};


PConta criarConta() {
    PConta conta = alocarMemoriaConta();

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

void verConta(PPConta contas, int * quantidade) {
    
    for(int i = 0; i <= *quantidade-1; i++){
        printf("\n**** Dados da Conta ****\n");
        printf("Titular: %s\n", contas[i]->nomeUser);
        printf("Número: %d\n", contas[i]->numero);
        printf("Saldo: R$%.2f\n", contas[i]->saldo);
        printf("Tipo: %c\n", contas[i]->tipo);
    }
}
