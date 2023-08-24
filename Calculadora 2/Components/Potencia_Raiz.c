//Funcion de potencia | X Base | Y Exponente 
float pot(float x, float y){
    
    float result=x;
    for (int i=1; i<y ; i++)
        result=result*x;
    return result;
}

// Funcion de Raiz | X Radicando | Y Indice
float raiz(float x, float y){
    float r=0;
    float z;
    int i;
    for (i=1; i<x ; i++){
        z=1;
        for (int j=0; j<y; j++){
            z*=i;
        }
        if (z==x){
            r=i;
            break;
        }
    }
    return r;
}
