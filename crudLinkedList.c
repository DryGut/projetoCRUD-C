#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
//constante para definir o tamanho das strings
#define TAM 50
FILE *arq;
//estrutura dos dados
typedef struct {
int id;
char name[TAM];
char address[TAM];
char phone[TAM];
}cadastro;

//no para manipular a lista
struct No{
cadastro cad;                //instancia a struct para ser inserida
struct No* prox;            //struct que apontará para o proximo nó
};

//lista propriamente dita
struct Lista{
struct No* inicio;         //ponteiro para o primeiro nó da lista
int tamanho;              //tamanho da lista
};

//escopo das funções
struct Lista* criar();
void inserir(struct Lista* li, int pos, cadastro cad);
bool vazia(struct Lista* li);
void imprimir(struct Lista* li);
void buscar(struct Lista* li, int pos);
void salvar(struct Lista* li);

//função que criará a lista
struct Lista* criar(){

  struct Lista* nova_lista = (struct Lista*) malloc(sizeof(struct Lista));

  if(nova_lista != NULL){
    nova_lista->inicio = NULL;
    nova_lista->tamanho = 0;
  }
  return nova_lista;
}

//função para verificar se a lista esta vazia
bool vazia(struct Lista* li){
  
  assert(li != NULL);
  if(li->inicio == NULL){
    return true;
  }else{
    return false;
  }
}

//função para inserir os dados na lista
void inserir(struct Lista* li, int pos, cadastro cad){

  assert(li != NULL);//verifica se o ponteiro não é nulo
  assert(pos >= 0 && pos <= li->tamanho);//verifica a posição de inserção
  
  //instancia um novo nó para armazenar um novo elemento
  struct No* novo_no = (struct No*) malloc(sizeof(struct No));
  novo_no->cad = cad;         //atualizando a variavel do novo nó

  if(pos == 0){              //verifica se a inserção do elemento é no inicio da lista
    novo_no->prox = li->inicio;
    li->inicio = novo_no;
  }else{                     //insere o elemento numa posição qualquer da lista
    struct No* aux = li->inicio;
    for(int i=0; i<pos-1; i++){
      aux = aux->prox;
    }
    novo_no->prox = aux->prox;
    aux->prox = novo_no;
  }
  li->tamanho++;
}

//função para obter o elemento da lista conforme o indice passado
void buscar(struct Lista* li, int pos){
  
  assert(li != NULL);
  assert(pos >= 0 && pos < li->tamanho);
  
  struct No* aux = li->inicio;
  for(int i=0; i<pos; i++){
    aux = aux->prox;
  }
  printf("\nId: %d", aux->cad.id);
  printf("\nNome: %s", aux->cad.name);
  printf("Endereço: %s", aux->cad.address);
  printf("Telefone: %s", aux->cad.phone);
}

//função que irá gerar os dados da estrutura
cadastro montar_cad(){
 
  //cria o vetor e sua alocação na memória
  cadastro *cad = (cadastro*) malloc(sizeof(cadastro));
  /*
   * bloco que irá coletar os dados
   */
  system("echo \033[93m"); //define a cor da tela de inserção de dados
  printf("\n****** INSIRA OS DADOS ******\n");

  printf("Insira o Id: ");
  setbuf(stdin, NULL);
  scanf("%d", &cad->id);
  printf("Nome: ");
  setbuf(stdin, NULL);
  fgets(cad->name, TAM, stdin);
  printf("Endereço: ");
  setbuf(stdin, NULL);
  fgets(cad->address, TAM, stdin);
  printf("Telefone: ");
  setbuf(stdin, NULL);
  fgets(cad->phone, TAM, stdin);

  return *cad;
}

//função que irá imprimir os dados armazenados na lista
void imprimir(struct Lista* li){

  assert(li != NULL);
  printf("\nDados Inseridos");
  struct No* aux = li->inicio;
  for(int i=0; i<li->tamanho; i++){
    printf("\nId: %d", aux->cad.id);
    printf("\nNome: %s", aux->cad.name);
    printf("Endereço: %s", aux->cad.address);
    printf("Telefone: %s", aux->cad.phone);
    aux = aux->prox;
  }
}
//função para salvar os dados
void salvar(struct Lista* li){
  
  assert(li != NULL);              //verifica se a lista esta vazia
  struct No* aux = li->inicio;      //coloca o ponteiro no inicio da lista
  arq = fopen("cad1.txt", "w");           //abre o arquivo
  fprintf(arq, "Dados Cadastrados");
  for(int i=0; i<li->tamanho; i++){
    fprintf(arq, "\nNome: ");
    fputs(aux->cad.name, arq);
    fprintf(arq, "Endereço: ");
    fputs(aux->cad.address, arq);
    fprintf(arq, "Telefone: ");
    fputs(aux->cad.phone, arq);
    aux = aux->prox;
  }
  fclose(arq);    //fecha o arquivo
}
//programa principal
int main(){
  struct Lista* registros = criar();
  cadastro cad;
  int opcao;
  int reg;
  do{
    system("echo \033[92m");//define a cor do menu
    printf("\n=================================");
    printf("\n|               MENU            |");
    printf("\n=================================");
    printf("\n|   Selecione a Opção Desejada  |");
    printf("\n| [1] - Para Inclusão           |");
    printf("\n| [2] - Para Imprimir Todos     |");
    printf("\n| [3] - Para Imprimir Especifico|");
    printf("\n| [4] - Para Salvar o Processo  |");
    printf("\n| [5] - Para SAIR               |");
    printf("\n=================================");
    printf("\nDigite a Opção Desejada: ");
    scanf("%d", &opcao);
    getchar();//limpa o buffer
    switch(opcao){
      case 1:
        cad = montar_cad();
        inserir(registros, 0, cad);
        system("clear");
        break;
      case 2:
        system("clear");
        imprimir(registros);
        break;
      case 3:
        printf("Digite o Registro: ");
        scanf("%d", &reg);
        buscar(registros, reg);
        break;
      case 4:
        salvar(registros);
        break;
      case 5:
        break;
      }
    }while(opcao != 5);
  return 0;
}