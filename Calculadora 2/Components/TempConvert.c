//Convertir entre Escalas de Temperaturas
// OP Escala original (°C, °K, °F)
// RES Escala Final (°C, °K, °F)
// X Valor de Temperatura Original
// R Valor Final
//1=°C | 2=°F | 3=°K
float temp(int op, int res, float x){
    float r=0;
    switch (op){
        case 1:
            switch(res){
                case 2:
                    r= (x*((float)9/5)+32);
                    break;
                case 3:
                    r=x+273.15;
                    break;
            }
            break;
        case 2:
            switch(res){
                case 1:
                    r= (x - 32)*((float)5/9);
                    break;
                case 3:
                    r= ((x - 32.00)*((float)5/9))+273.15;
                    break;
            }
            break;
        case 3:
            switch(res){
                case 1:
                    r = x-273.15;
                    break;
                case 2:
                    r = (((x - 273.15) * ((float)9/5)) + 32); 
                    break;
            }
            break;
    }
    return r;
}
