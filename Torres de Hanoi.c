#include <stdio.h>
#define tamanho 5

typedef struct pilha{
	int vetor[tamanho];
	int topo;
	char id;
}PilhaEstatica;

int pop(PilhaEstatica *p){
    int ret = p->vetor[p->topo];
		p->vetor[p->topo] = 0;
    p->topo --;

		printf("Removido o %d da Torre %c\n",ret,p->id);

    return ret;
}
void push(PilhaEstatica *p,int dado){
    p->topo ++;
    p->vetor[p->topo] = dado;

		printf("Adicionado o %d a Torre %c\n",dado,p->id);
}
void pushinicial(PilhaEstatica *p,int dado){
    p->topo ++;
    p->vetor[p->topo] = dado;
}
void inicializar(PilhaEstatica *p){
	p->topo = -1;
	pushinicial(p,0);
	pushinicial(p,0);
	pushinicial(p,0);
	pushinicial(p,0);
	pushinicial(p,0);
	p->topo = -1;
}
void inicializarcheia(PilhaEstatica *p){
	inicializar(p);
	pushinicial(p,5);
	pushinicial(p,4);
	pushinicial(p,3);
	pushinicial(p,2);
	pushinicial(p,1);
}

int mostra(PilhaEstatica *a,PilhaEstatica *b,PilhaEstatica *c,int count){
	printf("\n--%c--%c--%c--\n",a->id,b->id,c->id);
	for (int i = 4; i >= 0; i--){
		printf("  %d  %d  %d  \n",a->vetor[i] ,b->vetor[i] ,c->vetor[i]);
	}
	printf("-----------\n");
	if (count > 0)printf("Movimento %d\n",count);
	return count + 1;
}
void mov(PilhaEstatica * in,PilhaEstatica *to){
	push(to,pop(in));
}
int main(void){
	int count=0;
	PilhaEstatica a,b,c;
	inicializarcheia(&a);
	a.id='A';
	inicializar(&b);
	b.id='B';
	inicializar(&c);
	c.id='C';
	count = mostra(&a,&b,&c,count);

	mov(&a ,&c );count = mostra(&a,&b,&c,count);
	mov(&a ,&b );count = mostra(&a,&b,&c,count);
	mov(&c ,&b );count = mostra(&a,&b,&c,count);
	mov(&a ,&c );count = mostra(&a,&b,&c,count);
	mov(&b ,&a );count = mostra(&a,&b,&c,count);
	mov(&b ,&c );count = mostra(&a,&b,&c,count);
	mov(&a ,&c );count = mostra(&a,&b,&c,count);
	mov(&a ,&b );count = mostra(&a,&b,&c,count);
	mov(&c ,&b );count = mostra(&a,&b,&c,count);
	mov(&c ,&a );count = mostra(&a,&b,&c,count);
	mov(&b ,&a );count = mostra(&a,&b,&c,count);
	mov(&c ,&b );count = mostra(&a,&b,&c,count);
	mov(&a ,&c );count = mostra(&a,&b,&c,count);
	mov(&a ,&b );count = mostra(&a,&b,&c,count);
	mov(&c ,&b );count = mostra(&a,&b,&c,count);
	mov(&a ,&c );count = mostra(&a,&b,&c,count);
	mov(&b ,&a );count = mostra(&a,&b,&c,count);
	mov(&b ,&c );count = mostra(&a,&b,&c,count);
	mov(&a ,&c );count = mostra(&a,&b,&c,count);
	mov(&b ,&a );count = mostra(&a,&b,&c,count);
	mov(&c ,&b );count = mostra(&a,&b,&c,count);
	mov(&c ,&a );count = mostra(&a,&b,&c,count);
	mov(&b ,&a );count = mostra(&a,&b,&c,count);
	mov(&b ,&c );count = mostra(&a,&b,&c,count);
	mov(&a ,&c );count = mostra(&a,&b,&c,count);
	mov(&a ,&b );count = mostra(&a,&b,&c,count);
	mov(&c ,&b );count = mostra(&a,&b,&c,count);
	mov(&a ,&c );count = mostra(&a,&b,&c,count);
	mov(&b ,&a );count = mostra(&a,&b,&c,count);
	mov(&b ,&c );count = mostra(&a,&b,&c,count);
	mov(&a ,&c );count = mostra(&a,&b,&c,count);

	if (count == 31)	printf("Solução mais otimizada encotrada!");//hehe https://www.youtube.com/watch?v=Inm3Ie-4aKI

}