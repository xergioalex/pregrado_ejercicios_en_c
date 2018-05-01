/*
  Name: MANEJADOR DE PROYECTOS
  Copyright: TODOS LOS DERECHOS RESERVADOS
  Author:  SERGIO ALEXANDER FLOREZ GALEANO
  
  Date: 31/05/10 20:14
  Description: 
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <allegro.h>

//-----------------------------------------------------------------------------------------------------------
//PROTOTIPO: DECLARACION DE FUNCIONES
void init ();
void funcion_principal();

void escritura_en_pantalla();
int escribir_numeros(int numero);
char escribir_palabras();

void interfase(int estado);
void estado_interfase_click();
void estado_imagen(char* imagen);
void textos_interfase();

void agregar_a_archivo_ordenadamente();
void pedir_datos_contacto();
void listar_contactos();
void eliminar_registro();
void copypaste_eliminar_registro_final();
void modificar_contacto();
long filesize();

 /*Se encarga de manejar todas las imágenes contenidas en el programa*/
void guardar_datos (); 

//-----------------------------------------------------------------------------------------------------------
//DEFINICION DE ESTRUCTURA Y CREACION DE VARIABLES GLOBALES
typedef struct
{
     long int cedula;
     char nombre[30];
     long int telefono;
} CONTACTO;



CONTACTO new_contac={0,"",0};//Esta es la variable que se encargara de almacenar los nuevos contactos
CONTACTO modificar_contac={0,"",0};
CONTACTO cont_temporal={0,"",0};
BITMAP *buffer; //Bitmap usado, para el manejo de un sistema doble buffer, en relacion con la pantalla
BITMAP *mensaje_cerrar; //Por convención se define la imágen mensaje_cerrar
    	
int estado=0;
int cursor_esc_x,cursor_esc_y,cursor_ced=0,cursor_nom=0,cursor_telef=0,cursor_ced_m=0,cursor_ced_temp=0,cursor_nom_temp=0,cursor_telef_temp=0;
int cont_tamano=0,  boton=0, buscar=0, salir=0; //Variables incluidas dentro del main   
int bandera=0,cambio=0;
//-----------------------------------------------------------------------------------------------------------
//INICIO DEL PROGRAMA
int main()
{
    init(); //Inicializo la libreria allegro y todas las imagenes pertinentes
    funcion_principal();
    return 0;
}
END_OF_MAIN(); //Receta de cocina, para el uso de allegro en Linux.





//FUNCION PRINCIPAL
void funcion_principal()
{
     int i;
     do{
        interfase(estado);
        textos_interfase();
        
        
        //Aca entra cuando se da un Click
        if (mouse_b & 1) 
        {                
             estado_interfase_click(); 
        }
        if (keypressed())
        {
             //Condicionales para cuando se presione cualquier tecla, inicia acá
			escritura_en_pantalla();
        }

        
        textprintf_ex(buffer, font, 20, 15, makecol(255, 255, 255), -1, "X:%d, Y:%d Estado:%d", mouse_x, mouse_y,estado);
        blit(buffer, screen, 0, 0, 0, 0, buffer->w, buffer->h);
        
     }while (!key[KEY_ESC]);
}

//-----------------------------------------------------------------------------------------------------------
//SON LOS TEXTOS QUE SE IMPRIMEN CADA QUE SE ESCRIBE
void textos_interfase()
{
     switch(estado)
     {
         case 2:
             listar_contactos();          
             break;
         case 3:
             if (cursor_ced>0)
                 textprintf_ex(buffer, font, 238, 129, makecol(0, 0, 0), -1, "%d", new_contac.cedula);
             if (cursor_telef>0)
                 textprintf_ex(buffer, font, 238, 229, makecol(0, 0, 0), -1, "%d", new_contac.telefono);
             textprintf_ex(buffer, font, 240, 179, makecol(0, 0, 0), -1, "%s", new_contac.nombre);
             break;
         case 4:
             if(cursor_ced_m>0)
                 textprintf_ex(buffer, font, 238, 160, makecol(0, 0, 0), -1, "%d", modificar_contac.cedula);
             break;
         case 5:
             textprintf_ex(buffer, font, 250, 250, makecol(0, 0, 0), -1, "%i %s %i", modificar_contac.cedula,modificar_contac.nombre,modificar_contac.telefono);
             if(cursor_ced_temp>0)
                textprintf_ex(buffer, font, 240, 325, makecol(0, 0, 0), -1, "%i", cont_temporal.cedula);
             if(cursor_nom_temp>0)
                textprintf_ex(buffer, font, 240, 375, makecol(0, 0, 0), -1, "%s", cont_temporal.nombre);
             if(cursor_telef_temp>0)
                textprintf_ex(buffer, font, 240, 425, makecol(0, 0, 0), -1, "%i", cont_temporal.telefono);
             break;
          case 6:
             textprintf_ex(buffer, font, 240, 200, makecol(0, 0, 0), -1, "%i", modificar_contac.cedula);
           
     }
}

//-----------------------------------------------------------------------------------------------------------
//ESTABLECER ESTADO DE LA INTERFASE CUANDO SE PRESIONA CLICK EN UN BOTON, O CUANDO SE PRESIONA SOBRE 
void estado_interfase_click()
{
      if ((mouse_x>345 && mouse_y>478) && (mouse_x<446 && mouse_y<501)||(mouse_x>10 && mouse_y>166) && (mouse_x<200 && mouse_y<216))
      {
          estado=1;
          interfase(estado); 
      }
      if (estado==1)
      {
          if ((mouse_x>321 && mouse_y>77) && (mouse_x<453 && mouse_y<211))//listar
          {
             estado=2;
             interfase(estado); 
          }
          if ((mouse_x>581 && mouse_y>88) && (mouse_x<706 && mouse_y<198))//agregar
          {
             cursor_esc_x=238;           
             cursor_esc_y=129;
             estado=3;
             interfase(estado); 
          }
          if ((mouse_x>333 && mouse_y>279) && (mouse_x<461 && mouse_y<406))//modificar
          {
             cursor_esc_x=240;           
             cursor_esc_y=160;
             estado=4;
             interfase(estado); 
          }
          if ((mouse_x>575 && mouse_y>270) && (mouse_x<709 && mouse_y<409))//eliminar
          {
             cursor_esc_x=240;           
             cursor_esc_y=160;
             estado=6;
             interfase(estado); 
          }
      }
      if (estado==3)
      {
          if ((mouse_x>240 && mouse_y>222) && (mouse_x<350 && mouse_y<450))
          {
             agregar_a_archivo_ordenadamente(new_contac);            
             allegro_message("Guardado Exitosamente"); 
          }
      }
      if (estado==4)
      {
          if ((mouse_x>365 && mouse_y>220) && (mouse_x<500 && mouse_y<250))  
              modificar_contacto(modificar_contac);            
      }
      if (estado==5)
      {
          if ((mouse_x>365 && mouse_y>450) && (mouse_x<470 && mouse_y<480))
          {
             allegro_message("modificado Exitosamente");
             agregar_a_archivo_ordenadamente(cont_temporal);
             eliminar_registro(modificar_contac);
              
          }
      }
      if (estado==6)
      {
          if ((mouse_x>325 && mouse_y>275) && (mouse_x<420 && mouse_y<310))
          {
             eliminar_registro(modificar_contac);
          }
      }
}

//allegro_message("SE PRESIONO ENTER");

//-----------------------------------------------------------------------------------------------------------
//LOS CUADROS DE ESCRITURA, PARA ACOMODAR EL POSICIONAMIENTO DEL CURSOR DE ESCRITURA
void escritura_en_pantalla()
{
     int i,tecla=0;
     if (estado==3) //Si se encuentra dentro del botón venta
     {
         if (cursor_ced<11 && cursor_esc_y==129) 
    	 {       
                 if(key[KEY_BACKSPACE])
                {
                     new_contac.cedula=new_contac.cedula/10;//Insertar consonantes y vocales dentro de nombre en la estructura
   	                 cursor_ced--;
   	                 cont_tamano--;
                }
                if(key[KEY_ENTER] && tecla==0)
               	{
                    cursor_esc_y+=50;
                    tecla=1;
                }          
                if(cursor_ced<10)
                {
                    new_contac.cedula=escribir_numeros(new_contac.cedula);  //Inserta números en telefono dentro de la estructura
                    if (bandera==1)
                    {
                       cursor_ced++;  
                       bandera=0;
                    }
                }  	
    	 }
                                      
         if (cursor_nom<31 && cursor_esc_y==179) 
    	 {
                if(key[KEY_BACKSPACE] || cursor_nom==30)
                {
                     new_contac.nombre[cursor_nom-1]=0;//Insertar consonantes y vocales dentro de nombre en la estructura
   	                 cursor_nom--;
                }
                if(key[KEY_SPACE])
                {
                     new_contac.nombre[cursor_nom]=32;//Insertar consonantes y vocales dentro de nombre en la estructura
   	                 cursor_nom++;
                     tecla=1; 
                }
                if(key[KEY_ENTER] &&  tecla==0 )
               	{
                    cursor_esc_y+=50;
                }            
                 //Insertar consonantes y vocales dentro de nombre en la estructura
   	            if(cursor_nom<31)
                {
                    new_contac.nombre[cursor_nom]=escribir_palabras();  //Inserta números en telefono dentro de la estructura
                    if (bandera==1)
                    {
                       cursor_nom++;  
                       bandera=0;
                    }
                } 
    	 }
    	 if (cursor_telef<11 && cursor_esc_y==229) 
    	 {       
                
                if(key[KEY_BACKSPACE])
                {
                     new_contac.telefono=new_contac.telefono/10;//Insertar consonantes y vocales dentro de nombre en la estructura
   	                 cursor_telef--;    
                }
                if(cursor_telef<10)
                {
					 new_contac.telefono=escribir_numeros(new_contac.telefono);
                     if (bandera==1)
                     { 
                         cursor_telef++;
                         bandera=0;
                    }
                }
            	
    	 }	 
      }
      if (estado==4) //Si se encuentra dentro del botón venta
     {
         
         if (cursor_ced_m<11 && cursor_esc_y==160) 
    	 {     
                
                if(key[KEY_BACKSPACE])
                {
                     modificar_contac.cedula=modificar_contac.cedula/10;//Insertar consonantes y vocales dentro de nombre en la estructura
   	                 cursor_ced_m--;
                }   
                if(cursor_ced_m<10)
                {
                    
                    modificar_contac.cedula=escribir_numeros(modificar_contac.cedula);  //Inserta números en telefono dentro de la estructura
                    if (bandera==1)
                    {
                       cursor_ced_m++;  
                       bandera=0;
                    }
                }  	
    	 }
      }
      if (estado==5) 
      {
          if (cursor_ced_temp<11 && cursor_esc_y==325) 
    	 {       
                 if(key[KEY_BACKSPACE])
                {
                     cont_temporal.cedula=cont_temporal.cedula/10;
   	                 cursor_ced_temp--;
                }
                if(key[KEY_ENTER] && tecla==0)
               	{
                    cursor_esc_y+=50;
                    tecla=1;
                }          
                if(cursor_ced_temp<10)
                {
                    cont_temporal.cedula=escribir_numeros(cont_temporal.cedula);  
                    if (bandera==1)
                    {
                       cursor_ced_temp++;  
                       bandera=0;
                    }
                }  	
    	 }
                                      
         if (cursor_nom_temp<31 && cursor_esc_y==375) 
    	 {
                if(key[KEY_BACKSPACE] || cursor_nom==30)
                {
                     cont_temporal.nombre[cursor_nom_temp-1]=0;//Insertar consonantes y vocales dentro de nombre en la estructura
   	                 cursor_nom_temp--;
                }
                if(key[KEY_SPACE])
                {
                     cont_temporal.nombre[cursor_nom]=32;//Insertar consonantes y vocales dentro de nombre en la estructura
   	                 cursor_nom_temp++;
                     tecla=1; 
                }
                if(key[KEY_ENTER] &&  tecla==0 )
               	{
                    cursor_esc_y+=50;
                }            
                 //Insertar consonantes y vocales dentro de nombre en la estructura
   	            if(cursor_nom<31)
                {
                    cont_temporal.nombre[cursor_nom_temp]=escribir_palabras();  //Inserta números en telefono dentro de la estructura
                    if (bandera==1)
                    {
                       cursor_nom_temp++;  
                       bandera=0;
                    }
                } 
    	 }
    	 if (cursor_telef<11 && cursor_esc_y==425) 
    	 {       
                
                if(key[KEY_BACKSPACE])
                {
                     cont_temporal.telefono=cont_temporal.telefono/10;//Insertar consonantes y vocales dentro de nombre en la estructura
   	                 cursor_telef_temp--;    
                }
                if(cursor_telef<10)
                {
					 cont_temporal.telefono=escribir_numeros(cont_temporal.telefono);
                     if (bandera==1)
                     { 
                         cursor_telef_temp++;
                         bandera=0;
                    }
                }
            	
    	 }
      }
      if (estado==6) //Si se encuentra dentro del botón venta
      {
         
         if (cursor_ced_m<11 && cursor_esc_y==160) 
    	 {     
                
                if(key[KEY_BACKSPACE])
                {
                     modificar_contac.cedula=modificar_contac.cedula/10;//Insertar consonantes y vocales dentro de nombre en la estructura
   	                 cursor_ced_m--;
                }   
                if(cursor_ced_m<10)
                {
                    
                    modificar_contac.cedula=escribir_numeros(modificar_contac.cedula);  //Inserta números en telefono dentro de la estructura
                    if (bandera==1)
                    {
                       cursor_ced_m++;  
                       bandera=0;
                    }
                }  	
    	 }
      }
      clear_keybuf();
              
}

//------------------------------------------------------------------------------------------------------------
//ESTA FUNCION SE ENCARGA RECIBIR LOS NUMEROS QUE SE INGRESAN POR TECLADO E INGRESARLOS EN LA ESTRUCTURA
int escribir_numeros(int numero)
{
     int i;
     {
        for (i=37; i<=46; i++) 
        {
            if (key[i])
            {
                //allegro_message("SE PRESIONO ENTER");        
                numero=numero*10+(i-37); //Inserta números en telefono dentro de la estructura 
                bandera=1;         
            }
        }
     }
     
     return numero;
}

//------------------------------------------------------------------------------------------------------------
//ESTA FUNCION SE ENCARGA RECIBIR LOS caracteres QUE SE INGRESAN POR TECLADO E INGRESARLOS EN LA ESTRUCTURA
char escribir_palabras()
{
    int i;
    char caracter; 
    for (i=0; i<=26; i++)
    {
        if (key[i])
        {
            caracter=i+96; //Insertar consonantes y vocales dentro de nombre en la estructura
            bandera=1;
        }
    }
    return caracter; 
}

//allegro_message("SE PRESIONO ENTER");
//-----------------------------------------------------------------------------------------------------------
//ESTA FUNCION SE ENCARGA DE MANEJAR EL ESTADO DE LAS IMAGENES EN PANTALLA, CADA QUE SE PRESIONA UN BOTON DIFERENTE
void interfase (int estado)
{
    if(!(estado == 3))
    {
        new_contac.cedula=0;
        strcpy(new_contac.nombre,"                     ");
        new_contac.telefono=0;
        cursor_ced=0;
        cursor_nom=0;
        cursor_telef=0;
        
    }
    if(!(estado == 4) && !(estado == 5) && !(estado == 6))
    {
        modificar_contac.cedula=0;
        cursor_ced_m=0;
    }
    switch (estado)
    {
        case 0:{
            estado_imagen("img/inicio.bmp");
            break;
        }
        case 1:{
            estado_imagen("img/personal.bmp");
            break;
        }
        case 2:{
            estado_imagen("img/listar.bmp");
            break;
        }
        case 3:{
            estado_imagen("img/agregar.bmp");
            break;
        }
        case 4:{
            estado_imagen("img/modificar.bmp");
            break;
        }
        case 5:{
            estado_imagen("img/modificar_1.bmp");
            break;
        }
        case 6:{
            estado_imagen("img/eliminar.bmp");
            break;
        }
    }
}

void estado_imagen(char* imagen)
{
     BITMAP *inicio; //Por convención se define la imágen inicio
     inicio=load_bitmap(imagen, default_palette); //Se carga la imágen inicio
     draw_sprite(buffer, inicio, 0, 0); //Dibuja la imágen inicio dentro de buffer
     destroy_bitmap(inicio);    
}


//-----------------------------------------------------------------------------------------------------------
//ESTA FUNCION DEJA PREPARADO E INSTALADOS TODOS LOS PERIFERICOS Y LAS FUNCIONES DE ALLEGRO
void init()
{
    allegro_init(); //Inicializa la libreria
    install_mouse(); //Instala las funciones del mouse
    install_keyboard(); //Instala las funciones del teclado
    set_color_depth(32); //Especifica la profundidad de color de los graficos, entre mas algo, mas bonito pero mas lento
    set_gfx_mode (GFX_AUTODETECT_WINDOWED,800, 600, 0, 0); //Inicializa el modo gráfico estableciendo la pantalla o lienzo de trabajo
    show_mouse (screen); //Permite vizualizar el mouse dentro de la ventana
    buffer=create_bitmap (SCREEN_W, SCREEN_H); //Crea buffer con el tamaño de ventana
    set_window_title("Project Manajer v.1");
    mensaje_cerrar=load_bitmap("img/mensaje_cerrar.bmp", default_palette); //Carga la imágen mensaje_cerrar
}


//-----------------------------------------------------------------------------------------------------------
//ESTA FUNCION AGREGA UN NUEVO CONTACTO EN EL ARCHIVO DE MANERA ORDENADA
void agregar_a_archivo_ordenadamente(CONTACTO contacto)
{
    FILE *agenda;
    CONTACTO tmp;
    int i=0;
    agenda=fopen("agenda.txt","r+b");
    if (filesize()==0)
    {
       i++;
    }
    else
    {
       do //AKA BUSCO EL FIN DE ARCHIVO PARA PODER AGREGAR EL NUEVO CONTACTO JUSTO AL FINAL
       {
          fseek(agenda,sizeof(CONTACTO)*i,0);
          fread(&tmp,sizeof(CONTACTO),1,agenda);
          
          if (contacto.cedula == tmp.cedula)
          {
              fseek(agenda,sizeof(CONTACTO)*i,0);
              fwrite(&contacto,sizeof(CONTACTO),1,agenda);
              i++;
              break;
          }
          if (contacto.cedula < tmp.cedula)
          {
              fseek(agenda,sizeof(CONTACTO)*i,0);
              fwrite(&contacto,sizeof(CONTACTO),1,agenda);
              contacto=tmp;
          }
          i++;
       }while(!feof(agenda));
    }
    fseek(agenda,sizeof(CONTACTO)*(i-1),0);
    fwrite(&contacto,sizeof(CONTACTO),1,agenda);                  
    fclose(agenda);
}



//-----------------------------------------------------------------------------------------------------------
//ESTA FUNCION PIDE UN NUMERO DE CEDULA PARA MODIFICAR UN REGISTRO DETERMINADO
void modificar_contacto(CONTACTO contacto)
{
    FILE *agenda;
    CONTACTO temporal;
    int i=0;
    agenda=fopen("agenda.txt","r+b");
    do //AKA BUSCO EL FIN DE ARCHIVO PARA PODER AGREGAR EL NUEVO CONTACTO JUSTO AL FINAL
    {
          fseek(agenda,sizeof(CONTACTO)*i,0);
          fread(&temporal,sizeof(CONTACTO),1,agenda);
          fseek(agenda,sizeof(CONTACTO)*i,0);
          fread(&temporal,sizeof(CONTACTO),1,agenda);
          if (contacto.cedula == temporal.cedula)
          {
            
              estado=5;
              modificar_contac.cedula=temporal.cedula;
              strcpy(modificar_contac.nombre,temporal.nombre);
              modificar_contac.telefono=temporal.telefono;
              cursor_esc_x=240;
              cursor_esc_y=325;
              break;
          }
          if(feof(agenda))
          {
              allegro_message("-.-' Ese registro no existe");
              
          }
          i++;
    }while(!feof(agenda));
    fclose(agenda);
}

//-----------------------------------------------------------------------------------------------------------
//ESTA FUNCION RECORRE TODO EL ARCHIVO Y IMPRIME TODOS LOS CONTACTOS EXISTENTES
void listar_contactos()
{
    
    FILE *agenda;
    CONTACTO tmp;
    int i=0,y=110;
    agenda=fopen("agenda.txt","r+b");
    
    while(!feof(agenda))//AKA LEO CADA ESTRUCTURA TIPO CONTACTO DEL ARCHIVO, Y LO IMPRIMO EN PANTALLA
    {
          fseek(agenda,sizeof(CONTACTO)*i,0);
          fread(&tmp,sizeof(CONTACTO),1,agenda);
          if(!feof(agenda))
          {
          
             textprintf_ex(buffer, font, 230, y, makecol(0, 0, 0), -1, "%i %s %i", tmp.cedula,tmp.nombre,tmp.telefono);
             y+=10;
          }   
          i++;    
    }
    fclose(agenda);
}

//-----------------------------------------------------------------------------------------------------------
//ESTA  FUNCION PIDE UN NUMERO DE CEDULA Y ELIMINA EL REGISTRO QUE CONTIENE ESA CEDULA
void eliminar_registro(CONTACTO e_contacto){
     FILE *agenda;
     CONTACTO temp;
     int i=0;
     agenda=fopen("agenda.txt","r+b");
     do
     {
          fseek(agenda,sizeof(CONTACTO)*i,0);
          fread(&temp,sizeof(CONTACTO),1,agenda);
          i++;
     }while(!(e_contacto.cedula == temp.cedula) && !feof(agenda));
     if(feof(agenda))
     {
          allegro_message("-.-' Ese registro no existe");
     }
     else
     {
          while(!feof(agenda))
          {
                fseek(agenda,sizeof(CONTACTO)*i,0);
                fread(&temp,sizeof(CONTACTO),1,agenda);
                fseek(agenda,sizeof(CONTACTO)*(i-1),0);
                fwrite(&temp,sizeof(CONTACTO),1,agenda);
                fseek(agenda,sizeof(CONTACTO)*i,0);
                fread(&temp,sizeof(CONTACTO),1,agenda);
                i++;
           }
            fclose(agenda);
            copypaste_eliminar_registro_final();
            allegro_message("Contacto eliminado con exito");
     }
}

//-----------------------------------------------------------------------------------------------------------
//ESTA FUNCION SE ENCARGA DE ELIMINAR EL ULTIMO REGISTRO DEL ARCHIVO, HACIENDO
//UNA COPIA SIN INCLUIR ESTE, LUEGO ELIMINA EL ARCHIVO ORIGINAL, Y A LA COPIA
//TEMPORAL LA RENOMBRA CON EL NOMBRE DEL ARCHIVO ORIGINAL.
void copypaste_eliminar_registro_final()
{
     FILE *agenda,*arch_temp;
     CONTACTO temporal;
     int i=0;
     agenda=fopen("agenda.txt","r+b");
     
     arch_temp=fopen("temporal.txt","w+");
     while(!feof(agenda))
     {
          fseek(agenda,sizeof(CONTACTO)*i,0);
          fread(&temporal,sizeof(CONTACTO),1,agenda);
          fseek(arch_temp,sizeof(CONTACTO)*i,0);
          fwrite(&temporal,sizeof(CONTACTO),1,arch_temp);
          i++;
          fseek(agenda,sizeof(CONTACTO)*(i+1),0);
          fread(&temporal,sizeof(CONTACTO),1,agenda);
     }
     fclose(arch_temp);
     fclose(agenda);
     remove ("agenda.txt");
     rename ("temporal.txt","agenda.txt");
    
}





//------------------------------------------------------------------------------------------------------------
//Esta funcion nos encuentra el tamaño del archivo
long filesize(){    
       long i=0;
       FILE *archivo;
       archivo=fopen("agenda.txt","r");
       for(i=0;fgetc(archivo)!=EOF;i++); //Recorre el archivo incrementando i por cada caracter
       fclose(archivo);
       
       return i;     
}

