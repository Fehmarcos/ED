#include <stdio.h>
#define maxtam 30

typedef struct {
	int dado[maxtam];
	int ini;
	int fim;
	int tamanho;
} filaEstatica;

void inicializar(filaEstatica* fe){
	fe->tamanho = 0;
	fe->ini = -1;
	fe->fim = -1;
}

int isvazia(filaEstatica* fe){
	if(fe->tamanho == 0){
		printf("A Fila esta vazia!\n");
		return 1;
	}
	return 0;
}

int ischeia(filaEstatica* fe){
	if(fe->tamanho == maxtam){
		printf("A Fila esta cheia!\n");
		return 1;
	}
	return 0;
}

int movefila(int proximo){
	proximo = proximo + 1;
	if(proximo > maxtam) proximo = 0;
	return proximo;
}

void pfila(filaEstatica* fe){
	if(isvazia(fe))return;
	printf("{");
	int i = fe->ini - 1;

	do{
		i = movefila(i);
		printf("%d ",fe->dado[i]);
	} while (i != fe->fim);
	printf("}");
}

int add(filaEstatica* fe, int dado){
	if (ischeia(fe))return -1;

	int novo = fe->fim ;//pega a ultima pos da fila
	novo = movefila(novo);

	if(fe->tamanho == 0)fe->ini = 0;

	fe->fim = novo;
	fe->dado[novo] = dado;
	fe->tamanho++;
	return 1;
}

int remov(filaEstatica* fe){
	int dado = fe->dado[fe->ini];
	if(isvazia(fe))return -1;

	fe->ini =	movefila(fe->ini);

	fe->tamanho--;
	if (fe->tamanho == 0)inicializar(fe);
	return dado;
}

void main(void){
	int op, dado;
	filaEstatica fila;

	inicializar(&fila);

	while (1){
		printf("\n\n");
		printf("0 finaliza o progama\n");
		printf("1 Adicionar\n");
		printf("2 remover\n");
		printf("3 imprimir\n");
		scanf("%d", &op);
		switch (op){
		case 0:
			return;
			break;
		case 1:
			printf("Qual valor deseja adicionar?\n");
			scanf("%d", &dado);
			if(add(&fila,dado) != -1)	printf("O %d foi adicionado!\n",dado);
			break;
		case 2:
			dado = remov(&fila);
			if(dado != -1)printf("O %d foi removido!\n",dado);
			break;
		case 3:
			pfila(&fila);
			break;
		default:
			printf("Numero invalido\n");
			break;
		}
	}
}