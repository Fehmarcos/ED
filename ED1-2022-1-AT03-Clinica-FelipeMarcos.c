#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pessoa{
	int id;
	char nome[100];
	char sexo[100];
	char idade[100];
	char peso[100];
	char altura[100];
	char telefone[100];
}pessoa;

typedef struct Dado* PtrDado;
typedef struct Dado {//no de lista
	pessoa paciente;
	PtrDado proximo;
	PtrDado anterio;
} Dado;
typedef struct {//lista
  Dado sentinela;
  int tamanho;
} ListaOrd;

void inicia(ListaOrd *lo){
	lo->sentinela.paciente.id = -1;
	lo->sentinela.proximo = NULL;
	lo->sentinela.anterio = NULL;
	lo->tamanho = 0;
}
int vazia(ListaOrd *lo){
	return(lo->tamanho == 0);
}
int tamanho(ListaOrd *lo){
	return(lo->tamanho);
}

void loprint(ListaOrd *lo, FILE* saida){
	PtrDado aux = lo->sentinela.proximo;
	pessoa p;
	while(1){
		p  = aux->paciente;
		fprintf(saida,"{%d,%s,%s,%s,%s,%s,%s}\n",p.id,p.nome,p.sexo,p.idade,p.peso,p.altura,p.telefone);
		if(aux->proximo == NULL)break;
		aux = aux->proximo;
	}
}
void loprintdec(ListaOrd* lo, FILE* saida) {
	PtrDado aux = lo->sentinela.anterio;
	pessoa p;
	printf("\n");
	while (1){
		p  = aux->paciente;
		fprintf(saida,"{%d,%s,%s,%s,%s,%s,%s}\n",p.id,p.nome,p.sexo,p.idade,p.peso,p.altura,p.telefone);
		if (aux->anterio == NULL)break;
		aux = aux->anterio;
	}
	printf("\n");
}
int search(ListaOrd *lo,int val, FILE* saida){
	if(vazia(lo))return 0;
	PtrDado aux;
	aux = lo->sentinela.anterio;
	if(val > aux->paciente.id)return 0;
	if(val == aux->paciente.id){
		pessoa p = aux->paciente;
		fprintf(saida,"{%d,%s,%s,%s,%s,%s,%s}\n",p.id,p.nome,p.sexo,p.idade,p.peso,p.altura,p.telefone);
	}
	aux = lo->sentinela.proximo;
	if(val < aux->paciente.id)return 0;
	if(val == lo->sentinela.proximo->paciente.id){
		pessoa p = aux->paciente;
		fprintf(saida,"{%d,%s,%s,%s,%s,%s,%s}\n",p.id,p.nome,p.sexo,p.idade,p.peso,p.altura,p.telefone);
	}

	if (lo->tamanho == 2)return 0;//tamanho 2 mas nao tendo o dado em nem uma das estremidades da lista cai fora

	while(1){
		aux = aux->proximo;
		if(val == aux->paciente.id)break;
		if(aux->proximo == NULL)return 0;
	}
	pessoa p = aux->paciente;
	fprintf(saida,"{%d,%s,%s,%s,%s,%s,%s}\n",p.id,p.nome,p.sexo,p.idade,p.peso,p.altura,p.telefone);
}

void push(ListaOrd *lo, pessoa p){
	PtrDado new;

	new = (PtrDado)malloc(sizeof(Dado));
	new->paciente = p;

	if (vazia(lo)){
		new->proximo = NULL;
		new->anterio = NULL;
		lo->sentinela.proximo = new;
		lo->sentinela.anterio = new;
	}else if(new->paciente.id < lo->sentinela.proximo->paciente.id){
		new->proximo = lo->sentinela.proximo;
		new->anterio = NULL;
		lo->sentinela.proximo->anterio = new;
		lo->sentinela.proximo = new;
	}else if(new->paciente.id > lo->sentinela.anterio->paciente.id){
		new->proximo = NULL;
		new->anterio = lo->sentinela.anterio;
		lo->sentinela.anterio->proximo = new;
		lo->sentinela.anterio = new;
	}else{
		PtrDado auxpro =  lo->sentinela.proximo;
		PtrDado auxant = NULL;
		while(p.id > auxpro->paciente.id){
			auxant = auxpro;
			auxpro = auxpro->proximo;
		}
		new->proximo = auxpro;
		new->anterio = auxant;
		auxant->proximo = new;
		auxpro->anterio = new;
	}
	lo->tamanho++;
}

int primeiro(ListaOrd *lo){
	return lo->sentinela.proximo->paciente.id;
}
int ultimo(ListaOrd *lo){
	return lo->sentinela.anterio->paciente.id;
}

int main(int argc, const char* argv[]) {
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
		printf("Arquivo de entrada esta vazio!\n");
		return 0;
	}
	if (saida == NULL) {
		printf("Erro ao criar o arquivo de saida!\n");
		return 0;
	}

	ListaOrd lo;
	inicia(&lo);
	//#pega dados
	char buffer [1024];
	pessoa p;
	int rc,busc,count,i = 1,j = 0,pos = 1;
	int valid = 1; //1 = ta top / 0 = ta errado isso ai
	char c = '.',copy[100];
	while (fgets(buffer,1024,entrada)){//loop para ler o arquivo inteiro
		if (buffer[0]=='{'){
			while (buffer[i] != '\n'){//loop por linha
				if (buffer[i] == ',' || buffer[i] ==  '}'){//separaçao por campo
					copy[j] = '\0';
					switch (pos)
					{
					case 1://id
						if(copy[0]=='\0'){
							valid = 0;
						}else{
							p.id = atoi(copy);
						}
						break;
					case 2://nome
						if(copy[0]=='\0'){
							valid = 0;
						}else{
							strcpy(p.nome,copy);
						}
						break;
					case 3://sexo
						if(copy[0]=='\0'){
							valid = 0;
						}else{
							strcpy(p.sexo,copy);
						}
						break;
					case 4://idade
						if(copy[0]=='\0'){
							valid = 0;
						}else{
							strcpy(p.idade,copy);
						}
						break;
					case 5://peso
						if(copy[0]=='\0'){
							valid = 0;
						}else{
							strcpy(p.peso,copy);
						}
						break;
					case 6://altura
						if(copy[0]=='\0'){
							valid = 0;
						}else{
							strcpy(p.altura,copy);
						}
						break;
					case 7://telefone
						strcpy(p.telefone,copy);
						break;
					default:
						fprintf(saida,"Entrada Invalida!\n");
						printf("Code:1\n");
						return 0;
						break;
					}
					pos++;
					copy [0] = '\0';
					j = 0;
					i++;
				}else{
					copy[j] = buffer[i];
					j++;
					i++;
				}
			}
			if (valid == 0 || pos != 8){
				fprintf(saida,"Entrada Invalida!\n");
				printf("Code:0\n");
				return 0;
			}

			push(&lo,p);
			count++;

			copy [0] = '\0';
			j = 0;
			pos = 1;
			i = 1;
		}else{
			if (count < 1)
			{
				fprintf(saida,"Entrada Invalida!\n");
				printf("Code:2\n");
				return 0;
			}

			switch (buffer[0]){
			case '1':
				loprint(&lo, saida);
				return 1;
				break;
			case '2':
				loprintdec(&lo, saida);
				return 1;
				break;
			case '3':
				fgets(buffer,1024,entrada);
				sscanf(buffer,"%d",&busc);
				//int ret = ;
				if (search(&lo,busc, saida) < 1){
					fprintf(saida, "Elemento %d não encontrado!",busc);
					return 0;
				}else return 1;
				break;
			default:
				fprintf(saida,"Entrada Invalida!\n");
				printf("Code:2\n");
				return 0;
				break;
			}
		}
	}
}