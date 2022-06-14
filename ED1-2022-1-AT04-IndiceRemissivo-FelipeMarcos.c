#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct noarvore* ptrnoarvore;

typedef struct noarvore{
	char chave[1024];
	char pag[100];
	int presente;
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

int push(ptrnoarvore *no, char *chave){
	//inserir
	if ((*no)==NULL){
		(*no) = malloc(sizeof(noarvore));
		strcpy((*no)->chave, chave);
		(*no)->pag[0] = '\0';
		(*no)->presente = 0;
		(*no)->direita = NULL;
		(*no)->esquerda = NULL;
		return 1;
	}
	switch (strcmp(chave,(*no)->chave))
	{
	case 0://igual
		return  0;
		break;
	case -1://menor
		return push(&(*no)->esquerda,chave);
		break;
	case 1://maior
		return push(&(*no)->direita,chave);
		break;
	}
}

char* toMinuscula(char* s) {//https://stackoverflow.com/questions/2661766/how-do-i-lowercase-a-string-in-c
  for(char *p=s; *p; p++) *p=tolower(*p);
  return s;
}

void emordem(ptrnoarvore *no,FILE* saida){
	if(!(*no))return;
	emordem(&(*no)->esquerda,saida);
	fprintf(saida,"%s%s\n",(*no)->chave,(*no)->pag);
	emordem(&(*no)->direita,saida);
}
void zerapresente(ptrnoarvore *no){
	if (!(*no)){
		return;
	}

	(*no)->presente = 0;
	if ((*no)->direita){
		zerapresente(&((*no)->direita));
	}
	if ((*no)->esquerda){
		zerapresente(&((*no)->esquerda));
	}
}
ptrnoarvore busca(ptrnoarvore *no, char *busc){
	if (!(*no)){
		return NULL;
	}
	switch (strcmp(toMinuscula(busc),toMinuscula((*no)->chave))){
	case 0://igual
		return (*no);
		break;
	case -1://menor
		return busca(&(*no)->esquerda,busc);
		break;
	case 1://maior
		return busca(&(*no)->direita,busc);
		break;
	}
}
void addpage(ptrnoarvore *no, char *pag){
	if (!(*no)) return;//palavra nao esta presente nos termos da arvore
	if ((*no)->presente == 1)return;//pagina atual ja esta presente na string
	strcat((*no)->pag,",");
	strcat((*no)->pag,pag);
	(*no)->presente = 1;
}
int isletra(char c){
	if (c >= 'a' && c <= 'z')return 1;
	if (c >= 'A' && c <= 'Z')return 1;
	return 0;
}

int main(int argc, const char* argv[]){
	FILE* entrada;
	FILE* saida;
	switch (argc)
	{
	case 1:
		entrada = fopen("Entrada.txt", "r");
		saida = fopen("Saida.txt", "w");
		break;
	case 2:
		entrada = fopen(argv[1], "r");
		saida = fopen("Saida.txt", "w");
		break;
	case 3:
		entrada = fopen(argv[1], "r");
		saida = fopen(argv[2], "w");
		break;
	default:
		printf("Parametros invalidos!\n");
		break;
	}

	if (entrada == NULL) {
		printf("Erro ao criar o arquivo de entrada!\n");
		return 0;
	}
	if (feof(entrada)) {
		printf("Arquivo de entrada esta!\n");
		return 0;
	}
	if (saida == NULL) {
		printf("Erro ao criar o arquivo de saida!\n");
		return 0;
	}
	char buffer[1023];
	ptrnoarvore raiz;
	char page[5];
	page[0] = '\0';
	inicializa(&raiz);

	while (fgets(buffer,1024,entrada)){
		if(strncmp(buffer, "<termos:",8) == 0){
			char aux[25];
			int i = 0, j = 8;
			while (buffer[j] != '>'){
				if (buffer[j] == ','){
					push(&raiz, aux);
					i = 0;
					j++;
				}
				aux[i] = buffer[j];
				aux[i+1] = '\0';//a proxima sempre pode ser o fim
				i++;
				j++;
			}
			push(&raiz, aux);
		}else
		if (strncmp(buffer, "<page:",6) == 0){
			zerapresente(&raiz);//zera a variavel que diz a nivel de pagina se o termo esta contido
			sscanf(buffer+6,"%c",&page);
		}else{
			char aux[25];
			int i = 0, j = 0;
			while (1){
				if (!isletra(buffer[j])){
					ptrnoarvore find;
					inicializa(&find);
					if (aux[0] == '\n') break;
					find = busca(&raiz,aux);
					addpage(&find,page);
					i = 0;
					if (buffer[j] == '\n' || (buffer[j] == '.' && buffer[j] == '\n'))break;
					j++;
				}else{
					aux[i] = buffer[j];
					aux[i+1] = '\0';//a proxima sempre pode ser o fim
					i++;
					j++;
				}
			}
		}
	}
	emordem(&raiz,saida);
}