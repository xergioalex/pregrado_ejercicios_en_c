/*
  Name: ANIMACION PELOTA
  Author: SERGIO ALEXANDER FLOREZ GALEANO
  Date: 06/04/10 10:43
  Description: ESTE PROGRAMA MUESTRA UNA ANIMACION DE UNA PELOTA RECORRIENDO LA PANTALLA
*/

#include <allegro.h>

int main() 
{
    double circulo_posicion=0;
	allegro_init();
	BITMAP* buffer;
	buffer = create_bitmap(800,600);
	
	install_keyboard();
	install_timer();
	install_mouse();
	set_color_depth(8);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0);
                
	while(!key[KEY_ESC])
    {
         clear_bitmap(buffer);
         circlefill(buffer, (int) circulo_posicion, SCREEN_H/2, 50, makecol(255,255,255));
         
         circulo_posicion += 0.5;
         if (circulo_posicion - 50 >= SCREEN_W)
             break;
         
         blit(buffer, screen,0,0,0,0,SCREEN_W,SCREEN_H);
    }               
    
	system("PAUSE");
	allegro_exit();
	
	return 0;
}
END_OF_MAIN()
