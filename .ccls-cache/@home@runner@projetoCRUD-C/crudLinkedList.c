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
}CADASTRO;

//no para manipular a lista
struct No{
CADASTRO cad;                //instancia a struct para ser inserida
struct No* prox;            //struct que apontará para o proximo nó
};

//lista propriamente dita
struct Lista{
struct No* inicio;         //ponteiro para o primeiro nó da lista
int tamanho;              //tamanho da lista
};

//escopo das funções
struct Lista* criar();
void inserir(struct Lista* li, int pos, CADASTRO cad);
bool vazia(struct Lista* li);
void imprimir(struct Lista* li);
void buscar(struct Lista* li, int pos);
void salvar(struct Lista* li);
int posicao(struct Lista* li);
int remover(struct Lista* li, int pos);
void update(struct Lista* li, int velho, CADASTRO novo);

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
void inserir(struct Lista* li, int pos, CADASTRO cad){

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

//função para remover um item da lista
int remover(struct Lista* li, int pos){
  
  assert(vazia(li) == false);
  assert(pos >= 0 && pos < li->tamanho);

  struct No* ant = NULL;
  struct No* aux = li->inicio;
  for(int i=0; i<pos; i++){
    ant = aux;
    aux = aux->prox;
  }
  
  if(ant == NULL){
    li->inicio = aux->prox;
  }else{
    ant->prox = aux->prox;
  }
  
  int elemento = aux->cad.id;
  li->tamanho--;
  free(aux);
  return elemento;
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
CADASTRO montar_cad(){
 
  //cria o vetor e sua alocação na memória
  CADASTRO *cad = (CADASTRO*) malloc(sizeof(CADASTRO));
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

//função para atualizar registros
void update(struct Lista* li, int velho, CADASTRO novo){
  
  int pos = 0;
  struct No* aux = li->inicio;
  while(aux->prox != NULL){
    if(aux->cad.id == velho){
      remover(li, velho);
      novo = montar_cad();
      inserir(li, velho, novo);
      printf("Cadastro Atualizado com Sucesso");
    }
    aux = aux->prox;
    pos++;
  }
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
  
  assert(li != NULL);                     //verifica se a lista esta vazia
  struct No* aux = li->inicio;           //coloca o ponteiro no inicio da lista
  arq = fopen("cad1.txt", "w");         //abre o arquivo
  
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
  CADASTRO cad;
  int opcao;
  int reg;
  do{
    system("echo \033[92m");//define a cor do menu
    printf("\n=================================");
    printf("\n|             MENU              |");
    printf("\n=================================");
    printf("\n|   Selecione a Opção Desejada  |");
    printf("\n| [1] - Para Inclusão           |");
    printf("\n| [2] - Para Imprimir Todos     |");
    printf("\n| [3] - Para Imprimir Especifico|");
    printf("\n| [4] - Deletar Cadastro        |");
    printf("\n| [5] - Atualizar Cadastro      |");
    printf("\n| [6] - Salvar Cadastros        |");
    printf("\n| [7] - Para SAIR               |");
    printf("\n=================================");
    printf("\nDigite a Opção Desejada: ");
    scanf("%d", &opcao);
    getchar();//limpa o buffer
    switch(opcao){
      case 1:
        cad = montar_cad();
        inserir(registros, cad.id, cad); //O id inicia em 0 por questões de indice da lista.
        system("clear");
        break;
      case 2:
        system("clear");
        imprimir(registros);
        break;
      case 3:
        printf("Informe o Registro: ");
        scanf("%d", &reg);
        buscar(registros, reg);
        break;
      case 4:
        printf("Informe o Registro: ");
        scanf("%d", &reg);
        remover(registros, reg);
        break;
      case 5:
        printf("Informe o Registro: ");
        scanf("%d", &reg);
        update(registros, reg, cad);
        break;
      case 6:
        salvar(registros);
        break;
      case 7:
        system("clear");
        break;
      }
    }while(opcao != 7);
  return 0;
}