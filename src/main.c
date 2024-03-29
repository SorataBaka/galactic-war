
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "definition.h"
#include "mainscreen.h"

int main(){
	int maxHeight, maxWidth;

    //Begin initializing ncurses
    initscr();
    noecho();
    cbreak();
    getmaxyx(stdscr, maxHeight, maxWidth);

    //Initialize player
    Bindings defaultBindings = {
        'a', 'd', ' ', 'x', 'c'
    };
    Position startingPosition = {maxWidth/2, maxHeight};
    Player player;
    //Input username promt
    player.userBindings = defaultBindings;
    player.missileArray = NULL;
    //Initialize meteor array
    Meteor * meteorArray = NULL;

    //Begin game.
    mainScreen(&player, meteorArray ,  maxHeight, maxWidth);

    //Cleanup
    endwin();
    return 0;

}
