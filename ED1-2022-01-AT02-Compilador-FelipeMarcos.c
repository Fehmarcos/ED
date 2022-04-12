#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int TIPO_PILHA;

typedef struct Dado* PtrDado;

typedef struct Dado {
  TIPO_PILHA valor;
  PtrDado proximo;
} Dado;
typedef struct {
  PtrDado topo;
  int tamanho;
} PilhaDinamica;
void iniciaPd(PilhaDinamica *pd) {
  pd->topo = NULL;
  pd->tamanho = 0;
}
int tamanhoPd(PilhaDinamica *pd) {
  return(pd->tamanho);
}
int estaVaziaPd(PilhaDinamica *pd) {
  return(pd->tamanho == 0);
}
void push(PilhaDinamica *pd, TIPO_PILHA val){
    PtrDado Aux = NULL;
    Aux = (PtrDado)malloc(sizeof(Dado));
    if (estaVaziaPd(pd))
    {
        Aux->proximo = NULL;
        Aux->valor = val;
    }else{
        Aux->proximo = pd->topo;
        Aux->valor = val;
    }
    pd->topo = Aux;
    pd->tamanho++;
}
TIPO_PILHA pop(PilhaDinamica *pd){
    char val;
    PtrDado Aux = pd->topo;

    val = pd->topo->valor;
    pd->topo = Aux->proximo;
    pd->tamanho--;

    free(Aux);

    return val;
}
int letra(char c){
	if (c >= 'A' && c <= 'Z')return 1;
	return 0;
}
int operador(char c){
	if (c == '+')return 1;
	if (c == '-')return 2;
	if (c == '*')return 3;
	if (c == '/')return 4;

	return 0;
}
int main(int argc, const char * argv[]) {
	#pragma region valida
	//valida se o progama e executavel no estado atual
    if(argc!= 3) {
      printf("Quantidade de parametros invalida\n");
      return 0;
    }

    FILE* entrada = fopen(argv[1], "r");
    FILE* saida   = fopen(argv[2], "w");

    if(entrada == NULL) {
      printf("Erro ao criar o arquivo de entrada!\n");
      return 0;
    }
		if(feof(entrada)){
			printf("Arquivo de entrada esta!\n");
      return 0;
		}
    if(saida == NULL) {
      printf("Erro ao criar o arquivo de saida!\n");
      return 0;
    }
	#pragma endregion
	PilhaDinamica pilha;
  iniciaPd(&pilha);
	TIPO_PILHA info;
	int caso, x, y, flag;
	int temp = 100, casotemp = 0;//0 nem um temp, 1 x é temp, 2 y é temp, 3 x e y sao temp
	char op[10];
	char tempbuff[128], buff[1024], aux[128];

	while (info = fgetc(entrada)) {
		if (info == EOF || info == '\n' || info == ' ')break;;

		if (flag) {
			push(&pilha, temp); //guarda a quantidade (com um offset de 100 para servir de sepação EX: 111 = 11) de TEMP que foram usadas durante a execuçao
			flag = 0;
			strcat(buff, tempbuff);
		}

		if (letra(info)){
			push(&pilha,info);
		}else if(operador(info) && tamanhoPd(&pilha) >= 2){
			caso = operador(info); //1= '+'|2= '-'|3= '*'|4= '/'|
			x = pop(&pilha);
			if(x > 100){
				sprintf(aux, "LDR TEMP%d\n",x - 100);//desconciderar o offset
				strcat(buff, aux);
				casotemp = 1;//x é temp
			}else{
				sprintf(aux, "LDR %c\n",x);
				strcat(buff, aux);
			}
			y = pop(&pilha);
			if(y > 100){
				sprintf(aux, "LDR TEMP%d\n",y - 100);//desconciderar o offset
				strcat(buff, aux);
				if (casotemp == 1)casotemp = 3;//abos sao temp
				if (casotemp == 0)casotemp = 2;//y é temp
			}else{
				sprintf(aux, "LDR %c\n",y);
				strcat(buff, aux);
			}

			switch (caso)
			{
			case 1://|'+'|
				strcpy(op,"ADD");
				break;
			case 2://|'-'|
				strcpy(op,"SUB");
				break;
			case 3://|'*'|
				strcpy(op,"MUL");
				break;
			case 4://|'/'|
				strcpy(op,"DIV");
				break;
			}

			switch (casotemp)
			{
			case 0:
				sprintf(aux, "%s %c %c\n",op ,x ,y);
				strcat(buff, aux);
				break;
			case 1:
				sprintf(aux, "%s TEMP%d %c\n",op ,x-100 ,y);
				strcat(buff, aux);
				break;
			case 2:
				sprintf(aux, "%s %c TEMP%d\n",op ,x ,y-100);
				strcat(buff, aux);
				break;
			case 3:
				sprintf(aux, "%s TEMP%d TEMP%d\n",op ,x-100 ,y-100);
				strcat(buff, aux);
				break;
			}

			if (feof(entrada))return 1;
			temp ++;
			sprintf(tempbuff, "STR TEMP%d\n", temp - 100);
			flag = 1;
		}else break;
	}
	if(buff[1] == '\0' || tamanhoPd(&pilha) > 0){
		fprintf(saida,"Expressão inválida!");
		return 0;
	}else{
		fprintf(saida,buff);
		return 1;
	}
}