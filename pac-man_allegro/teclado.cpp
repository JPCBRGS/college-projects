#include <iostream>
#include <allegro5/allegro.h>

const float FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_H = 480;
const int BOUNCER_SIZE = 32;

//enum cria constantes 0, 1, 2, 3... com nomes; serao usadas para acessar as posicoes do vetor de status
enum MYKEYS {
   KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

int main(int argc, char **argv)
{
   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_EVENT_QUEUE *event_queue = NULL;
   ALLEGRO_TIMER *timer = NULL;
   ALLEGRO_BITMAP *bouncer = NULL;
   float bouncer_x = SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0;		//posiciona no centro da tela
   float bouncer_y = SCREEN_H / 2.0 - BOUNCER_SIZE / 2.0;
   
   bool key[4] = { false, false, false, false };				//boolenos que indicam se pressionado pra cima, baixo, esq, dir
   
   bool redraw = true;
   bool doexit = false;

   if(!al_init()) {
      std::cout << "failed to initialize allegro!\n";
      return -1;
   }

   if(!al_install_keyboard()) {									//inicializa sistema de eventos do teclado
      std::cout << "failed to initialize the keyboard!\n";
      return -1;
   }

   timer = al_create_timer(1.0 / FPS);
   if(!timer) {
      std::cout << "failed to create timer!\n";
      return -1;
   }

   display = al_create_display(SCREEN_W, SCREEN_H);
   if(!display) {
      std::cout << "failed to create display!\n";
      al_destroy_timer(timer);
      return -1;
   }

   bouncer = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);
   if(!bouncer) {
      std::cout << "failed to create bouncer bitmap!\n";
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }

   al_set_target_bitmap(bouncer);
   al_clear_to_color(al_map_rgb(0, 255, 255));
   al_set_target_bitmap(al_get_backbuffer(display));

   event_queue = al_create_event_queue();
   if(!event_queue) {
      std::cout << "failed to create event_queue!\n";
      al_destroy_bitmap(bouncer);
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }	

   al_register_event_source(event_queue, al_get_display_event_source(display));
   al_register_event_source(event_queue, al_get_timer_event_source(timer));
   al_register_event_source(event_queue, al_get_keyboard_event_source());			//registra leitor de evento de teclado

   al_clear_to_color(al_map_rgb(0,0,0));
   al_flip_display();
   al_start_timer(timer);

   while(!doexit)		//booleano que vai indicar fim
   {
      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);

      if(ev.type == ALLEGRO_EVENT_TIMER) {		//a cada evento do temporizador, atualiza posicao da figura, dependo das teclas pressionadas
         if(key[KEY_UP] && bouncer_y >= 0) {
            bouncer_y -= 4.0;
         }

         if(key[KEY_DOWN] && bouncer_y <= SCREEN_H - BOUNCER_SIZE) {
            bouncer_y += 4.0;
         }

         if(key[KEY_LEFT] && bouncer_x >= 0) {
            bouncer_x -= 4.0;
         }

         if(key[KEY_RIGHT] && bouncer_x <= SCREEN_W - BOUNCER_SIZE) {
            bouncer_x += 4.0;
         }

         redraw = true;
      }
      else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         break;
      }
      else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {		//evento gerado quando uma tecla e' pressionada
         switch(ev.keyboard.keycode) {					//verifica qual tecla foi
            case ALLEGRO_KEY_UP:						//  e ativa booleano correspondente
               key[KEY_UP] = true;
               break;

            case ALLEGRO_KEY_DOWN:
               key[KEY_DOWN] = true;
               break;

            case ALLEGRO_KEY_LEFT:
               key[KEY_LEFT] = true;
               break;

            case ALLEGRO_KEY_RIGHT:
               key[KEY_RIGHT] = true;
               break;
         }
      }
      else if(ev.type == ALLEGRO_EVENT_KEY_UP) {		//evento gerado quando uma tecla e' liberada
         switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
               key[KEY_UP] = false;						//desativa booleano correspondente
               break;

            case ALLEGRO_KEY_DOWN:
               key[KEY_DOWN] = false;
               break;

            case ALLEGRO_KEY_LEFT:
               key[KEY_LEFT] = false;
               break;

            case ALLEGRO_KEY_RIGHT:
               key[KEY_RIGHT] = false;
               break;

            case ALLEGRO_KEY_ESCAPE:					//tecla ESC, marca para sair do loop
               doexit = true;
               break;
         }
      }

      if(redraw && al_is_event_queue_empty(event_queue)) {
         redraw = false;

         al_clear_to_color(al_map_rgb(0,0,0));

         al_draw_bitmap(bouncer, bouncer_x, bouncer_y, 0);

         al_flip_display();
      }
   }

   al_destroy_bitmap(bouncer);
   al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);

   return 0;
}
