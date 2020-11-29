#include <iostream>
#include <allegro5/allegro.h>

using namespace std;

int main(int argc, char **argv){

   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_EVENT_QUEUE *event_queue = NULL;

   if(!al_init()) {
      cout << "failed to initialize allegro!\n";
      return -1;
   }

   display = al_create_display(640, 480);
   if(!display) {
      cout << "failed to create display!\n";
      return -1;
   }

   event_queue = al_create_event_queue();
   if(!event_queue) {
      cout << "failed to create event_queue!\n";
      al_destroy_display(display);
      return -1;
   }

   al_register_event_source(event_queue, al_get_display_event_source(display));		//eventos do display vao para a fila, para serem tratados
   al_clear_to_color(al_map_rgb(200,0,0));
   al_flip_display();

   while(1)					//loop "eterno"
   {
      ALLEGRO_EVENT ev;
      ALLEGRO_TIMEOUT timeout;
	  
      al_init_timeout(&timeout, 0.6);
      bool get_event = al_wait_for_event_until(event_queue, &ev, &timeout);		//Aguarda 0.6 segundos ou algum evento

      if(get_event && ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {			//Se clicou no X de fechar a janela sai do loop
         break;
      }

      al_clear_to_color(al_map_rgb(0,0,0));		//Colore de preto
      al_flip_display();
   }

   al_destroy_display(display);
   al_destroy_event_queue(event_queue);

   return 0;
}
