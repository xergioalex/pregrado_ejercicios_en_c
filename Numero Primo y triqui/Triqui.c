int main()
{
   //Declarar e inicializar variables
   int triki[3][3],i,j;
   int jugador_1,jugador_2;
   int jugada,posicion;
   jugador_1=1;
   jugador_2=0;
   jugada=1;
   posicion = 0;
   //Llenar Matriz triqui con -1
   for (i=0 ; i<3 ; i++)
   {
       for (j=0 ; j<3 ; j++)
       {
           triki[i][j]=5;
       }
       printf("\n");
   }  
   //Jugar triki
   while (jugada <= 9)
   {
         system("cls");
         printf("|1|2|3|4|5|6|7|8|9|\n\n|%i|%i|%i|\n|%i|%i|%i|\n|%i|%i|%i|\n",triki[0][0],triki[0][1],triki[0][2],triki[1][0],triki[1][1],triki[1][2],triki[2][0],triki[2][1],triki[2][2],"\n");
         printf("ingrese una posicion: ");
         scanf("%i",&posicion);
         if(triki[posicion/3][(posicion%3)-1] == 5)
         {
             triki[posicion/3][(posicion%3)-1]= jugada%2;
             jugada++;
         }
         if ((triki[0][0]==jugador_1 && triki[0][1]==jugador_1 && triki[0][2]==jugador_1) || (triki[1][0]==jugador_1 && triki[1][1]==jugador_1 && triki[1][2]==jugador_1) ||(triki[2][0]==jugador_1 && triki[2][1]==jugador_1 && triki[2][2]==jugador_1) ||(triki[0][0]==jugador_1 && triki[1][0]==jugador_1 && triki[2][0]==jugador_1) ||(triki[0][1]==jugador_1 && triki[1][1]==jugador_1 && triki[2][1]==jugador_1) ||(triki[0][2]==jugador_1 && triki[1][2]==jugador_1 && triki[2][2]==jugador_1) ||(triki[0][0]==jugador_1 && triki[1][1]==jugador_1 && triki[2][2]==jugador_1) ||(triki[2][0]==jugador_1 && triki[1][1]==jugador_1 && triki[0][2]==jugador_1))
         {   
             system("cls");
             printf("|1|2|3|4|5|6|7|8|9|\n\n|%i|%i|%i|\n|%i|%i|%i|\n|%i|%i|%i|\n",triki[0][0],triki[0][1],triki[0][2],triki[1][0],triki[1][1],triki[1][2],triki[2][0],triki[2][1],triki[2][2],"\n");
             printf("Ganador :  %i\n", jugador_1);
             break;     
         }
         if ((triki[0][0]==jugador_2 && triki[0][1]==jugador_2 && triki[0][2]==jugador_2) || (triki[1][0]==jugador_2 && triki[1][1]==jugador_2 && triki[1][2]==jugador_2) ||(triki[2][0]==jugador_2 && triki[2][1]==jugador_2 && triki[2][2]==jugador_2) ||(triki[0][0]==jugador_2 && triki[1][0]==jugador_2 && triki[2][0]==jugador_2) ||(triki[0][1]==jugador_2 && triki[1][1]==jugador_2 && triki[2][1]==jugador_2) ||(triki[0][2]==jugador_2 && triki[1][2]==jugador_2 && triki[2][2]==jugador_2) ||(triki[0][0]==jugador_2 && triki[1][1]==jugador_2 && triki[2][2]==jugador_2) ||(triki[2][0]==jugador_2 && triki[1][1]==jugador_2 && triki[0][2]==jugador_2))         
         {
             system("cls");
             printf("|1|2|3|4|5|6|7|8|9|\n\n|%i|%i|%i|\n|%i|%i|%i|\n|%i|%i|%i|\n",triki[0][0],triki[0][1],triki[0][2],triki[1][0],triki[1][1],triki[1][2],triki[2][0],triki[2][1],triki[2][2],"\n");
             printf("Ganador :  %i\n", jugador_2);
             break;     
         }
   }	
   system("PAUSE");	
   return 0;
}
