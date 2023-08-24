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
