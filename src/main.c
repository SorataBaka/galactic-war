
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
    timeout(100);
    getmaxyx(stdscr, maxHeight, maxWidth);
    while(1){
        erase();
        //For drawing the character sprite itself
	    charSprite(playerObject->currentPosition.x, playerObject->currentPosition.y);
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
                newMissile->prev = NULL;
                playerObject->missileArray = newMissile;
            } else {
                newMissile->next =  playerObject->missileArray;
                playerObject->missileArray->prev = newMissile;
                newMissile->prev = NULL;
                playerObject->missileArray = newMissile;
            }
        }
        //Handle missile movement logic. this is stupid. please fix if found ideas.
        struct Missile * movementPlaceholder = playerObject->missileArray;
        if(movementPlaceholder == NULL) continue;
        while(movementPlaceholder != NULL){
            movementPlaceholder->y--;
            if(movementPlaceholder->y < 0){
                if(movementPlaceholder->next == NULL && movementPlaceholder->prev == NULL){
                    //If it is the only object in the array.
                    playerObject->missileArray = NULL;
                    movementPlaceholder = NULL;
                    free(movementPlaceholder);
                } 
                else if(movementPlaceholder->next == NULL && movementPlaceholder->prev != NULL){
                    //If it is the last object in the array.
                    movementPlaceholder = movementPlaceholder->prev;
                    free(movementPlaceholder->next);
                    movementPlaceholder->next = NULL;
                }
                else if(movementPlaceholder->next != NULL && movementPlaceholder->prev == NULL){
                    // If it is the first object in the array.
                    playerObject->missileArray = movementPlaceholder->next;
                    playerObject->missileArray->prev = NULL;
                    free(movementPlaceholder);
                    movementPlaceholder = playerObject->missileArray;
                    movementPlaceholder = movementPlaceholder->next;
                } else {
                    //If it is somewhere in the middle
                    movementPlaceholder->prev->next = movementPlaceholder->next;
                    movementPlaceholder->next->prev = movementPlaceholder->prev;
                    struct Missile * temp = movementPlaceholder->next;
                    free(movementPlaceholder);
                    movementPlaceholder = temp;
                }
            } else {
                movementPlaceholder = movementPlaceholder->next;
            }
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
