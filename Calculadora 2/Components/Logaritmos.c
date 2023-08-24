#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//falta pulir
int main()
{
    float base,term,i,fin;
    printf("ingrese la base del log\n");
    scanf("%f",&base);
    printf("ingrese el termino a trabajar\n");
    scanf("%f",&term);
    i=-10;
    do{
        fin= pow(base,i);
        i++;
    }while (fin != term);
    printf("el resultado del logaritmo es %.2f", (i-1));

    return 0;
}
