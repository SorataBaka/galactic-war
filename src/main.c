
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>

#include "definition.h"
#include "game.h"
#include "endscreen.h"

int main(){
	int maxHeight, maxWidth;

    //Begin initializing ncurses
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    timeout(-1); // For initializion purposes, set timeout to no wait;
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
    game(&player, meteorArray);
    endScreen(maxWidth, maxHeight, &player);

    //Cleanup
    endwin();
    return 0;

}
