#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isvogal(char c){
    char vogal[10] = "AEIOUaeiou";
    for (int i = 0; i < 10; i++)
    {
        if (c == vogal[i])
        {
            return(1);
        }
    }
    return(0);
}

int main(void){
    FILE *arq1,*arq2;

    arq1 = fopen("C:\\UTF\\atv2(entrada).txt", "r") ;
    arq2 = fopen("C:\\UTF\\atv2(saida).txt", "w") ;
    if (arq1 == NULL)
    {
        printf("Erro ao abrir o arquivo com o seu texto!");
        return 0;
    }
    if (arq2 == NULL)
    {
        printf("Erro ao abrir o arquivo com o seu texto!");
        return 0;
    }

    char c;
    int count=1;

    while (!feof(arq1))
    {
        //inp
        c = fgetc(arq1);
        //processo
        if(c == '\n') count++;
        if(isvogal(c)) c = '*';
        //out
        fprintf(arq2, "%c", c);
    }
    fclose(arq1);
    fclose(arq2);
    printf("Numero de linhas: %d",count);
}