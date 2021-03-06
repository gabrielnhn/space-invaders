#ifndef LIB_LISTA

#define LIB_LISTA 1

struct s_elemento
{
	int i, j;
	char tipo;
  int contador;
};
typedef struct s_elemento elemento;

struct t_nodo
{
    elemento e;
    struct t_nodo *prox;
    struct t_nodo *prev;
};

typedef struct t_nodo t_nodo;

struct t_lista
{
    t_nodo *ini;
    t_nodo *atual;
    t_nodo *fim;
    int tamanho;
};
typedef struct t_lista t_lista;


int inicializa_lista(t_lista *l);
/*  Cria uma lista vazia. Ela eh duplamente encadeada e tem sentinelas no
  inicio e no final. Tambem tem um apontador para um elemento qualquer. */

int lista_vazia(t_lista *l);
/*  Retorna 1 se a lista está vazia e zero caso contrário. */

int insere_inicio_lista(elemento e, t_lista *l);
/*  Insere o elemento item no início da lista.
  Retorna 1 se a operação foi bem sucedida e zero caso contrário. */

int tamanho_lista(int *tam, t_lista *l);
/*  Retorna o tamanho da lista em *tam.
  Retorna 1 se a operação foi bem sucedida e zero caso contrário. */

int insere_fim_lista(elemento e, t_lista *l);
/*  Insere o elemento item no final da lista.
  Retorna 1 se a operação foi bem sucedida e zero caso contrário. */

int insere_ordenado_lista(elemento e, t_lista *l);
/*  Insere o elemento item na lista de maneira que ela fique em ordem
  crescente, do início para o final dela.
  Retorna 1 se a operação foi bem sucedida e zero caso contrário. */

int remove_inicio_lista(elemento *e, t_lista *l);
/*  Remove o primeiro elemento da lista e o retorna em *item.
  Retorna 1 se a operação foi bem sucedida e zero caso contrário. */

int remove_fim_lista(elemento *e, t_lista *l);
/*  Remove o último elemento da lista e o retorna em *item.
  Retorna 1 se a operação foi bem sucedida e zero caso contrário. */

int pertence_lista(elemento e, t_lista *l);
/*  Retorna 1 se o elemento contendo a chave chave existe na lista,
  caso contrário retorna zero.  */

int inicializa_atual_inicio(t_lista *l);
/*  Inicializa o ponteiro atual para o primeiro elemento da lista.
  Retorna 1 se a operação foi bem sucedida e zero caso contrário. */

int inicializa_atual_fim(t_lista *l);
/*  Inicializa o ponteiro atual para o ultimo elemento da lista.
  Retorna 1 se a operação foi bem sucedida e zero caso contrário. */

void incrementa_atual(t_lista *l);
/*  Faz o ponteiro atual apontar para o próximo nodo da lista l e retorna 
  este ponteiro. Se atual estiver apontando para o último, isto é, não 
  tem próximo, retorna NULL. */

void decrementa_atual(t_lista *l);
/*  Faz o ponteiro atual apontar para o nodo anterior da lista l e retorna 
  este ponteiro. Se atual estiver apontando para o primeiro, isto é, não 
  tem anterior, retorna NULL. */

int consulta_item_atual(elemento **e, t_lista *l);
/*  Retorna em *item o valor contido na chave apontada pelo ponteiro atual. 
  Se atual não for válido a função retorna zero senão retorna 1. */

int remove_item_atual(elemento *e, t_lista *l);
/*  Remove o elemento apontado por atual da lista l e o retorna em *item.
  Faz o atual apontar para o sucessor do nodo removido.
  Retorna 1 se houve sucesso e zero caso contrário. */

int remove_item_especifico(elemento e, t_lista* l, int contador_atual);
/* remove o item e da lista l sem perder o ponteiro atual (quando se informa contador_atual) */

void copia_lista(t_lista* A, t_lista* B, int contador_atual_A);
/* copia a lista A na lista B (assumindo que B esta vazia), sem perder o ponteiro atual de A */

void destroi_lista(t_lista* l);
/* Remove todos os elementos da lista e faz com que ela aponte para NULL. */

#endif