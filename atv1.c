#include <stdio.h>
void minToHora(int tm, int *m, int *h){
    *h = tm/60;
    *m = tm%60;
}
int main(void){
    int a;
    int b=0,c=0;

    a=120;

    minToHora(a, &b, &c);
    printf("%.2d:%.2d",c,b);

    return 0;
}