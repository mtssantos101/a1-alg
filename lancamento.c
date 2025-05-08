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

Lancamento criaLancamento(){
    Lancamento l;

    FILE *f = fopen("lancamento.txt", "a");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo lancamento.txt para escrita.\n");
        exit(1);
    }

    printf("**** Criar Lançamento ****\n");

    l.id = gerarIDLancamento();

    printf("\nDigite o id da conta: ");
    scanf("%d", &l.id_conta);
    getchar();

    printf("Data (AAAA-MM-DD): ");
    fgets(l.data, sizeof(l.data), stdin);
    l.data[strcspn(l.data, "\n")] = '\0';

    printf("Valor: ");
    scanf("%f", &l.valor);
    getchar();

    printf("tipo de conta (D para débito e C para crédito): ");
    scanf("%c", &l.tipo);
    getchar();

    printf("pagamento será feito agora ou no futuro? 0 para futuro e 1 para agora");
    scanf("%d", &l.efetivado);
    getchar();

    //efetua o débito ou crédito caso a opção seja para efetuar agora
    if(l.efetivado == 1)
        atualizarSaldoConta(l.id, l.valor, l.tipo);

    fprintf(f,"%d;%d;%s;%.2f;%c;%d\n",
        l.id, l.id_conta, l.data, l.valor, l.tipo, l.efetivado);
    
    
    fclose(f); 

    return l; 
}

int atualizarSaldoConta(int idConta, float valorLancamento, char tipo) {
    char* nomeArquivo = "contas.txt";

    FILE* arquivo = fopen(nomeArquivo, "r");
    FILE* temp = fopen("conta_temp.txt", "w");

    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir arquivos.\n");
        return 0; // falha
    }

    char linha[256];
    int encontrou = 0;

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        Conta contaAtual;

        linha[strcspn(linha, "\n")] = '\0';

        sscanf(linha, "%d;%99[^;];%c;%f",
               &contaAtual.id,
               contaAtual.nomeUser,
               &contaAtual.tipo,
               &contaAtual.saldo);

        if (contaAtual.id == idConta) {
            if (tipo == 'D' || tipo == 'd') { 
                contaAtual.saldo -= valorLancamento; 
            } else if (tipo == 'C' || tipo == 'c') {
                contaAtual.saldo += valorLancamento;  
            }
            encontrou = 1;
        }

        fprintf(temp, "%d;%s;%c;%.2f\n",
                contaAtual.id,
                contaAtual.nomeUser,
                contaAtual.tipo,
                contaAtual.saldo);
    }

    fclose(arquivo);
    fclose(temp);

    //remove(nomeArquivo);
    remove(nomeArquivo);
    rename("conta_temp.txt", nomeArquivo);

    return encontrou; // retorna 1 se atualizou com sucesso, 0 se não achou o ID
}

int removerLancamentosPorData(const char *dataRemover) {
    char* nomeArquivo = "lancamento.txt";
    FILE *arquivoOriginal = fopen(nomeArquivo, "r");
    FILE *arquivoTemp = fopen("lancamento_temp.txt", "w");
    
    if (arquivoOriginal == NULL || arquivoTemp == NULL) {
        printf("Erro ao abrir arquivos!\n");
        return 0; // falha
    }

    Lancamento l;
    int encontrou = 0;

    while (fscanf(arquivoOriginal, "%d;%d;%10[^;];%f;%c;%d\n", 
                  &l.id, &l.id_conta, l.data, &l.valor, &l.tipo, &l.efetivado) == 6) {
        
        if (strcmp(l.data, dataRemover) != 0) {
            // Copia lançamento para temporário, pois não é a data para remover
            fprintf(arquivoTemp, "%d;%d;%s;%.2f;%c;%d\n", 
                    l.id, l.id_conta, l.data, l.valor, l.tipo, l.efetivado);
        } else {
            encontrou = 1; // encontrou ao menos um lançamento com data a remover
        }
    }

    fclose(arquivoOriginal);
    fclose(arquivoTemp);

    // Substitui arquivo original pelo temporário
    remove(nomeArquivo);
    rename("lancamento_temp.txt", nomeArquivo);

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
void listaLancamentosOrdenado(){
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
    
    while (fscanf(arquivo, "%d;%d;%10[^;];%f;%c;%d\n", 
        &lancamentos[qtd].id, 
        &lancamentos[qtd].id_conta, 
        lancamentos[qtd].data, 
        &lancamentos[qtd].valor, 
        &lancamentos[qtd].tipo, 
        &lancamentos[qtd].efetivado) == 6) {
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

    for (int i = 0; i < qtd; i++) {
        printf("%2d | %5d | %s | %8.2f |  %c   |    %s\n", 
               lancamentos[i].id, 
               lancamentos[i].id_conta, 
               lancamentos[i].data, 
               lancamentos[i].valor, 
               lancamentos[i].tipo, 
               lancamentos[i].efetivado ? "Sim" : "Nao");
    }

    free(lancamentos);
}