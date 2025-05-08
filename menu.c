#include "conta.h"
#include "lancamento.h"

void menu(){
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
        printf("3 - criar lancamento\n");
        printf("4 - remover lancamento por data\n");
        printf("5 - listar os lançamentos em ordem\n");
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
            case 3:
                limparTela();
                criaLancamento();
                break;
            case 4:
                limparTela();
                char* data;
                printf("digite a data do lancamento para ser removida");
                scanf("%s", data);
                removerLancamentosPorData(data);
                break;
            case 5:
                limparTela();
                printf("lançamentos ordenados: \n");
                listaLancamentosOrdenado();
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
}