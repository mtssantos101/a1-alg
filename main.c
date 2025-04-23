typedef struct Conta{
    int numero;
    char tipo; 
    float saldo;
} Conta;

int main(){

    Conta *conta;
    conta = malloc(sizeof(Conta));

    conta->numero = 1;
    conta->tipo = 'c';
    conta->saldo = 1000.50;
    return 0;
}