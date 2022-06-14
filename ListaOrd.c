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
} ListaOrd;

void inicia(ListaOrd *lo){
	lo->inicio = NULL;
	lo->tamanho = 0;
}
int vazia(ListaOrd *lo){
	return(lo->inicio == NULL);
}
int tamanho(ListaOrd *lo){
	return(lo->tamanho);
}
void loprint(ListaOrd *lo){
	PtrDado aux;

	printf("{");
	for (aux = lo->inicio; aux != NULL; aux = aux->proximo)
	{
		printf("%d ",aux->valor);
	}
	printf("}\n");
}

void push(ListaOrd *lo, TIPO_LISTA val){
	PtrDado new;

	new = (PtrDado)malloc(sizeof(Dado));
	new->valor = val;

	if (vazia(lo)){
		new->proximo = NULL;
		lo->inicio = new;
	}else if(new->valor < lo->inicio->valor){
		new->proximo = lo->inicio;
		lo->inicio = new;
	}else{
		PtrDado aux =  lo->inicio;
		while(aux->proximo != NULL && val > aux->proximo->valor){
			aux = aux->proximo;
		}
		new->proximo = aux->proximo;
		aux->proximo = new;
	}
	lo->tamanho++;
}
void pop(ListaOrd *lo, TIPO_LISTA val){
	PtrDado old;
	if(vazia(lo))return;
	if(val < lo->inicio->valor)return;
	if(val == lo->inicio->valor){
		old = lo->inicio;
		lo->inicio = lo->inicio->proximo;
		free(old);
	}else{
		PtrDado aux = lo->inicio;
		while(val != aux->proximo->valor){
			aux = aux->proximo;
			if(aux->proximo == NULL)return;
		}
		old = aux->proximo;
		aux->proximo = old->proximo;
		free(old);
	}
	lo->tamanho--;
}
TIPO_LISTA search(ListaOrd *lo,TIPO_LISTA val){
	if(vazia(lo))return 0;
	if(val < lo->inicio->valor)return 0;
	if(val == lo->inicio->valor)return 1;
	PtrDado aux = lo->inicio;
	int count = 2;
	while(val != aux->proximo->valor){
		aux = aux->proximo;
		if(aux->proximo == NULL)return 0;
		count++;
	}
	return count;
}

int primeiro(ListaOrd *lo){
	return lo->inicio->valor;
}
int ultimo(ListaOrd *lo){
	PtrDado aux = lo->inicio;

	while(aux->proximo != NULL){
		aux = aux->proximo;
	}
	return aux->valor;
}

void main() {
	ListaOrd lo;
	inicia(&lo);

	push(&lo,10);
	loprint(&lo);

	push(&lo,4);
	loprint(&lo);

	push(&lo,6);
	loprint(&lo);

	push(&lo,8);
	loprint(&lo);

	push(&lo,1);
	loprint(&lo);

	push(&lo,20);
	loprint(&lo);

	int val = 20;
	printf("Pos do %d: %d\n",val,search(&lo,val));

	printf("Primeiro: %d\n Ultimo: %d\n",primeiro(&lo),ultimo(&lo));
}