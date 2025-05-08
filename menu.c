#include "conta.h"
#include "lancamento.h"

void menuSub(PConta contaAtiva){
    int opcao;
    do {
        printf("\n**** Menu ****\n");
        printf("1 - Ver dados da conta\n");
        printf("2 - criar lancamento\n");
        printf("3 - remover lancamento por data\n");
        printf("4 - listar os lancamentos em ordem\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                limparTela();
                if (!contaAtiva) {
                    printf("\nNenhuma conta selecionada.\n");
                    break;
                }   
                verConta(contaAtiva);
                break;
            case 2:
                limparTela();
                criaLancamento();
                break;
            case 3:
                limparTela();
                char* data;
                printf("digite a data do lancamento para ser removida");
                scanf("%s", data);
                removerLancamentosPorData(data);
                break;
            case 4:
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

}

void menuPrincipal(){
    int opcao;
    int quantidade = 0;
    PConta contaAtiva;
    PPConta contas = filePush(&quantidade);

    if (contas) {
        printf("Numero de contas carregadas: %d\n", quantidade);
    } else {
        printf("Nenhuma conta foi carregada.\n");
    }
    verContas(contas, quantidade);
    printf("Seja bem-vindo ao Banco!\n");

    do {
        printf("\n**** Voce ja possui uma conta? ****\n");
        printf("1 - Sim, desejo acessar a minha conta\n");
        printf("2 - Nao, desejo criar uma conta\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                limparTela();
                contaAtiva = acessarConta(contas, &quantidade);
                if(contaAtiva != NULL) {
                    printf("Conta ativa: %s\n", contaAtiva->nomeUser);
                    menuSub(contaAtiva);
                } else {
                    printf("Conta não encontrada.\n");
                }
                break;
            case 2:
                limparTela();
                if(!contas){
                    contas = alocarMemoriaEstrutura();
                    break;
                }
                contas[quantidade] = criarConta();
                contaAtiva = contas[quantidade];
                quantidade++;
                printf("Numero de contas: %d\n", quantidade);
                if(contas == NULL){
                    printf("Nenhuma conta foi criada ainda.\n");
                    break;
                }
                menuSub(contaAtiva);
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