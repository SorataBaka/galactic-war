
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "definition.h"
#include "draw.h"

void game(Player * playerObject, Meteor * meteorArray) {
    int maxHeight, maxWidth;
    char key;
    erase();
    timeout(50);
    getmaxyx(stdscr, maxHeight, maxWidth);
    while(1){
        erase();
        //For drawing the character sprite itself
	    charSprite(playerObject->currentPosition.x, playerObject->currentPosition.y);
        struct Missile * missilePrint = playerObject->missileArray;
        while(missilePrint != NULL){
            mvaddstr(missilePrint->y, missilePrint->x, "^");
            missilePrint = missilePrint->next;
        }

        //Read key bindings for next movement
        refresh();

        key = getch();
        if(key == 'q') break;
        if(key == playerObject->userBindings.left) playerObject->currentPosition.x--;
        if(key == playerObject->userBindings.right) playerObject->currentPosition.x++;
        if(key == playerObject->userBindings.shoot){
            struct Missile * newMissile = (struct Missile *)malloc(sizeof(struct Missile));
            newMissile->x = playerObject->currentPosition.x;
            newMissile->y = maxHeight-2;
            //Check if array is empty
            if(playerObject->missileArray == NULL){
                newMissile->next = NULL;
                playerObject->missileArray = newMissile;
            } else {
                newMissile->next =  playerObject->missileArray;
                playerObject->missileArray = newMissile;
            }
        }
        //Handle missile movement logic
        struct Missile * movementPlaceholder = playerObject->missileArray;
        while(movementPlaceholder != NULL){
            movementPlaceholder->y--;
            //TODO HANDLE WHAT HAPPENS WHEN THE MISSILE GO OUT OF BOUNDS
            movementPlaceholder = movementPlaceholder->next;
        }
    }
    return;
}

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
    Bindings testBindings = {
        'a', 'd', ' '
    };
    Position startingPosition = {maxWidth/2, maxHeight};
    Player testPlayer;
    strcpy(testPlayer.username, "sora");
    testPlayer.health = 100;
    testPlayer.points = 0;
    testPlayer.userBindings = testBindings;
    testPlayer.currentPosition = startingPosition;
    testPlayer.missileArray = NULL;
    
    //Initialize meteor array
    Meteor * meteorArray = (Meteor * )malloc(sizeof(Meteor) * 50);


    //Write main screen code bottom here.


    //Begin game.
    game(&testPlayer, meteorArray);

    
    //Cleanup
    endwin();
    return 0;

}
