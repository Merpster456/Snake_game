#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#define DELAY 30000
#define WIDTH 30
#define HEIGHT 30

int gameover = 0, score = 0;
int x = 0, y = 0;
int fruitx, fruity;
int size = 1;
int next_x = 0, next_y = 0;
int bx = 5, bx2 = 5;
int by = 5, by2 = 5;
int flag;
WINDOW *game_window;

void game() {
    wclear(game_window);
    for (int i = 0; i < size; i++) {
        if (size == 1) {
        mvprintw(y,x,"0");
        } else {
            mvprintw(y,x, "o");
        }
    }
    mvprintw(fruity, fruitx, "*");   
    wrefresh(game_window);
}
void input(){
    char ch;
    if ((ch = getch())){
        switch (ch) {
            case 'a':
                flag = 1;
                break;
            case 's':
                flag = 2;
                break;
            case 'd':
                flag = 3;
                break;
            case 'w':
                flag = 4;
                break;
            case 'x':
                gameover = 1;
                break;
            default:
                break;
        }
    }
}
void logic(){
    switch (flag) {
        case 1:
            x--; 
            break;
        case 2:
            y++;
            break;
        case 3:
            x++;
            break;
        case 4:
            y--;
            break;
    }
    int mx;
    int my;
    int bx;
    int by;
    getmaxyx(game_window, my, mx);
    getbegyx(game_window, by, bx);

    if (x > mx + 5 || x < bx || y > my + 5 || y < by) {
        gameover = 1;
    } else if (x == fruitx && y == fruity) {
        score += 10;
        size++;
    }
}

void setup() {
    initscr();
    noecho();
    cbreak();
    curs_set(FALSE);

    game_window = newwin(HEIGHT -1, WIDTH -1, 6, 6);

    x = (WIDTH/2) + 5;
    y = (HEIGHT/2) + 5;

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

void endmsg(){
    while (!getch()) {
        clear();
        mvprintw((HEIGHT/2)+5, (WIDTH/2) + 5, "~~~GAME OVER~~~");
        mvprintw((HEIGHT/2)+7, (WIDTH/2) + 5, "Score: %i", score);
        mvprintw((HEIGHT/2)+8, (WIDTH/2) + 5, "Size: %i", size);
        mvprintw((HEIGHT/2)+11, (WIDTH/2) + 5, "Press any button to quit");
        refresh();
    }
    clear();
    delwin(game_window);
    refresh();
    endwin();
}

int main() {

    setup();
    boundaries();

    while (!gameover) {
            game();
            input();
            logic();
            usleep(DELAY);
    }
    endmsg();
    return 0;
}
