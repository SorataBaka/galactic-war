
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "definition.h"
#include "game.h"
#include "endscreen.h"
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
        'a', 'd', ' '
    };
    Position startingPosition = {maxWidth/2, maxHeight};
    Player player;
    strcpy(player.username, "sora");
    player.health = 100;
    player.points = 0;
    player.userBindings = defaultBindings;
    player.currentPosition = startingPosition;
    player.missileArray = NULL;
    
    //Initialize meteor array
    Meteor * meteorArray = NULL;


    //Write main screen code bottom here.
    

    //Begin game.
    mainScreen(&player, meteorArray ,  maxHeight, maxWidth);

    //Cleanup
    endwin();
    return 0;

}
