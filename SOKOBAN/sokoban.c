/*
  Name: MAPA DEL SOKOBAN
  Copyright: TODOS LOS DERECHOS RESERVADOS
  Authors:  Sergio Alexander Florez Galeano
            Johan David Rubio
            Johan manuel Alvarez
  Date: 14/04/10 22:57
  Description: Este programa imprime el mapa del sokoban leyendolo desde un
               archivo txt
*/


#include <allegro.h>
#include <stdio.h>


void imprimir_mapa(char nivel[20][20]);
void cargar_mapa(FILE *niveles,char nivel[20][20]);
void mover_muneco(char nivel[20][20]);
void tiempo();

int HORAS=0, MINUTOS=0, SEGUNDOS=0;
BITMAP *caja;
BITMAP *muneco;
BITMAP *pared;
BITMAP *X;
BITMAP *piso;
int pasos=0,pos_muneco[2],posx_final[4],posy_final[4];


int main()
{
    int temp;
    char nivel[20][20];
    FILE *mapas;
    mapas = fopen("mapas.txt","r");
    
    allegro_init();  //INICIALIZA LA LIBRERIA
    install_keyboard(); //INSTALA EL TECLADO
    install_timer();   //INSTALA LIBRERIA DE TIEMPO NECESARIA TAMBIEN PARA EL TECLADO
    install_mouse(); //INSTALA EL MOUSE
    
    
    set_color_depth(16);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0);
    set_pallete(desktop_pallete);
    clear_to_color(screen,makecol(0,0,0));
    
    muneco=load_bitmap("muneco.bmp", desktop_pallete);
    pared=load_bitmap("pared.bmp", desktop_pallete);
    caja=load_bitmap("caja.bmp", desktop_pallete);
    X=load_bitmap("X.bmp", desktop_pallete);
    piso=load_bitmap("piso.bmp", desktop_pallete);
    
    
    cargar_mapa(mapas,nivel);
    install_int(tiempo, 1000);
    imprimir_mapa(nivel);
    mover_muneco( nivel);
    
    destroy_bitmap(caja);
    destroy_bitmap(muneco);
    destroy_bitmap(pared);
    fclose(mapas);
    
    
    textprintf(screen,font,550,20,makecol(255,255,255),"%d, %d | %d, %d | %d, %d | %d, %d",posx_final[0],posy_final[0],posx_final[1],posy_final[1],posx_final[2],posy_final[2],posx_final[3],posy_final[3]);  
    readkey();
    allegro_exit(); //CIERRA LA LIBRERIA
    
    return 0;
}
END_OF_MAIN()

//ESTA FUNCION SE ENCARGA DE HACER MOVER EL MUÑECO
void mover_muneco(char nivel[20][20])
{ 
    int i,bandera;
    while(!key[KEY_ESC])
    {           
          readkey();
          //AKA ENTRA CUANDO SE QUIERE MOVER EL MUÑECO HACIA LA IZQUIERDA     
          if (key[KEY_LEFT])
          {                 
              if (!(nivel[(pos_muneco[0])][pos_muneco[1]-1] == '0'))
              {
                  if (nivel[(pos_muneco[0])][pos_muneco[1]-1] == '#' && (nivel[(pos_muneco[0])][pos_muneco[1]-2] == '_' || nivel[(pos_muneco[0])][pos_muneco[1]-2] == '@'))
                  {
                      nivel[(pos_muneco[0])][pos_muneco[1]-2]='#';                                        
                      nivel[(pos_muneco[0])][pos_muneco[1]-1]='Y';
                      nivel[(pos_muneco[0])][pos_muneco[1]]='_'; 
                  }
                  if (!(nivel[(pos_muneco[0])][pos_muneco[1]-1] == '#'))
                  {                                                                                      
                         nivel[(pos_muneco[0])][pos_muneco[1]-1]='Y';
                         nivel[(pos_muneco[0])][pos_muneco[1]]='_';
                         pos_muneco[1] -= 1;
                         pasos++;
                      
                  }
              }
              
              
          }
          //AKA ENTRA CUANDO SE QUIERE MOVER EL MUÑECO HACIA ABAJO
          if (key[KEY_DOWN])    
          {
              if (!(nivel[(pos_muneco[0])+1][pos_muneco[1]] == '0'))
              {
                  if (nivel[(pos_muneco[0])+1][pos_muneco[1]] == '#' && (nivel[(pos_muneco[0])+2][pos_muneco[1]] == '_' || nivel[(pos_muneco[0])+2][pos_muneco[1]] == '@'))
                  {
                      nivel[(pos_muneco[0])+2][pos_muneco[1]]='#';                                        
                      nivel[(pos_muneco[0])+1][pos_muneco[1]]='Y';
                      nivel[(pos_muneco[0])][pos_muneco[1]]='_';
                  }
                  if (!(nivel[(pos_muneco[0])+1][pos_muneco[1]] == '#'))
                  {                                                            
                     nivel[(pos_muneco[0])+1][pos_muneco[1]]='Y';
                     nivel[(pos_muneco[0])][pos_muneco[1]]='_';
                     pos_muneco[0] += 1;
                     pasos++;
                  }
              }
          }
          //AKA ENTRA CUANDO SE QUIERE MOVER EL MUÑECO HACIA ABAJO
          if (key[KEY_UP])    
          {
              if (!(nivel[(pos_muneco[0])-1][pos_muneco[1]] == '0'))
              {
                  if (nivel[(pos_muneco[0])-1][pos_muneco[1]] == '#' && (nivel[(pos_muneco[0])-2][pos_muneco[1]] == '_' || nivel[(pos_muneco[0])-2][pos_muneco[1]] == '@'))
                  {
                      nivel[(pos_muneco[0])-2][pos_muneco[1]]='#';                                        
                      nivel[(pos_muneco[0])-1][pos_muneco[1]]='Y';
                      nivel[(pos_muneco[0])][pos_muneco[1]]='_';
                  }
                  if (!(nivel[(pos_muneco[0])-1][pos_muneco[1]] == '#'))
                  {
                      nivel[(pos_muneco[0])-1][pos_muneco[1]]='Y';
                      nivel[(pos_muneco[0])][pos_muneco[1]]='_';
                      pos_muneco[0] -= 1;
                      pasos++;
                  }
              }
          }
          //AKA ENTRA CUANDO SE QUIERE MOVER EL MUÑECO HACIA LA IZQUIERDA
          if (key[KEY_RIGHT])
          {
              if (!(nivel[(pos_muneco[0])][pos_muneco[1]+1] == '0'))
              {   
                  if (nivel[(pos_muneco[0])][pos_muneco[1]+1] == '#' && (nivel[(pos_muneco[0])][pos_muneco[1]+2] == '_' || nivel[(pos_muneco[0])][pos_muneco[1]+2] == '@'))
                  {
                      nivel[(pos_muneco[0])][pos_muneco[1]+2]='#';                                        
                      nivel[(pos_muneco[0])][pos_muneco[1]+1]='Y';
                      nivel[(pos_muneco[0])][pos_muneco[1]]='_';
                  }    
                  if (!(nivel[(pos_muneco[0])][pos_muneco[1]+1] == '#'))
                  {            
                      nivel[(pos_muneco[0])][pos_muneco[1]+1]='Y';
                      nivel[(pos_muneco[0])][pos_muneco[1]]='_';
                      pos_muneco[1] += 1;
                      pasos++;
                  }
              }    
          }
          //ESTO ARREGLA EL PROBLEMA DE LOS OBJETIVOS(X)
          if (nivel[posx_final[0]][posy_final[0]] == '_')
          {
              nivel[posx_final[0]][posy_final[0]] = '@';
          }
          if (nivel[posx_final[1]][posy_final[1]] == '_')
          {
              nivel[posx_final[1]][posy_final[1]] = '@';
          }
          if (nivel[posx_final[2]][posy_final[2]] == '_')
          {
              nivel[posx_final[2]][posy_final[2]] = '@';
          }
          if (nivel[posx_final[3]][posy_final[3]] == '_')
          {
              nivel[posx_final[3]][posy_final[3]] = '@';
          } 
          
          //IMPRIME MAPA
          imprimir_mapa(nivel);
          
          if (nivel[posx_final[0]][posy_final[0]] == '#' && nivel[posx_final[1]][posy_final[1]] == '#' && nivel[posx_final[2]][posy_final[2]] == '#' && nivel[posx_final[3]][posy_final[3]] == '#')
          {
               clear_to_color(screen,makecol(0,0,0));
               textprintf(screen,font,550,550,makecol(255,255,255),"%s","FIN");                                    
               readkey();
               break;
          }
          
    }
}

//ESTA FUNCION CARGA EL MAPA LEIDO DESDE EL ARCHIVO EN UN MATRIZ, PARA PODER MANIPULARLO
void cargar_mapa(FILE *niveles,char nivel[20][20])
{  
   char temp,tecla;
   int i=0,j=0,z=0,bandera=0;
   textprintf(screen,font,100,20,makecol(255,255,255),"%s","POR FAVOR SELECCIONE EL NIVEL QUE DESEA JUGAR: ");
   tecla=readkey();
   textprintf(screen,font,490,20,makecol(255,255,255),"%c",tecla);
   readkey();
     
   while((temp=fgetc(niveles)) != EOF)
   {
       if (bandera == 2)
       {
            if(temp=='F')
               break;                              
            nivel[i][j]=temp;
            if(temp=='Y')
            {
               pos_muneco[0]=i;
               pos_muneco[1]=j;             
             }
             if(temp=='@')
             {
                posx_final[z]=i;
                posy_final[z]=j;
                z++;             
             } 
             j+=1;
             if(temp==';')
             {
                i+=1;
                j=0;     
             }
        }
        if(temp == tecla || bandera == 1)
           bandera+=1;            
   }
}


//ESTA FUNCION IMPRIME EN PANTALLA EL MAPA DEL SOKOBAN
void imprimir_mapa(char nivel[20][20])
{
 
   int x=0,y=0,i=0,j=0;
   
   while(i<20)
   {
        //AKA SE IMPRIMEN LAS IMAGENES SEGUN SE VAYA LEYENDO DEL ARCHIVO
        switch (nivel[i][j])
        {
            case ';':
                 j=-1;
                 i+=1;
                 y +=50;
                 x=-100;
                 break;
            case '0':
                 blit(pared, screen, 0, 0, x, y, 50, 50);
                 break;
            case 'Y':
                 blit(muneco, screen, 0, 0, x, y, 50, 50);
                 break;
            case '@':      
                 blit(X, screen, 0, 0, x, y, 50, 50);
                 break;
            case '#':      
                 blit(caja, screen, 0, 0, x, y, 50, 50);
                 break;
            case '_':      
                 blit(piso, screen, 0, 0, x, y, 50, 50);
                 break;
            
            
        }   
        x += 50;
        j+=1;  
   }
   textprintf(screen,font,550,20,makecol(255,255,255),"%s, %d","PASOS",pasos);
   
}


//ESTA FUNCION SE ENCARGA DEL MANEJO DEL TIEMPO
void tiempo()
{ 
     if (HORAS<24)
     {  
        
                   
       if (MINUTOS<60)
       { 
          if(SEGUNDOS<60)
          {
              SEGUNDOS++;
          }
          else
          {
             SEGUNDOS=0;
             MINUTOS++;
          }
       }
       else
       {
           MINUTOS=0;
           HORAS++;
       }
    }
                 
 
    rectfill(screen, 550, 55, 600, 65, makecol(0,0,0));
    textprintf(screen,font,550,55,makecol(255,255,255),"%d :%d: %d", HORAS,MINUTOS,SEGUNDOS);
}
END_OF_FUNCTION(tiempo);



/*
if (HORAS<24) //Mientas horas sea menor que 24
    {
          if(MINUTOS<60) //Mientras minutos sea menor que 60
          {
                if (SEGUNDOS<60) //Mientras segundos sea menor que 60
                {
                      SEGUNDOS++;
                      textprintf(screen,font,550,55,makecol(255,255,255),"%d %d %d",HORAS,MINUTOS,SEGUNDOS);
                }
                MINUTOS++;
                SEGUNDOS=0;
          }
          HORAS++;
          MINUTOS=0;
    }
*/
