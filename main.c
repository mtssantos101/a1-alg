#include "conta.h"

void limparTela(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main(int argc, char *argv[]) {
    int opcao;
    int quantidade = 0;
    PPConta contas = filePush(&quantidade);

    if (contas) {
        printf("Numero de contas carregadas: %d\n", quantidade);
    } else {
        printf("Nenhuma conta foi carregada.\n");
    }

    printf("Seja bem-vindo ao Banco!\n");

    do {
        printf("\n**** Menu ****\n");
        printf("1 - Criar conta\n");
        printf("2 - Ver dados da conta\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                limparTela();
                if(!contas){
                    contas = alocarMemoriaEstrutura();
                    break;
                }
                contas[quantidade] = criarConta();
                quantidade++;
                printf("Numero de contas: %d\n", quantidade);
                break;
            case 2:
                limparTela();
                if (!contas) {
                    printf("\nNenhuma conta foi criada ainda.\n");
                    break;
                }   
                verConta(contas, &quantidade);
                break;
            case 0:
                limparTela();
                printf("\nSaindo...\n");
                break;
            default:
                limparTela();
                printf("\nOpçao invalida.\n");
        }

    } while (opcao != 0);

    if (contas != NULL) {
        for(int i = 0; i <= quantidade-1; i++){
            free(contas[i]);
        }
        free(contas);
    }

    return 0;
}
