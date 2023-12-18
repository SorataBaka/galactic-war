#include <stdlib.h>
#include <ncurses.h>
#include <locale.h>
#include "definition.h"
#include <math.h>


void printSprite(Position printPosition){
    mvaddch(printPosition.y, printPosition.x, '#');
}

void initialize(int * playerAmount, Player * playerArray){
    //Initialize start screen.
    erase();
    mvaddstr(1, 3, "Galactic War");
    mvaddstr(2, 3, "Welcome to Galactic Wars!");
    mvaddstr(4, 3, "How many players [1 - 4]: ");
    scanw("%d", playerAmount);
    if(*playerAmount < 2 || *playerAmount > 4){
        erase();
        mvaddstr(1, 3, "Invalid player size. Please enter again.");
        mvaddstr(3, 3, "How many players [1 - 4]: ");
    }

    //Initialize the player directory.
    playerArray = (Player *)malloc(sizeof(Player) * *playerAmount);

    //Start prompting for basic information.
    erase();
    for(int i = 0; i < *playerAmount; i++){
        Player * mem = playerArray + i;
        mem->id = i;
        mem->score = 0;
        mem->trajectory = down;
        mem->pos = {i + 5, i + 5};


        mvaddstr(1, 3, "Enter username: ");
        scanw("%s", mem->username);
        mvaddstr(2, 3, "Key binding for turning CLOCKWISE: ");
        scanw("%c", mem->user_bindings.clockwise);
        mvaddstr(3, 3, "Key binding for turning ANTICLOCKWISE: ");
        scanw("%c", mem->user_bindings.anticlockwise);
        mvaddstr(4, 3, );


    }
}

int main(){
    int width, height;
    int playerAmount;
    Player * playerArray;

    initscr();
    erase();

    getmaxyx(stdscr, height, width);
    Position screenMiddle = {width/2, height/2};
    timeout(-1);
    while(true){
        initialize(&playerAmount);
        if(getch() == 'q') break;
    }
    endwin();
    return EXIT_SUCCESS;
}
