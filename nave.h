#ifndef NAVE_H_INCLUDED
#define NAVE_H_INCLUDED
#include <stdlib.h>
#include <time.h>
#include <allegro.h>
#include "disparos.h"

struct Nave
{
    int x, y; //coordenadas
    int n_disparos;
    int max_disparos;
    int tick;
    //ancho y alto de la bala
    int ancho_bala;
    int alto_bala;
    //ancho y alto del personaje
    int ancho_personaje;
    int alto_personaje;
    int dir_bala;
    int tipo;
    BITMAP *img_nave;
    BITMAP *img_bala;

    void iniciar(char* ruta_nave, char* ruta_bala, int _ancho_bala, int _alto_bala,
                 int _ancho_personaje, int _alto_personaje, int _x, int _y,int dir_bala,int _tipo);
    void pintar(BITMAP* buffer);
    bool temporizador();
    void mover();
    void disparar(struct Balas disparos[], BITMAP* buffer);



};

#endif // NAVE_H_INCLUDED
