#include "conta.h"
#define CAPACIDADE_INICIAL 5

void atualizarID(int novoID) {
    FILE *fptr = fopen("config_conta.txt", "w");

    if (fptr == NULL) {
        printf("Erro ao abrir o arquivo de id_conta.\n");
        exit(1);
    }

    fprintf(fptr, "id=%d", novoID);
    fclose(fptr);
}

int gerarID() {
    FILE *fptr = fptr = fopen("config_conta.txt", "r");;
    int id = 1; 

    if (fptr == NULL) {
        atualizarID(id+1);
        return id;
    }

    fscanf(fptr, "id=%d", &id);
    fclose(fptr);
    atualizarID(id + 1);

    return id;
}

PConta alocarMemoriaConta(){
    PConta conta = (PConta) malloc(sizeof(Conta));
    if (!conta) {
        printf("Memoria cheia.\n");
        exit(1);
    }
    return conta;
}

PPConta alocarMemoriaEstrutura(){
    PPConta contas = (PPConta) malloc(CAPACIDADE_INICIAL * sizeof(PConta));
    if (!contas) {
        printf("Erro ao alocar memoria para o vetor de contas\n");
        exit(1);
    }
    return contas;
}

PPConta realocarEstrutura(PPConta contas, int* capacidade){
       PPConta temp = (PPConta)realloc(contas, *capacidade * sizeof(PConta));
       if (!temp) {
           perror("Erro ao realocar memória para vetor de contas");
           exit(EXIT_FAILURE);
       }
       return temp;
}

PPConta filePush(int* quantidade) {
    FILE *fptr = fopen("contas.txt", "a+");
    char linha[200];
    int capacidade = CAPACIDADE_INICIAL;
    int i = 0;

    PPConta contas = alocarMemoriaEstrutura(); 

    if (fptr == NULL) {
        printf("Erro ao abrir o arquivo\n");
        free(contas);
        *quantidade = 0;
        return NULL;
    }

    while (fgets(linha, sizeof(linha), fptr)) {
        if (i >= capacidade) {
            capacidade *= 2;
            contas = realocarEstrutura(contas, &capacidade);
        }

        PConta conta = alocarMemoriaConta();
        
        int r = sscanf(linha, " %d, %[^,], %f, %c", &conta->id, conta->nomeUser, &conta->saldo, &conta->tipo);
        if (r == 4) {
            contas[i++] = conta;
        } else {
            printf("Erro ao ler a linha: %s", linha);
            free(conta);
        }
    }

    fclose(fptr);
    *quantidade = i;
    return contas;
}

void filePull(PConta conta) {
    FILE *fptr = fopen("contas.txt", "a"); 

    if (fptr == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fprintf(fptr, "%d, %s,%.2f,%c\n",
        conta->id, conta->nomeUser, conta->saldo, conta->tipo);
    
        
    fclose(fptr);
}


PConta criarConta() {
    PConta conta = alocarMemoriaConta();

    printf("**** Criar Conta ****\n");

    printf("\nDigite seu nome completo: ");
    fgets(conta->nomeUser, sizeof(conta->nomeUser), stdin);
    conta->nomeUser[strcspn(conta->nomeUser, "\n")] = '\0';

    printf("\nEscolha seu tipo de conta: ");
    printf("\n A - Conta corrente (Digite A)\n B - Conta salario (Digite B)\n");
    scanf(" %c", &conta->tipo); 
    getchar();

    conta->saldo = 0.0;
    conta->id = gerarID();
    filePull(conta);

    printf("\nConta criada com sucesso!\n");
    printf("Numero: %d\nTitular: %s\nSaldo: R$%.2f\nTipo: %c\n",
           conta->id, conta->nomeUser, conta->saldo, conta->tipo);

    return conta;
}

void verConta(PConta conta) {
    printf("\n**** Dados da Conta ****\n");
    printf("Titular: %s\n", conta->nomeUser);
    printf("Numero: %d\n", conta->id);
    printf("Saldo: R$%.2f\n", conta->saldo);
    printf("Tipo: %c\n", conta->tipo);

}

void verContas(PPConta contas, int quantidade) {
    printf("\n**** Lista de Contas ****\n");
    for (int i = 0; i < quantidade; i++) {
        printf("Conta %d:\n", i + 1);
        printf("Titular: %s\n", contas[i]->nomeUser);
        printf("Numero: %d\n", contas[i]->id);
        printf("Saldo: R$%.2f\n", contas[i]->saldo);
        printf("Tipo: %c\n", contas[i]->tipo);
        printf("-----------------------------\n");
    }
    printf("Total de contas: %d\n", quantidade);
    printf("-----------------------------\n");
}

void limparTela(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

PConta acessarConta(PPConta contas, int *quantidade) {
    int num;
    printf("Digite o Numero da conta que deseja acessar: ");
    scanf("%d", &num);
    getchar();

    for (int i = 0; i < *quantidade; i++) {
        if (contas[i]->id == num) {
            printf("Acesso a conta %d permitido.\n", num);
            return contas[i];
        }
    }

    return NULL;
}