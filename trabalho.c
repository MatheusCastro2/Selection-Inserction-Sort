#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[100];
    int numero;
    float saldo;
} conta;

typedef struct{
    char nome;
    int numero;
    float saldo;
} temp;
//Neste trecho, você está incluindo as bibliotecas necessárias e definindo duas estruturas de dados: "conta" e "temp"
//"conta" representa uma conta bancária com nome, número e saldo. "temp" parece ser uma estrutura temporária, mas não é usada no código.


void cadastro(conta Contas[], int qntContas){
    
    int numeroConta;
    int voltar = 0;
    FILE *arquivo;

    arquivo = fopen("banco.txt", "a");
//Aqui abrimos o arquivo no modo apendice
    if (arquivo == NULL){
        printf("Erro ao abrir o arquivo\n");
        system("pause");
        exit(1);
//verifica se a funcao fopen foi bem-sucedida na abertura do arquivo
//. Se o arquivo não puder ser aberto por qualquer motivo (por exemplo, se ele não existir ou se não houver permissão de escrita)
// o ponteiro arquivo será nulo (NULL)
// Nesse caso, o programa exibe uma mensagem de erro, pausa a execução com system("pause")
// e sai do programa com exit(1), encerrando o programa abruptamente.
    }

    while (1) {
        printf("Digite o numero da conta: ");
        scanf("%d", &numeroConta);
        voltar = 0;
//Inicializa a variável voltar com o valor 0. 
//Essa variável é usada posteriormente para controlar se o loop deve ser interrompido.

        if(numeroConta > 99999 || numeroConta < 0){
            printf("Numero invalido, informe o numero novamente");
            voltar = 1;
            break;
// Verifica se o número da conta digitado é válido. 
//Se for maior que 99999 ou menor que 0, é considerado inválido. 
//Nesse caso, o programa exibe uma mensagem de erro e define voltar como 1 para indicar que o loop deve continuar pedindo um número de conta válido. 
//Em seguida, o loop é interrompido com break.
        }

        if (voltar == 0){//o programa permite ao usuário continuar o processo de cadastro.
            Contas[qntContas].numero = numeroConta;
            printf("Digite o nome: ");
            getchar();// Limpa o buffer de entrada para evitar problemas ao ler a próxima entrada.
            fgets(Contas[qntContas].nome, 100, stdin);// Lê o nome da conta digitado pelo usuário e o armazena na estrutura de dados Contas
            printf("Digite o valor do saldo: ");
            scanf("%f", &Contas[qntContas].saldo);

            fwrite(&Contas[qntContas], sizeof(conta), 1, arquivo);//Escreve a estrutura de dados da conta no arquivo de dados "banco.txt" usando a função fwrite. 
            //Isso armazena os dados da conta no arquivo.
            printf("\n");

            fclose(arquivo);
            break;
        }
    }
}
//A função cadastro permite que o usuário insira informações de uma nova conta bancária e armazena essas informações em um arquivo chamado "banco.txt".
//Ela verifica se o número da conta é válido e, em seguida, grava os dados da conta no arquivo.

void listagem(){

    FILE *arquivo;
    conta cnt;

    arquivo = fopen("banco.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        system("pause");
        exit(1);
    }

    while (fread(&cnt, sizeof(conta),1,arquivo) == 1) {
        printf("Nome: %s", cnt.nome);
        printf("Numero: %d", cnt.numero);
        printf("Saldo: %f", cnt.saldo);
    }
    fclose(arquivo);
    system("pause");
    system("cls");

}
//A função listagem lê e exibe todas as contas armazenadas no arquivo "banco.txt"
//Ela usa a função fread para ler os dados das contas do arquivo.

void selecao(int qntContas, conta Conta[]){
    FILE *arquivo;
    int i =0, maior, comp = 0, movi = 0;
    conta temp;// Declara uma variável temporária do tipo conta para ser usada na troca de contas durante a ordenação.

    arquivo = fopen("banco.txt", "r");
     if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        system("pause");
        exit(1);
    }

    while (fread(&Conta[i], sizeof(conta), 1, arquivo) == 1){
        i++;
        // Lê as contas do arquivo e armazena-as no array Conta. Isso permite que o programa trabalhe com os dados das contas no arquivo.
    }

    fclose(arquivo);


    time_t begin = time(NULL);//Registra o tempo de início da ordenação.
    for (int j = 0; j < i - 1; j++) {
        maior = j;
        for(int k = j + 1; k < i; k++){
            if(Conta[k].saldo > Conta[maior].saldo)
                maior = k;
                comp++;
            if(j != maior){
                temp = Conta[j];
                Conta[j] = Conta[maior];
                Conta[maior] = temp;
                movi++;
            }
        }
        // implementa o algoritmo de seleção para ordenar as contas com base no saldo. 
        //Ele encontra a conta com o maior saldo e a move para a posição correta no array Conta. 
        //Enquanto faz isso, conta o número de comparações e movimentos realizados.
    }

    time_t end = time(NULL);// Registra o tempo de término da ordenação

    printf("LISTA ORDENADA\n");

    for(int j=0; j<i; j++){
        printf("Nome: %s", Conta[j].nome);
        printf("N Conta %d\n", Conta[j].numero);
        printf("Saldo: %.2f\n", Conta[j].saldo);
        // exibe a lista ordenada das contas, incluindo nome, número da conta e saldo.
    }

    printf("Estatistica");
     printf("Comparacoes: %d\n", comp);
    printf("Movimentos: %d\n", movi);
    printf("Tempo percorrido: %d\n", (end - begin));
    system("pause");
    system("cls");
    //exibe estatísticas da ordenação, incluindo o número de comparações, o número de movimentos e o tempo gasto na ordenação.
}

//A função selecao ordena as contas por saldo usando o algoritmo de seleção.
//Ela lê os dados das contas do arquivo, realiza a ordenação e exibe a lista ordenada
//juntamente com estatísticas sobre o processo de ordenação.

void insercao(int qntContas, conta Conta[]){

    int i = 0, j = 0, maior, comp = 0, movi = 0;
    conta Temp;

    FILE *arquivo;

    arquivo = fopen("banco.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        system("pause");
        exit(1);
    }

    while (fread(&Conta[i], sizeof(conta), 1, arquivo) == 1) {
        i++;
        // Lê as contas do arquivo e armazena-as no array Conta. Isso permite que o programa trabalhe com os dados das contas no arquivo.
    }

    fclose(arquivo);

    time_t begin = time(NULL);//Esta linha registra o tempo de início da ordenação.
    for (int k = 1; k <= 15 - 1; k++){
      Temp = Conta[k];
      j = k - 1;
      comp++;

      while (j >= 0 && Temp.saldo > Conta[j].saldo) {

         Conta[j + 1] = Conta[j];
         j--;
         movi++;
      }

      Conta[j+1] = Temp;
      movi++;
      //O código implementa o algoritmo de ordenação por inserção. 
      //Ele começa com o segundo elemento (índice 1) do array Conta e insere esse elemento na posição correta em relação aos elementos anteriores. 
      //Durante esse processo, o número de comparações (comp) e movimentos (movi) é contado.
   }

   time_t end = time(NULL);// Esta linha registra o tempo de término da ordenação.

    printf("LISTA ORDENADA\n");
    for(int index = 0; index < i; index++){
        printf("Nome: %s", Conta[index].nome);
        printf("Conta: %d\n", Conta[index].numero);
        printf("Saldo: %.2f\n", Conta[index].saldo);
        //O código exibe a lista ordenada das contas, incluindo o nome, o número da conta e o saldo.
    }
    printf("Estatistica\n");
    printf("Comparacoes: %d\n", comp);
    printf("Movimentos: %d\n", movi);
    printf("Tempo percorrido: %d\n", (end - begin));
    system("pause");
    system("cls");
    //O código exibe estatísticas da ordenação, incluindo o número de comparações, o número de movimentos e o tempo gasto na ordenação.
}
//A função insercao ordena as contas por saldo usando o algoritmo de inserção.
//Ela lê os dados das contas do arquivo, realiza a ordenação e exibe a lista ordenada
//juntamente com estatísticas sobre o processo de ordenação.

int main(){
    int selecioneOperacao, ordenacao;
    int qntContas = 0;
    conta Conta[15];

    for(int i = 0; i < 15; i++){
        Conta[i].nome[100] = "";
        Conta[i].numero = 0;
        Conta[i].saldo = 0.0;
    }

    do {
        
        
        printf("1-- Cadastrar conta\n");
        printf("2-- Ordenar conta\n");
        printf("3-- Listar contas\n");
        printf("4-- Sair\n");
        printf("Selecione a operacao:");
        scanf("%d", &selecioneOperacao);
        printf("\n");

        switch (selecioneOperacao) {
            case 1:
                if (qntContas < 15) {
                    cadastro(Conta, qntContas);
                    printf("Conta cadastrada\n");
                    system("pause");
                    system("cls");
                    ++qntContas;
                } else {
                    printf("limite alcancado\n");
                }
                break;
            case 2:

                do{
                    printf("|  Selecione sua ordenacao  |\n");
                    printf("\n");
                    printf("1-- Ordenacao por selectionSort \n");
                    printf("2-- Ordenacao por inserction Sort\n");
                    printf("3-- voltar\n");
                    printf("Selecione a operacao:");
                    scanf("%d", &ordenacao);
                    printf("\n");

                    switch(ordenacao){
                    case 1:
                        selecao(qntContas, Conta);
                        break;
                    case 2:
                        insercao(qntContas, Conta);
                        break;
                    case 3:
                        printf("-- Voltando...\n");
                        sleep(2);
                        system("cls");
                        break;
                    default:
                        printf("Operacao invalida\n");
                        system("cls");
                        break;
                    }

                }while(ordenacao != 3);
                break;
            case 3:
                listagem();
                break;
            case 4:
                printf("-- Saindo...\n");
                sleep(2);
                break;
            default:
                printf("Operacao invalida\n");
                system("cls");
            break;
        }
    } while (selecioneOperacao != 4);

    return 0;
}
//A função main é a função principal do programa
//Ela contém um loop que permite que o usuário selecione várias operações, como cadastrar contas, ordenar contas e listar contas
//O programa continua em execução até que o usuário escolha sair (opção 4)
//Cada operação chama as funções relevantes para executar as tarefas específicas.
