#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

int i, j, width = 30;
int height = 30, score;
int x, y, fruitx, fruity;
int gameover = 0;
int dir;

void draw(void){
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++){
            if  (i == 0 || i == width - 1
                    || j == 0 || j == height - 1){
                printf("#");
            } else if ( i == x && j == y) {
                printf("0");
            } else if (i == fruitx && j == fruity){
                printf("*");
            } 
            else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void input(void){
    if (khbit()) {
        switch (getch()) {
            case 'a':
                dir = 1;
                break;
            case 's':
                dir = 2;
                break;
            case 'd':
                dir = 3;
                break;
            case 'w':
                dir = 4;
                break;
            case 'x':
                gameover = 1;
                break;
            default:
                break;
        }
    } 
}

void logic(void) {
    switch(dir) {
        case 1:
            x--;
            break;
        case 2:
            y--;
            break;
        case 3:
            x++;
            break;
        case 4:
            y++;
            break;
    }
    if (x == 0 || x == width - 1 || y == 0 || y == height -1){
        gameover == 1;
    } else if (x == fruitx && y == fruity) {
        score += 10;
    }
}

void setup(void) {
    x = width/2;
    y = height/2;
    label1:
        fruitx = rand() % 30;
        if (fruitx == 0){
            goto label1;
        }
    label2:
        fruity = rand() % 30;
        if (fruity == 0){
            goto label2;
        }
}

int main(void) {
    setup();
    while (!gameover) {
        draw();
        input();
        logic();
    }
    return 0;
}

