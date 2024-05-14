#ifndef DRAW_H
#define DRAW_H

#include <iostream>
#include <mpi.h>
#include <QCoreApplication>
#include "/home/svetlana/allegro5/include/allegro5/allegro.h"
#include "/home/svetlana/allegro5/include/allegro5/allegro_primitives.h"

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 1600;

void draw_rectangles(int *mas, int N, int rank) {
        al_clear_to_color(al_map_rgb(0,0,0));
        al_init_primitives_addon();
        int x_wid=5;
        for (int i=0; i<N; i++){
                al_draw_filled_rectangle(i*x_wid+i*10, mas[i] ,(i+1)*x_wid+i*10, 0,al_map_rgb(255,255,255) );
        }
        al_flip_display();
        al_rest(0.001);
}

#endif // DRAW_H
