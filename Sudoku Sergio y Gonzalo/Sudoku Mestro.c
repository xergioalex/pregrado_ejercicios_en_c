/*
  Name: SUDOKU
  Copyright: Todos los derechos reservados
  Author: Sergio Alexander Florez Galeano 
          Gonzalo de Jesus Ramirez Ramirez
  Date: 14/03/10 18:35
  Description: Este programa es un juego denominado sudoku, donde se debe completar una matriz de 9x9 con numeros del 1 al 9
               procurando que no se repitan numeros segun ciertas condiciones.
               El programa muestra en pantalla el tablero, y espera a que se inserten todos los numeros, y cuando el tablero 
               esta terminado verifica si la combinacion es correcta o incorreta. 
*/


void imprimir_sudoku(int sudoku[9][9]);
int pedir_datos(int posicion,int tipo);
int validar_sudoku(int sudoku[9][9]);
int validar_region(int sudoku[9][9]);
int validar_numero_en_region(int sudoku[9][9],int fila,int filalim,int columna,int columnalim,int posf,int posc);

int main()
{
   system("COLOR F0");
   //Declarar e inicializar variables
   int sudoku[9][9],i,j,valores[9][9]={4,2,0,0,1,0,0,0,0,3,0,0,5,4,9,1,0,0,0,9,7,0,0,0,0,5,0,8,0,0,0,6,0,0,0,3,5,0,0,2,0,4,0,0,8,2,0,0,0,5,0,0,0,1,0,1,0,0,0,0,3,4,0,0,0,0,4,2,5,0,0,7,0,0,0,0,3,0,0,8,6};
   //valores[9][9]={4,2,5,7,1,6,8,3,9,3,6,8,5,4,9,1,7,2,1,9,7,3,8,2,6,5,4,8,4,9,1,6,7,5,2,3,5,3,1,2,9,4,7,6,8,2,7,6,8,5,3,4,9,1,9,1,2,6,7,8,3,4,5,6,8,3,4,2,5,9,1,7,7,5,4,9,3,1,2,8,6};
   int cont_ceros=0,valor=-1,fila,columna,continuar,validar,bandera_de_ceros=0;
   //Llenar Matriz con valores sudoku
   for (i=0 ; i<9 ; i++)
   {
       for (j=0 ; j<9 ; j++)
       {
           sudoku[i][j]=valores[i][j];
           if (valores[i][j]==0)
              cont_ceros++;
       }
   }
   //Jugar Sudoku
   while(cont_ceros>0)
   {
        continuar=0;
        validar=0;
        imprimir_sudoku(sudoku);
        printf("\nRecuerde que solo puede ingresar numeros del 0 al 8, si es una posicion o \nNumeros del 1 al 9 si son valores a ingresar\n\n");
        while(continuar==0)
        {
             fila=pedir_datos(valor,0);
             columna=pedir_datos(valor,1);
             if (valores[fila][columna]==0)
             {
                if(sudoku[fila][columna]==0)
                    bandera_de_ceros=1;                         
                sudoku[fila][columna]=pedir_datos(valor,2);
                continuar=1;
                 
             } 
             else
             {
                 printf("Lo siento pero esa posicion no se puede modificar\n");
             }
        }
        if (bandera_de_ceros==1)
           cont_ceros--;
        bandera_de_ceros=0;           
   }   
   imprimir_sudoku(sudoku);     
   if (validar_sudoku(sudoku)==1)
   {
      printf("\nLO SIENTO PERO SU COMBINACION NO SATISFACE EL SUDOKU\n");
      system("COLOR FC");
   }
   else
   {
       printf("\n¡GANASTE!... --FELICITACIONES--\n");
       system("COLOR F1");
   }
   system("PAUSE");
}



//------------------------------------------------------------------------------

//Funcion que imprime el sudoku
void imprimir_sudoku(int sudoku[9][9])
{
   int i,j;
   system("cls");
   printf("\n              SUDOKU\n\n");
   printf("     0  1  2   3  4  5   6  7  8");
   printf("\n");
   printf("  ******************************\n");
   for (i=0 ; i<9 ; i++)
   {
       
       if (i>0 && i%3==0)
              printf("  * ----------------------------\n");
       printf("%i",i);
       printf(" * ");
           
       for (j=0 ; j<9 ; j++)
       {
           if (j>0 && j%3==0)
              printf("|");
           if (sudoku[i][j]==0)
               printf(" _ ");
           else
               printf(" %i ",sudoku[i][j]);     
       }
       printf("\n");
   }
}  

//------------------------------------------------------------------------------

//Funcion que pide datos del sudoku por pantalla
int pedir_datos(int posicion,int tipo)
{
    int n=0;
    if (tipo==2)
        n=1;
    while (!(posicion>-1+n && posicion<9+n))
        {
           if(tipo==0)
              printf("Ingrese la posicion fila: ");
           if(tipo==1)
              printf("Ingrese la posicion columna: ");
           if(tipo==2)
              printf("Ingrese valor a insertar: ");
           scanf("%i",&posicion);
        }  
        return posicion;
}       

//------------------------------------------------------------------------------
//VALIDA QUE SE CUMPLAN LAS REGLAS DEL SUDOKU

//Valida las filas y las columnas del sudoku y y las regiones llamando a otra funcion
int validar_sudoku(int sudoku[9][9])
{
    int i,j,x,y,z,limf1=0,limf2=2,limc1=0,limc2=2;
    //Verifica las filas y las columnas
    for (i=0;i<9;i++)
    {
        for (j=0;j<9;j++)
        {
            for (z=j+1;z<9;z++)
            {
                if (sudoku[i][j]==sudoku[i][z])
                   return 1;
                if (sudoku[j][i]==sudoku[z][i])
                   return 1;      
            }
        }
    }
    if (validar_region(sudoku) == 1)  
        return 1;
    return 0;
} 

//Valida cada region del sudoku
int validar_region(int sudoku[9][9])
{
    int i,j,k,f=0,fl=2,c=0,cl=2;
    for (i=1;i<=9;i++)
    {
         for(j=0;j<3;j++)
         {
             for(k=0;k<3;k++)
             {
                if(validar_numero_en_region(sudoku,f,fl,c,cl,j+f,k+c)==1)
                  return 1;
             }
         }
         c+=3;
         cl+=3;
         if(cl==11)
         {
             f+=3;
             fl+=3;
             c=0;
             cl=2;
         }
         
         
    }      
    return 0;
}

    
//Valida que un solo numero dentro de una region especifica del sudoku
int validar_numero_en_region(int sudoku[9][9],int fila,int filalim,int columna,int columnalim,int posf,int posc)
{
    int i,j,z;
    for (i=fila ; i<=filalim ; i++)
    {
        for (j=columna ; j<=columnalim ; j++)
        {
            if (!(i==posf && j==posc))
            {
                if(sudoku[posf][posc]==sudoku[i][j])
                    return 1;
            }
        }
    }    
    return 0;
}

//valores[9][9]={4,2,5,7,1,6,8,3,9,3,6,8,5,4,9,1,7,2,1,9,7,3,8,2,6,5,4,8,4,9,1,6,7,5,2,3,5,3,1,2,9,4,7,6,8,2,7,6,8,5,3,4,9,1,9,1,2,6,7,8,3,4,5,6,8,3,4,2,5,9,1,7,7,5,4,9,3,1,2,8,6};
//valores[9][9]={1,0,0,0,0,0,9,4,8,0,6,7,0,0,0,0,0,5,0,8,0,4,3,2,6,0,0,3,0,8,0,5,0,0,6,2,0,0,0,3,0,1,0,0,0,5,9,0,0,7,0,4,0,0,0,4,9,5,8,0,0,0,0,0,0,1,6,0,7,0,0,3,7,0,6,0,1,9,5,8,0};
//valores[9][9]={5,3,0,0,7,0,0,0,0,6,0,0,1,9,5,0,0,0,0,9,8,0,0,0,0,6,0,8,0,0,0,6,0,0,0,3,4,0,0,8,0,3,0,0,1,7,0,0,0,2,0,0,0,6,0,6,0,0,0,0,2,8,0,0,0,0,4,1,9,0,0,5,0,0,0,0,8,0,0,7,9};
//valores[9][9]={4,2,0,0,1,0,0,0,0,3,0,0,5,4,9,1,0,0,0,9,7,0,0,0,0,5,0,8,0,0,0,6,0,0,0,3,5,0,0,2,0,4,0,0,8,2,0,0,0,5,0,0,0,1,0,1,0,0,0,0,3,4,0,0,0,0,4,2,5,0,0,7,0,0,0,0,3,0,0,8,6};
