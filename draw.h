#ifndef DRAW_H
#define DRAW_H

#include <iostream>
#include <mpi.h>
#include <math.h>
#include <QCoreApplication>
#include <iostream>
#include <vector>
#include "/home/svetlana/allegro5/include/allegro5/allegro.h"
#include "/home/svetlana/allegro5/include/allegro5/allegro_primitives.h"
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 500;

bool shows=false;

void draw_rectangles(int *mas, int N, int start) {

        al_clear_to_color(al_map_rgb(0,0,0));
        al_init_primitives_addon();
        //int x_wid=SCREEN_WIDTH/N;
        int x_wid=10;
        int t;
        t=0;
        for (int i=start; i<N+start; i++, t++){

            al_draw_filled_rectangle(i*x_wid+i*10, mas[t] ,(i+1)*x_wid+i*10, 0,al_map_rgb(255,255,255) );
        }
        t=0;
        al_flip_display();
        al_rest(1);

        //al_destroy_display(display);


    }

#endif // DRAW_H
