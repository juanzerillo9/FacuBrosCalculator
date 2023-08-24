//Funcion Exponencial | x!
unsigned long expo(int x){
    unsigned long r=1;
    for (int i=1; i<=x ; i++)
        r= r*i;
    return r;
}
