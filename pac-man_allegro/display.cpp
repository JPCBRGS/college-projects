#include <iostream>
#include <allegro5/allegro.h>


using namespace std;

int main(int argc, char **argv){

   ALLEGRO_DISPLAY *display = NULL;

   if(!al_init()) {
      cout << "failed to initialize allegro!\n";
      return -1;
   }

   display = al_create_display(640, 480);		//Cria janela 640 x 480
   if(!display) {
      cout << "failed to create display!\n";
      return -1;
   }
   
   al_clear_to_color(al_map_rgb(200,0,0));		//limpa e colore com RGB(200,0,0)
   al_flip_display();							//troca a tela atual pela tela recem-desenhada
   al_rest(5.0);								//aguarda 5 segundos   
   al_destroy_display(display);					//"destroi" a janela e libera memoria

   return 0;
}




