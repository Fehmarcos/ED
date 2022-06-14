#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
typedef struct noarvore* ptrnoarvore;

typedef struct noarvore{
	int chave;
	ptrnoarvore direita;
	ptrnoarvore esquerda;
}noarvore;

void inicializa(ptrnoarvore *r){
	(*r) = NULL;
}
int vazia (ptrnoarvore *r){
	if ((*r)==NULL){
		return 1;
	}else{
		return 0;
	}

}

int push(ptrnoarvore *no, int nval){
	//inserir
	if ((*no)==NULL){
		(*no) = malloc(sizeof(noarvore));
		(*no)->chave = nval;
		(*no)->direita = NULL;
		(*no)->esquerda = NULL;
		return 1;
	}
	//ja existe o valor na arvore
	if ((*no)->chave == nval) return  0;
	//percorer a arvore para  achar aonde o valor deve ser inserido
	if (nval > (*no)->chave){
		return push(&(*no)->direita,nval);
	}
	if (nval < (*no)->chave){
		return push(&(*no)->esquerda,nval);
	}

}

//Prints
void preordem(ptrnoarvore *no){
	if((*no)==NULL)return;
	printf("%d ",(*no)->chave);
	preordem(&(*no)->esquerda);
	preordem(&(*no)->direita);
}
void posordem(ptrnoarvore *no){
	if((*no)==NULL)return;
	preordem(&(*no)->esquerda);
	preordem(&(*no)->direita);
	printf("%d ",(*no)->chave);
}
void emordem(ptrnoarvore *no){
	if((*no)==NULL)return;
	preordem(&(*no)->esquerda);
	printf("%d ",(*no)->chave);
	preordem(&(*no)->direita);
}
void print_arv(ptrnoarvore *no,int cas){//1 preordem | 2 posordem | 3 emordem
	printf("{ ");
	switch (cas)
	{
	case 1:
		preordem(&(*no));
		break;
	case 2:
		posordem(&(*no));
		break;
	case 3:
		emordem(&(*no));
		break;
	default:
		break;
	}
	printf("}\n");
}

int tamanho(ptrnoarvore *no){
	if((*no)==NULL)return 1;
	return(tamanho(&(*no)->esquerda) + tamanho(&(*no)->direita));\
}
int maximo(ptrnoarvore *no){
	if((*no)==NULL)return(*no)->chave ;
	return maximo(&(*no)->direita);
}
int minimo(ptrnoarvore *no){
	if((*no)==NULL)return(*no)->chave ;
	return maximo(&(*no)->esquerda);
}

int pesquisa(ptrnoarvore *no, int val){//retorna 1 se existe e 0 se nao existir
	if ((*no)== NULL){
		return 0;
	}if (val == (*no)->chave){
		return 1;
	}if(val > (*no)->chave){
		return pesquisa(&(*no)->direita, val);
	}if(val < (*no)->chave){
		return pesquisa(&(*no)->esquerda, val);
	}

}

ptrnoarvore pegarmaiorvalor(ptrnoarvore *no){
	ptrnoarvore ret;

	while ((*no)->direita != NULL){
		(*no) = (*no)->direita;
	}
	ret = (*no);
	(*no) = (*no)->esquerda;
	return ret;
}
void pop(ptrnoarvore *no, int nval){
	if ((*no)->esquerda == NULL && (*no)->direita != NULL){
		(*no) = (*no)->direita;
	}
	else if ((*no)->esquerda == NULL && (*no)->direita == NULL){
		(*no) = NULL;
	}
	else if (((*no)->esquerda != NULL && (*no)->direita == NULL)){
		(*no) = (*no)->esquerda;
	}
	else{

	}


}

void main(){
	ptrnoarvore raiz;

	inicializa(&raiz);

	push(&raiz,10);
	push(&raiz,5);
	push(&raiz,15);
	push(&raiz,2);
	push(&raiz,18);
	push(&raiz,8);
	push(&raiz,12);


}