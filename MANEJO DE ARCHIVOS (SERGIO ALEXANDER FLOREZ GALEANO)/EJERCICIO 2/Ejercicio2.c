/*
  Name:  CONTAR LETRAS DEL ALFABETO
  Copyright: TODOS LOS DERECHOS RESERVADOS
  Author: SERGIO ALEXANDER FLOREZ GALEANO
  Date: 07/03/06 22:18
  Description: ESTE PROGRAMA LEE UN ARCHIVO.txt Y CUENTA LA CANTIDAD DE CADA 
               UNA DE LAS LETRAS DEL ABECEDARIO QUE HAY
*/


#include <stdio.h>
#include <ctype.h>

main()
{
      FILE *arch;
      char temp;
      int ascii_temp=0,cadena[26],i;
      //Inicializa el arreglo en 0
      for (i=0;i<26;i++)
      {
          cadena[i]=0;
      }
      //aca se abre el archivo
      arch = fopen("frecuencia.txt","r");
      //Aca se llena el arreglo
      while((temp=fgetc(arch)) != EOF)
      {
            if(isupper(temp))
                temp= towlower(temp);
            ascii_temp=temp;
            ascii_temp -=97;
            cadena[ascii_temp] +=1;
      }
      //Aca se imprime el arreglo 
      for (i=0;i<26;i++)
      {
          printf("%c = %i\n",i+97,cadena[i]);
      }
      
      fclose(arch);  
      system("PAUSE");           
}
