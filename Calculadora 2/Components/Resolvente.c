#include <stdio.h>
#include <stdlib.h>
#include <math.h>


float resultado(float x, float y, float z,float *xr,float *xt, float *yr);
int main()
{
    float x, y, z,xr,yr,xt;
    do{
        printf("escribe el termino cuadratico (x) = ");
        scanf("%f",&x);
    } while (x==0);
    printf("escribe el termino  x (y) = ");
    scanf("%f",&y);
    printf("escribe el termino independiente (z) = ");
    scanf("%f",&z);
    resultado(x,y,z,&xr,&xt,&yr);
        if (xt==99999)
            printf("los terminos dan raiz negativa, no es posible");
        else{
            printf("Raiz 1= %.2f\n",xr);
            printf("Raiz 2= %.2f",yr);
        }
    return 0;
}

float resultado(float x, float y, float z,float *xr,float *xt, float *yr){
    float raiz, parcial;
    raiz= ((y*y)-(4*x*z));
        if (raiz<0){
            *xt=99999;
            return 0;
        }
        else{
            parcial = sqrt (raiz);
            *xr = ((-y-parcial)/(2*x));
            *yr = ((-y+parcial)/(2*x));
            return 0;
        }
}
