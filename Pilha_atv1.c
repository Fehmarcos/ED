#include <stdio.h>
#define tamanho 1

typedef struct pilha{
    //pilha
    int vetor[tamanho];
    //index de qual a proxima posicao
    int topo;
}PilhaEstatica;

void inicializar(PilhaEstatica *p){//seta o topo para 0 zerando a pilha
    p->topo = 0;
}

int is_vazia(PilhaEstatica *p){//verifica se a pilha esta vazia
    if (p->topo == 0) return 1;
    return 0;
}

int is_cheia(PilhaEstatica *p){//verifica se a pilha esta cheia
    if (p->topo == tamanho) return 1;
    return 0;
}

int tam_pilha(PilhaEstatica *p){//retorna o tamanho da pilha
    return p->topo;
}

int tirar(PilhaEstatica *p){//remove ultimo item
    if (is_vazia(p)){
        printf("\nimposivel remover!\nA pilha esta vazia.\n");
        return -1;
    }
    int ret = p->vetor[p->topo];
    p->topo --;

    return ret;
}

int inserir(PilhaEstatica *p,int dado){//adiciona um item ao final da pilha
    if (is_cheia(p)){
        printf("\nimposivel adicionar!\nA pilha esta cheia\n"); 
        return -1;
    }
    p->vetor[p->topo] = dado;
    p->topo ++;
    return dado;
}

void mostra(PilhaEstatica *p){//imprime ate o topo da pilha
    int i,prox;
    printf("[");
    for (i = 0; i < p->topo; i++)
    {
        prox = i+1;
        printf("%d",p->vetor[i]);
        if (prox != p->topo)printf(", ");
    }
    printf("]\n");
}

int main(void){
    PilhaEstatica pilha;
    inicializar(&pilha);
    int op, dado = 0, ret = 0;

    while (1)
    {   
        printf("O-------------------------------O\n");
        printf("|1: inserir item                |\n");
        printf("|2: remover ultimo item da pilha|\n");
        printf("|3: visualizar a pilha          |\n");
        printf("|0: finaliza o progama          |\n");
        printf("O-------------------------------O\n");
        scanf("%d", &op);
        printf("\n");
        switch (op)
        {
        case 0:
            return 0;
            break;
        case 1:
            while (1){
                printf("Qual numero deseja guardar ?\n");
                scanf("%d",&dado);

                if (dado > 0)break;
                printf("O numero precisa ser positivo!\n");
            }
            ret = inserir(&pilha,dado);
            if (ret != -1) printf("\nO %d Foi guardado!\n",ret);
            break;
        case 2:
            ret = tirar(&pilha);
            if (ret != -1) printf("\nO %d Foi removido!\n",ret);
            break;
        case 3:
            mostra(&pilha);
            break;
        default:
            printf("Numero invalido\n");
            break;
        }
    }
}