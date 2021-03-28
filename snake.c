#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#define DELAY 30000
#define WIDTH 30
#define HEIGHT 30

int gameover = 0, score = 0;
int x = 0, y = 0;
int fruitx, fruity;
int size = 0;
int next_x = 0, next_y = 0;
//int directionx, directiony;
int bx = 5, bx2 = 5;
int by = 5, by2 = 5;

void game() {
    
}

void setup() {
    initscr();
    noecho();
    curs_set(FALSE);

    x = WIDTH/2;
    y = HEIGHT/2;

    int lower = 6;
    int upper = 34;
    fruitx = (rand() % (upper - lower + 1)) + lower;
    fruity = (rand() % (upper - lower + 1)) + lower;
}

void boundaries() {
    int control = 0;
    int flag = 0;
    int direction = 1;
    while (!control) {
        mvprintw(by,bx, "#");
        mvprintw(by2, bx2, "#");
        refresh();
        
        if (!flag) {
            next_x = bx + direction;
            next_y = by2 + direction; 
        }
        if (next_x > WIDTH + 5 && next_y > HEIGHT + 5 || flag) {
            if (!flag){
                next_x = 0;
                next_y = 0;
                flag = 1;
            }
            next_x = bx2 + direction;
            next_y = by + direction;

            if (next_x > WIDTH + 5 && next_y > HEIGHT + 5) {
                control = 1;
            } else {
                bx2 += direction;
                by += direction;
            }
        } else {
            bx+= direction;
            by2+= direction;
        }
        usleep(DELAY);
    }
}

int main() {

    setup();
    boundaries();
    char c;
    scanf("%c", &c);
    if (c) {
        endwin();     
    }
    return 0;
}
