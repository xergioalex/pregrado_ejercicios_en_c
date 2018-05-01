/*
  Name: MONTOESCRITO
  Copyright: TODOS LOS DERECHOS RESERVADOS
  Author: SERGIO ALEXANDER FLOREZ GALEANO 
  Date: 07/05/10 08:40
  Description: El siguiente programa recibe un numero desde 0 hasta 2000000000 (dos mil millones) 
               el cual es el entero mas grande que soporta C, pero si no existiera esta limitacion 
			   por parte de la maquina, el algoritmos iria hasta 999999999999(novecientos noventa 
			   y nueve mil novecientos noventa y nueve millones novecientos noventa y nueve mil 
			   novecientos noventa y nueve)
*/

void traducir(int numero);

int main(){
 	int numero;
 	printf("Por favor ingrese un numero\n");
 	scanf("%i",&numero);
 	traducir(numero);     
 	printf("\n");
 	system("pause");
}

void traducir(int numero){
    /* 1-15 */(numero==0)? printf("cero"):(numero==1)? printf("uno"):(numero==2)? printf("dos"):(numero==3)? printf("tres"):(numero==4)? printf("cuatro"):(numero==5)? printf("cinco"):(numero==6)? printf("seis"):(numero==7)? printf("siete"):(numero==8)? printf("ocho"):(numero==9)? printf("nueve"):(numero==10)? printf("diez"):(numero==11)? printf("once"):(numero==12)? printf("doce"):(numero==13)? printf("trece"):(numero==14)? printf("catorce"):(numero==15)? printf("quince"):(numero>15 && numero<20)? printf("dieci"):0,/* 16-19 */(numero>15 && numero<20)? traducir(numero-10):0,/* 20-99 */(numero>=20 && numero<100)? ((numero>=20 && numero<30)? ((numero==20)? printf("veinte"):printf("venti")):(numero>=30 && numero<40)? printf("treinta"):(numero>=40  && numero<50)? printf("cuarenta"):(numero>=50  && numero<60)? printf("cincuenta"):(numero>=60  && numero<70)? printf("sesenta"):(numero>=70  && numero<80)? printf("setenta"):(numero>=80  && numero<90)? printf("ochenta"):(numero>=90  && numero<100)? printf("noventa"):0,(numero%10>0)? ((numero<30)? 0:printf(" y "),(numero%10>0)? traducir(numero%10):0):0):0,/* 100-999 */(numero>=100 && numero<1000)? ((numero>=100 && numero<200)? ((numero==100)? printf("cien"):printf("ciento ")):(numero>=500 && numero<600)? printf("quinientos "):(((numero>=700 && numero<800)? printf("sete"):(numero>=900 && numero<1000)? printf("nove"):traducir(numero/100),printf("cientos "))),(numero%100 >0)? traducir(numero%100):0  ):0,/* 1000-999999 */(numero>=1000 && numero<1000000)? (((numero>=2000)? traducir(numero/1000):0),printf(" mil "),(numero%1000 > 0)? traducir(numero%1000):0):0,/* 1000000-100000000000*/(numero>=1000000 && numero<1000000000000)? ((numero>=1000000 && numero<2000000)? (printf("un "),printf("millon ")):(traducir(numero/1000000),printf(" millones ")),(numero%1000000 > 0)? traducir(numero%1000000):0):0;   
}
