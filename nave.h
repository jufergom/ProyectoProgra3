#ifndef NAVE_H_INCLUDED
#define NAVE_H_INCLUDED
#include <stdlib.h>
#include <time.h>
#include <allegro.h>
#include "disparos.h"
void explocion1(struct Nave ene,BITMAP *buffer);
void explocion2(struct Nave N,BITMAP *buffer);

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
    int vida;

    BITMAP *img_nave;
    BITMAP *img_bala;
    BITMAP *explo_ene;



    void iniciar(char* ruta_nave, char* ruta_bala, int _ancho_bala, int _alto_bala,
                 int _ancho_personaje, int _alto_personaje, int _x, int _y,int dir_bala,int _tipo, int _vida);
    void pintar(BITMAP* buffer);
    bool temporizador();
    void mover();
    void disparar(struct Balas disparos[], BITMAP* buffer);






};

#endif // NAVE_H_INCLUDED
