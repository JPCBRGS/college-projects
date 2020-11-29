#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

using namespace std;

int main(int argc, char **argv){

   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_BITMAP  *image   = NULL;

   if(!al_init()) {
      cout <<"Failed to initialize allegro!" << endl;
      return 0;
   }

   if(!al_init_image_addon()) {
      cout <<"Failed to initialize al_init_image_addon!" << endl;
      return 0;
   }

   display = al_create_display(500,550);

   if(!display) {
      cout <<"Failed to initialize display!" << endl;
      return 0;
   }

   image = al_load_bitmap("map.bmp");		//Carrega imagem do arquivo map.bmp

   if(!image) {
      cout << "Failed to load image!" << endl;
      al_destroy_display(display);
      return 0;
   }

   al_draw_bitmap(image,0,0,0);				//Desenha a imagem na posicao (0,0) - canto superior esquerdo

   al_flip_display();
   al_rest(10);

   al_destroy_display(display);
   al_destroy_bitmap(image);

   return 0;
}
