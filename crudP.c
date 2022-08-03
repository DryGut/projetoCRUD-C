#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//constante para definir o tamanho das strings
#define TAM 50
//escopo das funções
struct cadastro* montar_cad();
void imprimir();
//cria a estrutura do formulário a ser preenchido
typedef struct cadastro{
char id[TAM];
char name[TAM];
char address[TAM];
char phone[TAM];
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
  system("echo \033[93m"); //define a cor da tela de inserção de dados
  printf("\n****** INSIRA OS DADOS ******\n");

  printf("Insira o Id: ");
  setbuf(stdin, NULL);
  fgets(cad->id, TAM, stdin);
  printf("Nome: ");
  setbuf(stdin, NULL);
  fgets(cad->name, TAM, stdin);
  printf("Endereço: ");
  setbuf(stdin, NULL);
  fgets(cad->address, TAM, stdin);
  printf("Telefone: ");
  setbuf(stdin, NULL);
  fgets(cad->phone, TAM, stdin);

  return cad;
}
//função para imprimir os dados do arquivo gerado
void imprimir(){
  arq = fopen("cad1.txt", "r");
  char buffer[50];
  if(arq == NULL){
    perror("opening file");
  }
  while(EOF != fscanf(arq, "%50[^\n]\n", buffer)){
    printf("%s\n", buffer);
  }
  fclose(arq);
}
//programa principal
int main(){
  //cria a variável da estrutura
  struct cadastro *cad;
  //variável para as opções
  int opcao;
  
  do{
    system("echo \033[92m");//define a cor do menu
    printf("\n=================================");
    printf("\n|               MENU            |");
    printf("\n=================================");
    printf("\n|   Selecione a Opção Desejada  |");
    printf("\n|   [1] - Para Novo Arquivo     |");
    printf("\n|   [2] - Para Inclusão         |");
    printf("\n|   [3] - Para Imprimir         |");
    printf("\n|   [4] - para SAIR             |");
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
        fprintf(arq, "\nID: ");
        fputs(cad->id, arq);
        fprintf(arq, "Nome: ");
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
        fprintf(arq, "\nID: ");
        fputs(cad->id, arq);
        fprintf(arq, "Nome: ");
        fputs(cad->name, arq);
        fprintf(arq, "Endereço: ");
        fputs(cad->address, arq);
        fprintf(arq, "Telefone: ");
        fputs(cad->phone, arq);
        fclose(arq);

      case 3:
        imprimir();
        break;

      case 4:
        system("clear");
        break;
    }
  }while(opcao != 4);
  return 0;
}