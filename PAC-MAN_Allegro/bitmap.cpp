#include<iostream>
#include <allegro5/allegro.h>

using namespace std;

const float FPS = 60;
const int SCREEN_W = 640;		//constantes para facilitar os calculos
const int SCREEN_H = 480;
const int BOUNCER_SIZE = 20;

int main(int argc, char **argv)
{
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_BITMAP *bouncer = NULL;
    float bouncer_x = SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0;
    float bouncer_y = SCREEN_H / 2.0 - BOUNCER_SIZE / 2.0;
    float bouncer_dx = -4.0, bouncer_dy = 4.0;
    bool redraw = true;

    if(!al_init())
    {
        return -1;
    }

    timer = al_create_timer(1.0 / FPS);
    if(!timer)
    {
        return -1;
    }

    display = al_create_display(SCREEN_W, SCREEN_H);
    if(!display)
    {
        al_destroy_timer(timer);
        return -1;
    }

    bouncer = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);		//cria um bitmap 20 x 20
    if(!bouncer)
    {
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }

    al_set_target_bitmap(bouncer);						//muda destino dos desenhos para o bitmap bouncer
    al_clear_to_color(al_map_rgb(255, 0, 255));			//limpa e colore de magenta
    al_set_target_bitmap(al_get_backbuffer(display));	//muda de volta o destino dos desenhos para o display

    event_queue = al_create_event_queue();
    if(!event_queue)
    {
        al_destroy_bitmap(bouncer);
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    al_clear_to_color(al_map_rgb(0,0,0));

    al_flip_display();

    al_start_timer(timer);

    while(1)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER)		//Atualiza posicao do bitmap a cada evento do temporizador
        {
            if(bouncer_x < 0 || bouncer_x > SCREEN_W - BOUNCER_SIZE)	//se chegou no limite do display, muda direcao
            {
                bouncer_dx = -bouncer_dx;
            }

            if(bouncer_y < 0 || bouncer_y > SCREEN_H - BOUNCER_SIZE)
            {
                bouncer_dy = -bouncer_dy;
            }

            bouncer_x += bouncer_dx;			//muda posicao
            bouncer_y += bouncer_dy;

            redraw = true;
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }

        if(redraw && al_is_event_queue_empty(event_queue))
        {
            redraw = false;

            al_clear_to_color(al_map_rgb(0,0,0));

            //cout << "x: " << bouncer_x << " y: " << bouncer_y << endl;
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
