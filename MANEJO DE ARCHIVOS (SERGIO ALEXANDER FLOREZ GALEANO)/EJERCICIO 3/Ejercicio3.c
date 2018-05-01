/*
  Name:  ENCRITADO POR CESAR
  Copyright: TODOS LOS DERECHOS RESERVADOS
  Author: SERGIO ALEXANDER FLOREZ GALEANO
  Date: 07/03/06 22:18
  Description: ESTE PROGRAMA LEE UN ARCHIVO.txt Y ENCRITA SU CONTENIDO SEGUN 
               EL ALGORITMO CESAR.
*/


#include <stdio.h>
#include <ctype.h>
#include <math.h>

main()
{
      FILE *sinencriptar, *encriptado;
      char temp;
      int ascii_temp=0,i;

      sinencriptar = fopen("sinencriptar.txt","r");
      encriptado = fopen("encriptado_por_cesar.txt","a");
      encriptado = fopen("encriptado_por_cesar.txt","w");
      
      //Aca se pasan las letras encriptadas por cesar 
      while((temp=fgetc(sinencriptar)) != EOF)
      {
            
            ascii_temp=temp;
            if(islower(temp))
               ascii_temp =(((ascii_temp - 97) + 3)%26)+97;
            if(isupper(temp))
               ascii_temp =(((ascii_temp - 65) + 3)%26)+65;
            temp=ascii_temp;
            
            fputc(temp,encriptado);
      }
      fclose(sinencriptar);
      fclose(encriptado);  
                 
}
