#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


using namespace std;

const float FPS = 5;
const int SCREEN_W = 500;
const int SCREEN_H = 550;

struct Info{
    double dist;
    int x;
    int y;
    char seta;
};

double distancia(int x1,int y1,int x2,int y2){

    return abs(sqrt((x2 - x1)*(x2 - x1) +  (y2 - y1)*(y2 - y1)));

}


bool inicio = true;
bool acabar = false;

enum MYKEYS
{
    KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

//matriz definindo mapa do jogo: 1 representa paredes, 0 representa corredor
char MAPA[26][26] =
{
    "1111111111111111111111111",
    "1222222222222222222222221",
    "1211211121211121211121121",
    "1211211122222222211121121",
    "1222222221121211222222221",
    "1112121121121211211212111",
    "1222122222222222222212221",
    "1212112121121211212112121",
    "1212222121121211212222121",
    "1211112121121211212111121",
    "3211112122222222212111121",
    "1222112221110111222112221",
    "1212112121000001212112121",
    "1222222221000001222222223",
    "1211111121111111211111121",
    "1211122222220222222211121",
    "1222221111112111111222221",
    "1211121112222222111211121",
    "1211121112112112111211121",
    "1222222222112112222222221",
    "1211121112112112111211121",
    "1222221112112112111222221",
    "1211122222222222222211121",
    "1222221111111111111222221",
    "1111111111111111111111111",
};
//auxiliar para controlar pontos;
int r = 0;
int s = 0;
int contpontos = 0;

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_BITMAP *mapa   = NULL;
ALLEGRO_BITMAP *deathmap = NULL;
ALLEGRO_BITMAP *icon = NULL;
ALLEGRO_BITMAP *pontos = NULL; //287 no total;
ALLEGRO_BITMAP *pacman   = NULL;
ALLEGRO_BITMAP *pacup   = NULL;
ALLEGRO_BITMAP *pacleft   = NULL;
ALLEGRO_BITMAP *pacdown   = NULL;
ALLEGRO_BITMAP *pacright   = NULL;
ALLEGRO_BITMAP *fechado = NULL;
ALLEGRO_BITMAP *aux = NULL;
ALLEGRO_BITMAP *blinky = NULL;
ALLEGRO_BITMAP *clyde = NULL;
ALLEGRO_BITMAP *inky = NULL;
ALLEGRO_BITMAP *pinky = NULL;
ALLEGRO_FONT *fonte = NULL;
ALLEGRO_SAMPLE *sample = NULL;
ALLEGRO_SAMPLE *win = NULL;
ALLEGRO_SAMPLE *death = NULL;
ALLEGRO_SAMPLE *beggining = NULL;
ALLEGRO_SAMPLE *teleport = NULL;

int i = 15, j = 12; //posição inicial do Pacman na matriz;
int vX= 12, vY = 10; //posição inicial do Blinky;
int lX = 13, lY = 10; //posição inicial do Clyde;
int rX = 13, rY = 14; //posição inicial do Pinky;
int aX = 12, aY = 14; //posição inicial do Inky;
int q = 20; //tamanho de cada célula no mapa;

//posições iniciais do pac man;

int posy = i*q;
int posx = j*q;

//posições iniciais do Blinky;
int vermelhoX = vY * q;
int vermelhoY = vX * q;

//posições iniciais do Clyde;
int laranjaX = lY * q;
int laranjaY = lX * q;

//posições iniciais do Pinky;
int rosaX = rY * q;
int rosaY = rX * q;

//posições iniciais do Inky;
int azulX = aY * q;
int azulY = aX * q;

//baixo = 0; esquerda = 1; cima = 2; direita = 3;
int lastmouth, sim = 0;
int total = 287;

int randomIndex = -1;
int lastLaranjaPos = -1;
int lastAzulPos = -1;
int lastRosaPos = -1;
int lastRandomPos = -1;

bool key[4] = { false, false, false, false };
bool redraw = true;
bool sair = false;
bool acabou = false;
bool gameover = false;

int ulx=vX; //Ultimas coordenadas do Blinky, usado pra morte do PacMan e para a movimentacao dele mesmo
int uly=vY;

int lastlaranjax=lX , lastlaranjay=lY, lastazulx=aX, lastazuly=aY, lastrosax=rX, lastrosay=rY;
int lastpacmanx = i, lastpacmany = j, lastvermelhox=vX, lastvermelhoy=vY;

void BM(char M[][26],int &x, int &y, int &bX, int &bY) {

                

				if((x==8) && (y==11) && (j<=y)) { 
					ulx=vX;
					uly=vY;
					y--;
					vermelhoX = y*q;
					return;
				}else if((x==8) && (y==11) && (j>=y)) {
					ulx=vX;
					uly=vY;
					y++;
					vermelhoX = y*q;
					return;
				}
				Info vai[4]; //calculo das distancias das 4 posicoes ao redor de blinky
				vai[0].dist= distancia(x+1,y,i,j); vai[0].x=x+1; vai[0].y=y;vai[0].seta='S';
				vai[1].dist= distancia(x,y-1,i,j); vai[1].x=x; vai[1].y=y-1;vai[1].seta='A';
				vai[2].dist= distancia(x-1,y,i,j); vai[2].x=x-1; vai[2].y=y;vai[2].seta='W';
				vai[3].dist= distancia(x,y+1,i,j); vai[3].x=x; vai[3].y=y+1;vai[3].seta='D';

				double less=1000;
				int which=1000;
				for(int c=0;c<4;c++){  //vendo qual distancia � menor e ao mesmo tempo acessivel
						if((vai[c].dist<less) && (M[vai[c].x][vai[c].y]!='1')){
							if((vai[c].x!=ulx) || (vai[c].y!=uly)){
							  less=vai[c].dist;
							  which=c;
							}
						}
				}
				ulx=vX;
				uly=vY;


				if(which==0) {   //indo pela menor distancia
					x++;
					vermelhoY = x*q;
				}

				else if(which==2) {
					x--;
					vermelhoY = x*q;
				}

				else if(which==3) {
					y++;
					vermelhoX = y*q;
				}

				else if(which==1) {
					y--;
					vermelhoX = y*q;
				}

				if(x == 10 && y == -1){
					x = 10;
					y = 23;
					vermelhoX = y*q;
					vermelhoY = x*q;
				}

				else if(x == 10 && y == 22){
					x = 10;
					y = -1;
					vermelhoX = y*q;
					vermelhoY = x*q;
				}
				

}

void recurse(char M[][26],int &x, int &y, int &gposX, int &gposY, int &lastThisPos) {

    
    int auxX = x;
    int auxY = y;


                
                if(i > x && M[auxX+1][y] != '1') {
                    if(lastThisPos == 0) return; 
                    lastThisPos = 1;
                    x++;
                    gposY = x*q;
                }

                else if(i < x && M[auxX-1][y] != '1') {
                    if(lastThisPos == 1) return;
                    lastThisPos = 0;
                    x--;
                    gposY = x*q;
                }

                else if(j > y && M[x][auxY+1] != '1') {
                    if(lastThisPos == 3) return;
                    lastThisPos = 2;
                    y++;
                    gposX = y*q;
                }

                else if(j < y && M[x][auxY-1] != '1') {
                    if(lastThisPos == 2) return;
                    lastThisPos = 3;
                    y--;
                    gposX = y*q;
                }

                else if(x == 10 && y == -1){
                    x = 10;
                    y = 23;
                    gposX = y*q;
                    gposY = x*q;
                }

                else if(x == 10 && y == 22){
                    x = 10;
                    y = -1;
                    gposX = y*q;
                    gposY = x*q;
                }


}

void randmov(char M[][26],int &x, int &y, int &gposX, int &gposY, int phantom){

    int auxX = x;
    int auxY = y;

    randomIndex= rand()%4;

/*    
    if(phantom == 1)
        srand(time(NULL));
    randomIndex = rand()%4;

    if(phantom == 2)
        srand(time(NULL));
    randomIndex = rand()%4;
*/

    // Teleporte
    if(auxX == 10 && auxY == -1){
        x = 10;
        y = 22;
        gposX = y*q;
        gposY = x*q;
        return;
    }

    else if(auxX == 10 && auxY == 23){
        x = 10;
        y = 0;
        gposX = y*q;
        gposY = x*q;
        return;
    }

    if(randomIndex == 0 && M[auxX-1][y] != '1'){
        if(lastRandomPos == 1) return;
        lastRandomPos = 0;
        x--;
        gposY = x*q;
    }

    else if(randomIndex == 1 && M[auxX+1][y] != '1'){
        if(lastRandomPos == 0) return;
        lastRandomPos = 1;
        x++;
        gposY = x*q;
    }

    else if(randomIndex == 2 && M[x][auxY+1] != '1'){
        if(lastRandomPos == 3) return;
        lastRandomPos = 2;
        y++;
        gposX = y*q;
    }

    else if(randomIndex == 3 && M[x][auxY-1] != '1'){
        if(lastRandomPos == 2) return;
        lastRandomPos = 3;
        y--;
        gposX = y*q;
    }

    else
        recurse(M,x,y,gposX,gposY, randomIndex);

}

int inicializa() 
    {
    srand(time(NULL));

    if(!al_init())
    {
        cout << "Falha ao carregar Allegro" << endl;
        return 0;
    }

    if(!al_install_keyboard())
    {
        cout << "Falha ao inicializar o teclado" << endl;
        return 0;
    }

    timer = al_create_timer(1.0 / FPS);
    if(!timer)
    {
        cout << "Falha ao inicializar o temporizador" << endl;
        return 0;
    }
    
   if(!al_install_audio()){
      fprintf(stderr, "falha ao iniciar o audio!\n");
      return -1;
   }

   if(!al_init_acodec_addon()){
      fprintf(stderr, "falha ao iniciar o audio!\n");
      return -1;
   }
    
    if (!al_reserve_samples(2)){
      fprintf(stderr, "falha ao iniciar o audio\n");
      return -1;
   }

   win = al_load_sample("win.wav" );
   death = al_load_sample("death.wav" );
   beggining = al_load_sample("beggining.wav" );
   teleport = al_load_sample("teleport.wav");

    if(!win){
        printf("Winning audio clip sample not loaded! \n");
        return -1;
    }

    if(!beggining){
        printf("Beggining clip sample not loaded! \n");
        return -1;
    }

    if (!teleport){
        printf("Teleport clip sample not loaded! \n");
        return -1;
    }
    sample = al_load_sample("waka.wav"); 

    if (!sample){
      printf( "Falha ao iniciar o audio!\n" );
      return -1;
   }

    if(!al_init_image_addon())
    {
        cout <<"Falha ao iniciar al_init_image_addon!" << endl;
        return 0;
    }

    display = al_create_display(SCREEN_W, SCREEN_H);
    if(!display)
    {
        cout << "Falha ao inicializar a tela" << endl;
        al_destroy_timer(timer);
        return 0;
    }

    al_init_font_addon();
    al_init_ttf_addon();

    // Inicializacao das fontes
    if (!al_init_ttf_addon())
    {
        cout<< "Falha ao inicializar add-on allegro_ttf."<<endl;;
        return -1;
    }

    fonte = al_load_font("fonte.ttf", 30, 0);
    if(!fonte)
    {
        cout << "Falha ao carregar a fonte!" << endl;
        al_destroy_display(display);
        return 0;
    }
    al_draw_textf(fonte, al_map_rgb(255, 255, 255), 0, 515, 0, "Score: %d", contpontos);



    mapa = al_load_bitmap("map.bmp");
    if(!mapa)
    {
        cout << "Falha ao carregar o mapa!" << endl;
        al_destroy_display(display);
        return 0;
    }
    al_draw_bitmap(mapa,0,0,0);

	deathmap = al_load_bitmap("deathmap.bmp");
    if(!deathmap)
    {
        cout << "Falha ao carregar a imagem deathmap.bmp!" << endl;
        al_destroy_display(display);
        return 0;
    }

    pacman = al_load_bitmap("pacman.png");
    if(!pacman)
    {
        cout << "Falha ao carregar o pacman!" << endl;
        al_destroy_display(display);
        return 0;
    }
    al_draw_bitmap(pacman,posx,posy,0);

    pacup = al_load_bitmap("pac_up.png");
    pacdown = al_load_bitmap("pac_down.png");
    pacleft = al_load_bitmap("pac_left.png");
    pacright = al_load_bitmap("pac_right.png");
    fechado = al_load_bitmap("fechado.png");

    blinky = al_load_bitmap("blinky.png");
    if(!blinky)
    {
        cout << "Falha ao carregar Blinky!" << endl;
        al_destroy_display(display);

        return 0;
    }
    al_draw_bitmap(blinky,vermelhoX,vermelhoY,0);

    clyde = al_load_bitmap("clyde.png");
    if(!clyde)
    {
        cout << "Falha ao carregar Clyde!" << endl;
        al_destroy_display(display);

        return 0;
    }
    al_draw_bitmap(clyde, laranjaX, laranjaY,0);

        pinky = al_load_bitmap("pinky.png");
    if(!pinky)
    {
        cout << "Falha ao carregar Pinky!" << endl;
        al_destroy_display(display);

        return 0;
    }
    al_draw_bitmap(pinky,rosaX,rosaY,0);

        inky = al_load_bitmap("inky.png");
    if(!inky)
    {
        cout << "Falha ao carregar Inky!" << endl;
        al_destroy_display(display);

        return 0;
    }
    al_draw_bitmap(inky,azulX,azulY,0);

        pontos = al_load_bitmap("pontos.png");
    if(!pontos)
    {
        cout << "Falha ao carregar as pontos!" << endl;
        al_destroy_display(display);
        return 0;
    }
    al_draw_bitmap(pontos,r*20,s*20,0);

    event_queue = al_create_event_queue();
    if(!event_queue)
    {
        cout << "Falha ao criar a fila de eventos" << endl;
        al_destroy_display(display);
        al_destroy_timer(timer);
        return 0;
    }

    
    

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_textf(fonte, al_map_rgb(255, 255, 255), 0, 515, 0, "Score: %d", contpontos);
    al_flip_display();
    al_start_timer(timer);

    return 1;
}

int main(int argc, char **argv)
{

    int contador = 0;

    if(!inicializa()) return -1;


    while(!sair)
    {
		cout << contador << endl;
		contador++;


        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);


        if(ev.type == ALLEGRO_EVENT_TIMER)
        {




            if(key[KEY_RIGHT] && (i==13) && (j==24)){
                i = 10;
                j = 0;
                posx = j*q;
                posy = i*q;
                al_play_sample(teleport, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE, NULL);
            }

            if(key[KEY_LEFT] && (i==10) && (j==0)){
                i = 13;
                j = 24;
                posx = j*q;
                posy = i*q;
                al_play_sample(teleport, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE, NULL);
            }

            if(key[KEY_UP] && MAPA[i-1][j] != '1')
            {
                pacman = pacup;
                i--;
                posy = i*q;
                lastmouth = 2;
            }

            if(key[KEY_DOWN] && MAPA[i+1][j] != '1')
            {
                pacman = pacdown;
                i++;
                posy = i*q;
                lastmouth = 0;
            }

            if(key[KEY_LEFT] && MAPA[i][j-1] != '1')
            {
                pacman = pacleft;
                j--;
                posx = j*q;
                lastmouth = 1;
            }

            if(key[KEY_RIGHT] && MAPA[i][j+1] != '1')
            {
                pacman = pacright;
                j++;
                posx = j*q;
                lastmouth = 3;
            }
            //sumir com os itens anteriores caso ele passe em cima;
            if(MAPA[i][j] == '2'){
                    al_play_sample(sample, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE, NULL);
                    MAPA[i][j] = '0';
                    contpontos=contpontos+5;
                    total --;

            if(total==0){
                al_destroy_sample(sample);
                acabar == true;
                al_play_sample(win, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                al_rest(4.8);
                return 0;
            }

            }

 

        // Controle do abrir e fechar da boca do pacman
        if(sim%2==0){
            aux = pacman;
            pacman = fechado;  //Se a variavel sim for par, redraw o pacman com boca fechada
            redraw = true;
        }
        else{
            pacman = aux;
            redraw = true; //Se nao, da redraw nele normal

            //Switch para redesenhar ultima posica do pacman apos fechar boca
            switch(lastmouth){
                case 0:
                    pacman = pacdown; break;
                case 1:
                    pacman = pacleft;  break;
                case 2:
                    pacman = pacup;  break;
                case 3:
                    pacman = pacright;  break;
                }
			}

        sim++;

            redraw = true;
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }
        else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_UP:
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
        else if(ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            switch(ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_UP:
                key[KEY_UP] = false;
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

            case ALLEGRO_KEY_ESCAPE:
                sair = true;
                break;
            }
        }



        if(redraw && al_is_event_queue_empty(event_queue))
        {
            redraw = false;

            al_clear_to_color(al_map_rgb(0,0,0));

            if(gameover){
                al_destroy_bitmap(mapa);
				al_draw_bitmap(deathmap,0,0,0);
				al_destroy_sample(sample);
				al_play_sample(death, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
				al_rest(0.8);
				acabar=true;
	      		al_rest(1.3);
			}            
            

            al_draw_bitmap(mapa,0,0,0);
            al_draw_textf(fonte, al_map_rgb(255, 255, 255), 0, 515, 0, "Score: %d", contpontos);
            al_draw_bitmap(pacman,posx,posy,0);
            al_draw_bitmap(blinky, vermelhoX, vermelhoY,0);
            al_draw_bitmap(clyde, laranjaX, laranjaY,0);
            al_draw_bitmap(pinky, rosaX, rosaY,0);
            al_draw_bitmap(inky, azulX, azulY,0);
            for (int r = 0; r<26; r++){
                for (int s = 0; s<26; s++){
                    if (MAPA[s][r] == '2'){
                        al_draw_bitmap(pontos,r*q,s*q, 0);
                    }
                }
            }

                randmov(MAPA,aX,aY,azulX,azulY,0);  
                randmov(MAPA,lX,lY,laranjaX,laranjaY,1); 
                randmov(MAPA,rX,rY,rosaX,rosaY,2);  
                BM(MAPA,vX,vY,vermelhoX,vermelhoY);
                

                
                al_flip_display();
            }
                    if (inicio){
                al_play_sample(beggining, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                inicio=false;
                al_rest(4.1);	
            }
            if( (vX==i && vY==j) || (i==aX && j==aY) || (i==lX && j==lY) || (i==rX && j==rY)){
                al_play_sample(death, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

				gameover=true;

			}

                
        else if ((lastpacmanx==vX && lastpacmany==vY && i==ulx && j==uly) || 
                  (lastpacmanx==aX && lastpacmany==aY && i==lastazulx && j==lastazuly) ||
                  (lastpacmanx==lX && lastpacmany==lY && i==lastlaranjax && j==lastlaranjay) ||
                  (lastpacmanx==vX && lastpacmany==vY && i==lastrosax && j==lastrosay) ){



                gameover=true;

                }
                
        	if(acabou){
			al_destroy_bitmap(pacman);
			al_destroy_bitmap(pontos);
			al_destroy_bitmap(blinky);
			al_destroy_bitmap(inky);
			al_destroy_bitmap(clyde);
			al_destroy_bitmap(pinky);
            al_rest(1.92);
            return 0;
            }

        lastpacmanx=i; lastpacmany=j;
        lastvermelhox=vX; lastvermelhoy=vY;
        lastlaranjax=lX; lastlaranjay=lY;
        lastrosax=rX; lastrosay=rY;
        lastazulx=aX; lastazuly=aY;

        }
    
		
			
		


        al_destroy_bitmap(mapa);
        al_destroy_bitmap(pacman);
        al_destroy_timer(timer);
        al_destroy_display(display);
        al_destroy_event_queue(event_queue);
        al_destroy_bitmap(blinky);
        al_destroy_bitmap(clyde);
        al_destroy_bitmap(pinky);
        al_destroy_bitmap(pontos);
        al_destroy_font(fonte);
        al_destroy_bitmap(deathmap);


    return 0;
}

//g++ pacman.cpp -lallegro -lallegro_image -lallegro_audio -lallegro_acodec -lallegro_font -lallegro_ttf

