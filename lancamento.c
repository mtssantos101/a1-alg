#include "lancamento.h"
#include "conta.h"

void atualizarIDLancamento(int novoID) {
    FILE *fptr = fopen("config_id.txt", "w");

    if (fptr == NULL) {
        printf("Erro ao abrir o arquivo de ID.\n");
        exit(1);
    }

    fprintf(fptr, "id=%d", novoID);
    fclose(fptr);
}

int gerarIDLancamento() {
    FILE *fptr = fopen("config_id.txt", "r");
    int id = 1; 

    if (fptr == NULL) {
        atualizarIDLancamento(id+1);
        return id;
    }

    fscanf(fptr, "id=%d", &id);
    fclose(fptr);
    atualizarIDLancamento(id + 1);

    return id;
}

Lancamento criaLancamento(PConta conta) {
    Lancamento l;

    FILE *f = fopen("lancamento.txt", "a");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo lancamento.txt para escrita.\n");
        exit(1);
    }

    printf("**** Criar Lancamento ****\n");

    l.id = gerarIDLancamento();

    printf("Data (AAAA-MM-DD): ");
    fgets(l.data, sizeof(l.data), stdin);
    l.data[strcspn(l.data, "\n")] = '\0';

    printf("Valor: ");
    scanf("%f", &l.valor);
    getchar();
    
    printf("Digite '1' para Deposito ou '2' para Pagar: ");
    scanf("%i", &l.acao);
    getchar();
    if(l.acao == 1){
        l.tipo = 'D'; // Deposito
    }else{
        printf("tipo de conta (D para debito e C para credito): ");
        scanf("%c", &l.tipo);
        getchar(); //Pagar
    }

    printf("A acao sera feito agora ou no futuro? 0 para futuro e 1 para agora: ");
    scanf("%d", &l.efetivado);
    getchar();

    //efetua o débito ou crédito caso a opção seja para efetuar agora
    if(l.efetivado == 1)
        atualizarSaldoConta(l.id_conta, l.valor, l.tipo);


    fprintf(f,"%d;%d;%s;%.2f;%d;%c;%d\n",
        l.id, conta->id, l.data, l.valor, l.acao, l.tipo, l.efetivado);
    
    
    fclose(f); 

    return l; 
}

int atualizarSaldoConta(void *conta, float valorLancamento, int acao) {
    Conta *contaReal = (Conta *)conta; 
    char* nomeArquivo = "contas.txt";
    char* nomeArquivoTemp = "conta_temp.txt";

    FILE* arquivo = fopen(nomeArquivo, "r");
    FILE* temp = fopen(nomeArquivoTemp, "w");

    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir arquivos.\n");
        return 0; // falha
    }

    char linha[256];
    int encontrou = 0;

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        int id;
        char nome[100], tipoConta;
        float saldo;

        if (sscanf(linha, "id: %d", &id) != 1) continue;

        if (fgets(linha, sizeof(linha), arquivo) == NULL) break;
        sscanf(linha, "Titular: %99[^\n]", nome);

        if (fgets(linha, sizeof(linha), arquivo) == NULL) break;
        sscanf(linha, "Saldo: R$%f", &saldo);

        if (fgets(linha, sizeof(linha), arquivo) == NULL) break;
        sscanf(linha, "Tipo: %c", &tipoConta);

        fgets(linha, sizeof(linha), arquivo);

        if (id == idConta) {
            encontrou = 1;
            if (tipo == 'D' || tipo == 'd') { 
                saldo -= valorLancamento; 
            } else if (tipo == 'C' || tipo == 'c') {
                saldo += valorLancamento;  
            } 
            printf("Saldo atualizado com sucesso para conta ID %d.\n", idConta);
        }

        fprintf(temp, "id: %d\n", id);
        fprintf(temp, "Titular: %s\n", nome);
        fprintf(temp, "Saldo: R$%.2f\n", saldo);
        fprintf(temp, "Tipo: %c\n", tipoConta);
        fprintf(temp, "-----------------------------\n");

    }

    fclose(arquivo);
    fclose(temp);

    if (!encontrou) {
        printf("Conta com id %d não encontrada.\n", idConta);
        remove(nomeArquivoTemp);
        return 0; 
    }

    if (remove(nomeArquivo) != 0) {
        printf("Erro ao remover arquivo original.\n");
        return 0;
    }
    if (rename(nomeArquivoTemp, nomeArquivo) != 0) {
        printf("Erro ao renomear arquivo temporário.\n");
        return 0;
    }

    return 1;   
}

int removerLancamentosPorData(char *dataRemover) {
    FILE *arquivoOriginal = fopen("lancamento.txt", "r");
    FILE *arquivoTemp = fopen("lancamento_temp.txt", "w");

    if (!arquivoOriginal || !arquivoTemp) {
        printf("Erro ao abrir arquivos!\n");
        if (arquivoOriginal) fclose(arquivoOriginal);
        if (arquivoTemp) fclose(arquivoTemp);
        return 0;
    }

    Lancamento l;
    char linha[256];
    int encontrou = 0;

    while (fgets(linha, sizeof(linha), arquivoOriginal)) {
        linha[strcspn(linha, "\n")] = '\0';

        int camposLidos = sscanf(linha, "%d;%d;%10[^;];%f;%c;%d",
                                 &l.id, &l.id_conta, l.data, &l.valor, &l.tipo, &l.efetivado);

        if (camposLidos == 6) {
            l.data[10] = '\0'; 
            if (strcmp(l.data, dataRemover) != 0) {
                fprintf(arquivoTemp, "%d;%d;%s;%.2f;%c;%d\n",
                        l.id, l.id_conta, l.data, l.valor, l.tipo, l.efetivado);
            } else {
                encontrou = 1; 
            }

        } else {
            printf("Linha mal formatada ignorada: %s\n", linha);
        }
    }

    fclose(arquivoOriginal);
    fclose(arquivoTemp);

    if (encontrou) {
        remove("lancamento.txt");
        rename("lancamento_temp.txt", "lancamento.txt");
        printf("Lançamento(s) na data %s removido(s) com sucesso.\n", dataRemover);
    } else {
        remove("lancamento_temp.txt");
        printf("Nenhum lançamento encontrado para a data %s.\n", dataRemover);
    }

    return encontrou;
}
void trocar(Lancamento *a, Lancamento *b) {
    Lancamento temp = *a;
    *a = *b;
    *b = temp;
}

// QuickSort
void quickSort(Lancamento vetor[], int esquerda, int direita) {
    int i = esquerda, j = direita;
    char pivot[11];
    strcpy(pivot, vetor[(esquerda + direita) / 2].data);

    while (i <= j) {
        while (strcmp(vetor[i].data, pivot) < 0) i++;
        while (strcmp(vetor[j].data, pivot) > 0) j--;

        if (i <= j) {
            trocar(&vetor[i], &vetor[j]);
            i++;
            j--;
        }
    }

    if (esquerda < j)
        quickSort(vetor, esquerda, j);
    if (i < direita)
        quickSort(vetor, i, direita);
}
void listaLancamentosOrdenado(int contaId) {
    FILE *arquivo = fopen("lancamento.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }

    int capacidade = 100;
    int qtd = 0;
    Lancamento *lancamentos = malloc(capacidade * sizeof(Lancamento));
    if (!lancamentos) {
        printf("Falha ao alocar memoria!\n");
        exit(1);
    }
    
    while (fscanf(arquivo, "%d;%d;%10[^;];%f;%d;%c;%d\n", 
        &lancamentos[qtd].id, 
        &lancamentos[qtd].id_conta, 
        lancamentos[qtd].data, 
        &lancamentos[qtd].valor, 
        &lancamentos[qtd].acao,
        &lancamentos[qtd].tipo, 
        &lancamentos[qtd].efetivado) == 7) {
        qtd++;
        if (qtd >= capacidade) {
            capacidade *= 2;
            lancamentos = realloc(lancamentos, capacidade * sizeof(Lancamento));
            if (!lancamentos) {
                printf("Falha ao realocar memoria!\n");
                exit(1);
            }
        }
    }
    
    fclose(arquivo);

    // Ordenar os lançamentos por data
    quickSort(lancamentos, 0, qtd - 1);
    if(lancamentos == NULL){
        printf("Nenhum lancamento encontrado.\n");
        return;
    }
    for (int i = 0; i < qtd; i++) {
         if (lancamentos[i].id_conta == contaId) {
            printf("%2d | %5d | %s | %8.2f | %d |  %c   |    %s\n", 
                   lancamentos[i].id, 
                   lancamentos[i].id_conta, 
                   lancamentos[i].data, 
                   lancamentos[i].valor, 
                   lancamentos[i].acao, 
                   lancamentos[i].tipo, 
                   lancamentos[i].efetivado ? "Sim" : "Nao");
         }
    }

    free(lancamentos);
}