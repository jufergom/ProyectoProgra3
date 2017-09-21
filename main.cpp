#include <allegro.h>
#include "inicia.h"
#include "disparos.h"
#include "nave.h"
#include <stdlib.h>
#include <time.h>
#define ALTO 550
#define ANCHO 520

bool ganar(struct Nave enemigos[])
{
    for(int i = 0; i < 60; i++)
    {
        if(enemigos[i].vida != 0)
            return false;
    }
    return true;
}

bool limites(struct Nave enemigos[], int &dir)
{
    for(int i = 0; i < 60; i++)
    {
        if((enemigos[i].x > 520 || enemigos[i].x < 50) && enemigos[i].vida)
        {
            dir = -1 * dir;
            return true;
        }
    }
    return false;
}

Nave enemigos[60];
int azar = rand()%55;//es para los disparos aleatorios
int mov = 0;
int dir = -5;
int velocidad_juego = 40;

void acomoda_enemigo(struct Nave enemigos[]){
    int indice =-1;//>
    for (int i=0;i<5;i++){
      for (int j=0;j<11;j++){
        indice++;
        enemigos[indice].iniciar("Imagenes/enemigos.bmp", "Imagenes/Bala_enem.bmp", 6, 12, 25, 20, 140+j*30, 100+i*24,1,1, 1);
            }
        }
}

void pintar_enemigo(struct Nave enemigos[],BITMAP*buffer){
    int indice =-1;
    for (int i=0;i<5;i++){
      for (int j=0;j<11;j++){
        indice++;
        if(enemigos[indice].vida != 0)
            enemigos[indice].pintar(buffer);
        }
    }
}

void mover_enemigos(struct Nave enemigos[], int &mov, int &dir)
{
    for(int i = 0; i < 55; i++)
    {
        enemigos[i].x += dir;
    }
    if(++mov == 2)
        mov = 0;

    if(limites(enemigos, dir))
    {
        for(int j = 0; j < 60; j++)
        {
            enemigos[j].y += 10;
        }
    }
}

void jugar(Nave nave,Nave enemigos[], BITMAP* buffer)
{

    Balas disparo[nave.max_disparos];
    BITMAP *espacio = load_bitmap("espa.bmp", NULL);
    Balas disparo_enemigo[enemigos[0].max_disparos];

    acomoda_enemigo(enemigos);
    bool quit_game = false;
    while(!(key[KEY_ESC] || quit_game))
    {
        clear_to_color(buffer, 0x000000);

        if(enemigos[0].temporizador(velocidad_juego))
            mover_enemigos(enemigos, mov, dir);

        nave.pintar(buffer);
        nave.mover();
        if(key[KEY_SPACE] && nave.temporizador(velocidad_juego))
        crear_bala(nave.n_disparos,nave.max_disparos,disparo,nave.x,nave.y,nave.dir_bala);

        nave.disparar(disparo, buffer);

        for(int i = 0; i < 60; i++)
            if(eliminar_bala_objeto(nave, enemigos[i], disparo))
                explocion1(enemigos[i],buffer);

        pintar_enemigo(enemigos,buffer);
        if(enemigos[azar].n_disparos==0)  azar = rand()%55;
        enemigos[azar].disparar(disparo_enemigo,buffer);

        if(eliminar_bala_objeto(enemigos[azar],nave,disparo_enemigo))
            explocion2(nave,buffer);

        if(ganar(enemigos))
            quit_game = true;
        if(nave.vida == 0)
            quit_game = true;

        //masked_blit(cursor, buffer, 0, 0, mouse_x, mouse_y, 13, 22);
        blit(buffer, screen, 0, 0, 0, 0, ANCHO, ALTO);
    }
}


int main()
{

    //iniciando allegro
    inicia_allegro(ANCHO, ALTO);
    inicia_audio(190, 190);

    //variables bitmap

    //pantalla
    BITMAP *buffer = create_bitmap(ANCHO, ALTO);
    //fondo del menu
    BITMAP *fondo = load_bitmap("Fondo.bmp", NULL);

    BITMAP *Jugar = load_bitmap("Jugar.bmp", NULL);

    BITMAP *Instrucciones = load_bitmap("Instrucciones.bmp", NULL);

    BITMAP *Scores = load_bitmap("Scores.bmp", NULL);

    BITMAP *Salir = load_bitmap("Salir.bmp", NULL);

    BITMAP *Instru = load_bitmap("Instru.bmp", NULL);

    BITMAP *Instru2 = load_bitmap("Instru2.bmp", NULL);

    BITMAP *cursor = load_bitmap("cursor.bmp", NULL);

    SAMPLE *musica = load_sample("musica.wav");



    //aqui vamos a crear los bitmaps de la bala y la nave
    //BITMAP *bala = load_bitmap("Imagenes/Bala2.bmp", NULL);
    //BITMAP *nave = load_bitmap("Imagenes/nave.bmp", NULL);

    //objeto de tipo nave, viene de la estructura nave
    Nave nave;
    nave.iniciar("Imagenes/nave.bmp", "Imagenes/Bala2.bmp", 6, 12, 30, 20, ANCHO/2, ALTO-50,-2,0, 3);

    //este objeto de tipo nave es el enemigo



    /*esta variable booleana que esta aqui sirve para saber cuando se va a finalizar
    la ejecucion del programa, practicamente es lo que va a romper el ciclo del juego
    */
    bool quit = false;
    //con esto reproducimos la musica
    play_sample(musica, 200, 150, 1000, 0);

    int recien_salido = 0; //variable para controlar tiempos en el menu
    int cont = 0; //lo mismo que la anterior
    while(!quit)
    {
        //limpiar pantalla
        clear_to_color(buffer, 0x000000);
        //Texto de jugar
        blit(fondo, buffer, 0, 0, 0, 0, ANCHO, ALTO);
        if(mouse_x > 190 && mouse_x < 331 && mouse_y > 239 && mouse_y < 283)
        {
            blit(Jugar, buffer, 0, 0, 0, 0, ANCHO, ALTO);
            if(mouse_b & 1)
                jugar(nave,enemigos, buffer);
        }

        //Texto de instrucciones
        if(mouse_x > 105 && mouse_x < 424 && mouse_y > 305 && mouse_y < 348)
        {
            blit(Instrucciones, buffer, 0, 0, 0, 0, ANCHO, ALTO);
            if(mouse_b & 1)
            {
                //con esta variable controlo la salida de la pantalla de instrucciones
                bool salir_instrucciones = false;
                //este ciclo es para que no se cierre la pantalla de las instrucciones
                while(!salir_instrucciones)
                {
                    blit(Instru, buffer, 0, 0, 0, 0, ANCHO, ALTO);
                    //cambiar la imagen de instrucciones
                    if(mouse_x > 100 && mouse_x < 380 && mouse_y > 444 && mouse_y < 510)
                    {
                        clear_to_color(buffer, 0x000000);
                        blit(Instru2, buffer, 0, 0, 0, 0, ANCHO, ALTO);
                        //aqui regresaremos al menu principal
                        if(mouse_b & 1)
                        {
                            salir_instrucciones = true;
                            recien_salido = 1;
                        }
                    }
                    //imagen del cursor
                    masked_blit(cursor, buffer, 0, 0, mouse_x, mouse_y, 13, 22);
                    //esto practicamente imprime lo que queremos meter en la pantalla
                    blit(buffer, screen, 0, 0, 0, 0, ANCHO, ALTO);
                }
            }
        }

        //Texto de scores
        if(mouse_x > 182 && mouse_x < 345 && mouse_y > 377 && mouse_y < 421)
        {
            blit(Scores, buffer, 0, 0, 0, 0, ANCHO, ALTO);
            if(mouse_b & 1)
            {
                while(!(key[KEY_ESC]))
                {
                    clear_to_color(buffer, 0x000000);
                    textout_centre_ex(buffer, font, "holis", ANCHO/2, 10, 0xFFFFFF, 0xDF1680);
                    blit(buffer, screen, 0, 0, 0, 0, ANCHO, ALTO);
                }
            }
        }

        //Texto de salir
        if(mouse_x > 205 && mouse_x < 318 && mouse_y > 444 && mouse_y < 492)
        {
            blit(Salir, buffer, 0, 0, 0, 0, ANCHO, ALTO);
            if(mouse_b & 1 && recien_salido == 0)
                quit = true;
        }
        //controlar tiempo
        if(cont++ > 40)
        {
            recien_salido = 0;
            cont = 0;
        }
        //imagen del cursor
        masked_blit(cursor, buffer, 0, 0, mouse_x, mouse_y, 13, 22);
        //esto practicamente imprime lo que queremos meter en la pantalla
        blit(buffer, screen, 0, 0, 0, 0, ANCHO, ALTO);
    }

    //destructores
    destroy_bitmap(buffer);
    destroy_bitmap(fondo);
    destroy_sample(musica);
    return 0;
}
END_OF_MAIN () //siempre colocar esto
