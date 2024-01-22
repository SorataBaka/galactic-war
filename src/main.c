
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "definition.h"
#include "draw.h"
#include "util.h"

time_t currentTime;

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
        //Print missiles
        Missile * missilePrint = playerObject->missileArray;
        while(missilePrint != NULL){
            missileSprite(missilePrint->x, missilePrint->y);
            missilePrint = missilePrint->next;
        }
        Meteor * meteorPrint = meteorArray;
        while(meteorPrint != NULL){
            meteorSprite(meteorPrint->x, meteorPrint->y);
            meteorPrint = meteorPrint->next;
        }

        //Read key bindings for next movement
        refresh();

        key = getch();
        if(key == 'q') break;
        if(key == playerObject->userBindings.left) playerObject->currentPosition.x--;
        if(key == playerObject->userBindings.right) playerObject->currentPosition.x++;
        if(key == playerObject->userBindings.shoot){
            Missile * newMissile = (Missile *)malloc(sizeof(Missile));
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
        //Logic for meteor generation
        int randomNumber = rand() % 1000;
        if(randomNumber > 980){
            Meteor * newMeteor = (Meteor *)malloc(sizeof(Meteor));
            newMeteor->x = rand() % maxWidth;
            newMeteor->y = 0;
            newMeteor->point = rand()%((20+1)-5) + 5;
            newMeteor->prev = NULL;
            if(meteorArray == NULL){
                newMeteor->next = NULL;
            } else {
                meteorArray->prev = newMeteor;
                newMeteor->next = meteorArray;
            }
            meteorArray = newMeteor;
        }
        //Logic for meteor out of bounds NEED TO MAKE THIS SLOWER
        Meteor * meteorMovementPlaceholder = meteorArray;
        while(meteorMovementPlaceholder != NULL){
            meteorMovementPlaceholder->y++;
            if(meteorMovementPlaceholder->y > maxHeight){
                if(meteorMovementPlaceholder->next == NULL && meteorMovementPlaceholder->prev == NULL){
                    //If it is the only object in the array.
                    meteorArray = NULL;
                    meteorMovementPlaceholder = NULL;
                    free(meteorMovementPlaceholder);
                } else {
                    // If it is the last object in the array.
                    meteorMovementPlaceholder = meteorMovementPlaceholder->prev;
                    free(meteorMovementPlaceholder->next);
                    meteorMovementPlaceholder->next = NULL;
                } 
            } else {
                meteorMovementPlaceholder = meteorMovementPlaceholder->next;
            }
        }
        //Logic for missile out of bounds
        Missile * movementPlaceholder = playerObject->missileArray;
        while(movementPlaceholder != NULL){
            movementPlaceholder->y--;
            if(movementPlaceholder->y < 0){
                if(movementPlaceholder->next == NULL && movementPlaceholder->prev == NULL){
                    //If it is the only object in the array.
                    playerObject->missileArray = NULL;
                    movementPlaceholder = NULL;
                    free(movementPlaceholder);
                } else {
                    // If it is the last object in the array.
                    movementPlaceholder = movementPlaceholder->prev;
                    free(movementPlaceholder->next);
                    movementPlaceholder->next = NULL;
                } 
            } else {
                movementPlaceholder = movementPlaceholder->next;
            }
        }
        currentTime = time(NULL);
    }
    return;
}

int main(){
	int maxHeight, maxWidth;


    currentTime = time(NULL);
    srand(time(NULL));


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
    Meteor * meteorArray = NULL;


    //Write main screen code bottom here.
    

    //Begin game.
    game(&testPlayer, meteorArray);

    
    //Cleanup
    endwin();
    return 0;

}
