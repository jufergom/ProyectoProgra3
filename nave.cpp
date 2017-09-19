#include "nave.h"
#include <allegro.h>
#include "disparos.h"

#define ALTO 600
#define ANCHO 600
int dir_bala;
void Nave::iniciar(char* ruta_nave, char* ruta_bala, int _alto_bala, int _ancho_bala,
                   int _ancho_personaje, int _alto_personaje, int _x, int _y,int _dir_bala)
{
    x = _x;
    y = _y;
    n_disparos = 0;
    max_disparos = 5;
    tick = 0;
    ancho_bala = _ancho_bala;
    alto_bala = _alto_bala;
    ancho_personaje = _ancho_personaje;
    alto_personaje = _alto_personaje;
    dir_bala = _dir_bala;

    img_nave = load_bitmap(ruta_nave, NULL);
    img_bala = load_bitmap(ruta_bala, NULL);
}

void Nave::pintar(BITMAP *buffer)
{
    masked_blit(img_nave, buffer, 0, 0, x, y, ancho_personaje, alto_personaje);
}

void Nave::mover()
{
    if(key[KEY_LEFT])
        x-=1;
    if(key[KEY_RIGHT])
        x+=1;
}

bool Nave::temporizador()
{
    tick++;
    if(tick == 5)
    {
        tick = 0;
        return true;
    }
    return false;
}

void Nave::disparar(struct Balas disparos[], BITMAP* buffer)
{
    if(key[KEY_SPACE] && temporizador())
        crear_bala(n_disparos, max_disparos, disparos, x, y, dir_bala);

    pintar_bala(n_disparos, max_disparos, disparos, buffer, img_bala, alto_bala, ancho_bala);
    elimina_bala(n_disparos, max_disparos, disparos, ANCHO, ALTO);
}
void Nave::acomoda_enemigo(struct Nave enemigos[]){
    int indice =-1;//>
    for (int i=0;i<5;i++){
      for (int j=0;j<11;j++){
        indice++;
        enemigos[indice].iniciar("Imagenes/enemigos.bmp", "Imagenes/Bala_enem.bmp", 6, 12, 25, 20, 140+j*30, 100+i*24,2);

    }

    }
}
void Nave::pintar_enemigo(struct Nave enemigos[],BITMAP*buffer){
    int indice =-1;
    for (int i=0;i<5;i++){
      for (int j=0;j<11;j++){
        indice++;
        enemigos[indice].pintar(buffer);

    }

    }
}


