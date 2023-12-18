#include <stdlib.h>
#include <ncurses.h>
#include <locale.h>
#include "definition.h"

int main(){
    initscr();

    mvprintw(0, 0, "Hello World");

    timeout(-1);
    while(true){
        if(getch() == 'q') break;
    }
    endwin();
    return EXIT_SUCCESS;
}