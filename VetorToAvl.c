#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct NoAVL* PtrNoAVL;

typedef struct NoAVL{
  int chave;
	PtrNoAVL dir, esq;
  int altura;
} NoAVL;

void iniciaArvoreAVL(PtrNoAVL *no){
  (*no) = NULL;
}

bool estaVaziaArvoreAVL(PtrNoAVL *no) {
  return((*no) == NULL);
}

int alturaArvoreAVL(PtrNoAVL *no) {
  if ((*no) == NULL) return 0;
  else return (*no)->altura;
}

int atualizaAlturaNoAVL(PtrNoAVL *esq, PtrNoAVL *dir) {
  int ae, ad, ret;
  ae = alturaArvoreAVL(&(*esq));
  ad = alturaArvoreAVL(&(*dir));

  if(ae >= ad) {
    ret = ae + 1;
  } else {
    ret = ad + 1;
  }
  return (ret);
}

void rotacaoSimplesDireita(PtrNoAVL *p) {
  PtrNoAVL v = (*p)->esq;
  (*p)->esq  = v->dir;
  v->dir     = (*p);
  (*p)->altura = atualizaAlturaNoAVL(&(*p)->esq, &(*p)->dir);
  v->altura    = atualizaAlturaNoAVL(&(v->esq), &(v->dir));
  (*p) = v;
}

void rotacaoSimplesEsquerda(PtrNoAVL *p) {
  PtrNoAVL v = (*p)->dir;
  (*p)->dir  = v->esq;
  v->esq     = (*p);
  (*p)->altura = atualizaAlturaNoAVL(&(*p)->esq, &(*p)->dir);
  v->altura    = atualizaAlturaNoAVL(&(v->esq), &(v->dir));
  (*p) = v;
}

void rotacaoDuplaDireita(PtrNoAVL *p) {
  PtrNoAVL u = (*p)->esq;
  PtrNoAVL v = u->dir;
  u->dir     = v->esq;
  (*p)->esq  = v->dir;
  v->esq     = u;
  v->dir     = (*p);
  (*p)->altura = atualizaAlturaNoAVL(&(*p)->esq, &(*p)->dir);
  v->altura    = atualizaAlturaNoAVL(&(v->esq), &(v->dir));
  u->altura    = atualizaAlturaNoAVL(&(u->esq), &(u->dir));
  (*p) = v;
}

void rotacaoDuplaEsquerda(PtrNoAVL *p){
  PtrNoAVL u = (*p)->dir;
  PtrNoAVL v = u->esq;
  u->esq     = v->dir;
  (*p)->dir  = v->esq;
  v->esq     = (*p);
  v->dir     = u;
  (*p)->altura = atualizaAlturaNoAVL(&(*p)->esq, &(*p)->dir);
  v->altura    = atualizaAlturaNoAVL(&(v->esq), &(v->dir));
  u->altura    = atualizaAlturaNoAVL(&(u->esq), &(u->dir));
  (*p) = v;
}

void aplicarRotacoes(PtrNoAVL *no) {
  int ae, ad, fatorBalanceamento;
  ae = alturaArvoreAVL(&(*no)->esq);
  ad = alturaArvoreAVL(&(*no)->dir);
  fatorBalanceamento = ad - ae;
  PtrNoAVL u;
  int aUdir, aUesq;
  if(fatorBalanceamento == -2) {
    u = (*no)->esq;
    aUdir = alturaArvoreAVL(&u->dir);
    aUesq = alturaArvoreAVL(&u->esq);
    if(aUesq >= aUdir) {
      rotacaoSimplesDireita(&(*no));
    } else {
      rotacaoDuplaDireita(&(*no));
    }
  } else { // == +2
    u = (*no)->dir;
    aUdir = alturaArvoreAVL(&u->dir);
    aUesq = alturaArvoreAVL(&u->esq);

    if(aUdir >= aUesq) {
      rotacaoSimplesEsquerda(&(*no));
    } else {
      rotacaoDuplaEsquerda(&(*no));
    }
  }
}

bool insereArvoreAVL(PtrNoAVL *no, int valor) {
  if((*no) == NULL) {
    (*no) = malloc(sizeof(NoAVL));
    (*no)->esq = NULL;
    (*no)->dir = NULL;
    (*no)->chave = valor;
    (*no)->altura = 1;  // novidade na AVL

    return true;
  }

  if((*no)->chave == valor) {
    printf("Warning: elemento duplicado (%d), não inserindo\n",valor);
    return false;
  }

  bool ret;
  if(valor > (*no)->chave) {
    ret = insereArvoreAVL(&(*no)->dir, valor);
  } else {
    ret = insereArvoreAVL(&(*no)->esq, valor);
  }

  if(!ret) return false;

  int ad, ae, fatorBalanceamento;
  ad = alturaArvoreAVL(&(*no)->dir);
  ae = alturaArvoreAVL(&(*no)->esq);
  fatorBalanceamento = ad - ae;
  if(fatorBalanceamento == 2 || fatorBalanceamento == -2) {
    aplicarRotacoes(&(*no));
  }
  (*no)->altura = atualizaAlturaNoAVL(&(*no)->esq, &(*no)->dir);
  return true;
}

int ordenaVec(PtrNoAVL *no,int ord, int* array) {
  if((*no) == NULL) return ord;

  ord = ordenaVec(&(*no)->esq,ord,array);

	array[ord] = (*no)->chave;
	ord++;

	ord = ordenaVec(&(*no)->dir,ord,array);
}

void ordenaVetorUsandoArvore(int n, int *array){
	PtrNoAVL raiz;
  iniciaArvoreAVL(&raiz);

	if (n <= 0){
		printf("Array invalido!\nVerifique!\n");
		return;
	}

	for (int i = 0; i < n; i++){
		insereArvoreAVL(&raiz, array[i]);
	}

	ordenaVec(&raiz, 0, array);
}

#define tamanho 10

int main() {
	int valores[tamanho];

	printf("Informe %d valores.\n",tamanho);

	for (int i = 0; i < tamanho; i++){
		scanf("%d",&valores[i]);
	}

	for (int i = 0; i < tamanho; i++){
		printf("%d, ",valores[i]);
	}
	printf("\n");

	ordenaVetorUsandoArvore(tamanho, valores);

	for (int i = 0; i < tamanho; i++){
		printf("%d, ",valores[i]);
	}
	printf("\n");
  return 0;
}