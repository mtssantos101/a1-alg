#include "conta.h"

int main(int argc, char *argv[]) {
    int opcao;
    PConta minhaConta = NULL;

    printf("Seja bem-vindo ao Banco!\n");

    do {
        printf("\n**** Menu ****\n");
        printf("1 - Criar conta\n");
        printf("2 - Ver dados da conta\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                minhaConta = criarConta();
                break;
            case 2:
                verConta(minhaConta);
                break;
            case 0:
                printf("\nSaindo...\n");
                break;
            default:
                printf("\nOpção inválida.\n");
        }

    } while (opcao != 0);

    if (minhaConta != NULL) {
        free(minhaConta);
    }

    return 0;
}
