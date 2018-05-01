/*
  Name: Pasar de minusculas.txt  a MAYUSCULAS.TXT
  Copyright: TODOS LOS DERECHOS RESERVADOS
  Author: SERGIO ALEXANDER FLOREZ GALEANO
  Date: 12/04/10 14:51
  Description: Este programa lee un texto de un archivo llamado minusculas.txt
               y crea uno nuevo llamado MAYUSCULAS.TXT, y copia el contenido del 
               primer archivo en el segundo pero en mayusculas.
*/


#include <ctype.h>
#include <stdio.h>


main()
{
      FILE *minusculas, *MAYUSCULAS;
      char temp;
      int i=0;
      
      minusculas = fopen("minusculas.txt","r");
      MAYUSCULAS = fopen("MAYUSCULAS.txt","a");
      MAYUSCULAS = fopen("MAYUSCULAS.txt","w");
      while((temp=fgetc(minusculas)) != EOF)
      {
            fputc(toupper(temp),MAYUSCULAS);
            i++;
            
      }
      fclose(minusculas);
      fclose(MAYUSCULAS);          
}
