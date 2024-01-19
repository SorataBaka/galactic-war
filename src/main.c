
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#include "definition.h"
#include "draw.h"

void game(Player * playerObject, Meteor * meteorArray) {
    int maxHeight, maxWidth;
    char key;
    erase();
    timeout(-1);
    getmaxyx(stdscr, maxHeight, maxWidth);
    while(1){
        erase();
	
        refresh();
        key = getch();
        if(key == 'q') break;

    }
    return;
}

int main(){
    //Initialize player
    Bindings testBindings = {
        'a', 'd', ' '
    };
    Position startingPosition = {0, 0};
    Player testPlayer;
    strcpy(testPlayer.username, "sora");
    testPlayer.health = 100;
    testPlayer.points = 0;
    testPlayer.userBindings = testBindings;
    testPlayer.currentPosition = startingPosition;
    testPlayer.missileArray = (Missile *)malloc(sizeof(Missile) * 200);
    
    //Initialize meteor array
    Meteor * meteorArray = (Meteor * )malloc(sizeof(Meteor) * 50);

    //Begin initializing ncurses
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    timeout(-1); // For initializion purposes, set timeout to no wait;

    //Write main screen code bottom here.


    //Begin game.
    game(&testPlayer, meteorArray);

    
    //Cleanup
    endwin();
    return 0;

}
