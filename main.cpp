#include <allegro.h>
#include "inicia.h"

int main()
{
    inicia_allegro(520, 550);
    inicia_audio(190, 190);

    BITMAP *buffer = create_bitmap(520, 550);

    BITMAP *fondo = load_bitmap("Fondo.bmp", NULL);

    BITMAP *cursor = load_bitmap("cursor.bmp", NULL);

    SAMPLE *musica = load_sample("musica.wav");

    bool quit = false;

    play_sample(musica, 200, 150, 1000, 0);
    while(!quit)
    {
        blit(fondo, buffer, 0, 0, 0, 0, 520, 550);
        if(mouse_x > 205 && mouse_x < 318 && mouse_y > 444 && mouse_y < 492)
        {
            if(mouse_b & 1)
                quit = true;
        }
        masked_blit(cursor, buffer, 0, 0, mouse_x, mouse_y, 13, 22);
        blit(buffer, screen, 0, 0, 0, 0, 520, 550);
    }
    destroy_bitmap(buffer);
    destroy_bitmap(fondo);
    destroy_sample(musica);
    return 0;
}
END_OF_MAIN ()
