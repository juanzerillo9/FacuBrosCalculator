//Funcion de potencia | X Base | Y Exponente 
float pot(float x, float y){
    
    float result=x;
    for (int i=1; i<y ; i++)
        result=result*x;
    return result;
}
