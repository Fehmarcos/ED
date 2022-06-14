#include <stdio.h>
#include <stdlib.h>

typedef int TIPO_LISTA;

typedef struct Dado* PtrDado;
typedef struct Dado {//no de lista
  TIPO_LISTA valor;
  PtrDado proximo;
} Dado;
typedef struct {//lista
  PtrDado inicio;
  int tamanho;
} Lista;

void inicia(Lista *l){
	l->inicio = NULL;
	l->tamanho = 0;
}
void lprint(Lista *l){//usada para debug
	PtrDado aux;

	printf("{");
	for (aux = l->inicio; aux != NULL; aux = aux->proximo)
	{
		printf("%d ",aux->valor);
	}
	printf("}\n");
}

void push(Lista *l, TIPO_LISTA val){
	PtrDado new;

	new = (PtrDado)malloc(sizeof(Dado));
	new->valor = val;

	if (l->tamanho == 0){
		new->proximo = NULL;
		l->inicio = new;
	}else if(new->valor < l->inicio->valor){
		new->proximo = l->inicio;
		l->inicio = new;
	}else{
		PtrDado aux =  l->inicio;
		while(aux->proximo != NULL && val > aux->proximo->valor){
			aux = aux->proximo;
		}
		new->proximo = aux->proximo;
		aux->proximo = new;
	}
	l->tamanho++;
}
Lista constroi(int n,int* v){
	Lista l;
	inicia(&l);

	for (int i = 0; i < n; i++){
		push(&l,v[i]);
	}

	return l;
}
void main() {
	Lista l;
	int vec[10] = {20};

	l = constroi(20,vec);

	lprint(&l);
}