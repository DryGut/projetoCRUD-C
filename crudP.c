#include <stdio.h>
#include <stdlib.h>

//constante para definir o tamanho das strings
#define TAM_S 50
//escopo da função
struct cadastro* montar_cad();
//cria a estrutura do formulário a ser preenchido
typedef struct cadastro{
char name[TAM_S];
char address[TAM_S];
char phone[TAM_S];
}cad;
//variável para o arquivo que será utilizado
FILE *arq;
//função para criar um vetor que receberá os dados da struct
struct cadastro* montar_cad(){
 
  //cria o vetor e sua alocação na memória
  struct cadastro *cad = (struct cadastro*) malloc(sizeof(struct cadastro));
  /*
   * bloco que irá coletar os dados
   */
  system("echo \033[93m"); //define a cor na tela de inserção de dados
  printf("\n****** INSIRA OS DADOS ******\n");
 
  printf("Nome: ");
  fflush(stdin);
  fgets(cad->name, TAM_S, stdin);
  printf("Endereço: ");
  fflush(stdin);
  fgets(cad->address, TAM_S, stdin);
  printf("Telefone: ");
  fflush(stdin);
  fgets(cad->phone, TAM_S, stdin);

  return cad;
}
//programa principal
int main(){
  //cria a variável da estrutura
  struct cadastro *cad;
  //variável para as opções
  int opcao;
  
  do{
    system("echo \033[92m");//define a cor do menu
    printf("=================================");
    printf("\n|               MENU            |");
    printf("\n=================================");
    printf("\n|   Selecione a Opção Desejada  |");
    printf("\n|   [1] - Para Novo Arquivo     |");
    printf("\n|   [2] - Para Inclusão         |");
    printf("\n|   [3] - Para SAIR             |");
    printf("\n=================================");
    printf("\nDigite a Opção Desejada: ");
    scanf("%d", &opcao);
    getchar();//limpa o buffer
    switch(opcao){
      case 1:
        cad = montar_cad(); //chamada da função que coleta os dados
        system("clear");//limpa a tela dps da inclusão dos dados
        arq = fopen("cad1.txt", "w");//abre e escreve no arquivo com a flag W
        
        //formatação da primeira inclusão no arquivo
        fprintf(arq, "###### DADOS PESSOAIS ######");
        fprintf(arq, "\nNome: ");
        fputs(cad->name, arq);
        fprintf(arq, "Endereço: ");
        fputs(cad->address, arq);
        fprintf(arq, "Telefone: ");
        fputs(cad->phone, arq);
        fclose(arq);
        break;

      case 2:
        cad = montar_cad();//chamada da função que coleta os dados
        system("clear");
        arq = fopen("cad1.txt", "a");
        //com a flag A toda nova inclusão será ao final do arquivo
        fprintf(arq, "\nNome: ");
        fputs(cad->name, arq);
        fprintf(arq, "Endereço: ");
        fputs(cad->address, arq);
        fprintf(arq, "Telefone: ");
        fputs(cad->phone, arq);
        fclose(arq);

      case 3:
        break;
    }
  }while(opcao != 3);
  return 0;
}