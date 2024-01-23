
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>

#include "definition.h"
#include "draw.h"
#include "util.h"


void game(Player * playerObject, Meteor * meteorArray) {
    int maxHeight, maxWidth;
    char key;
    erase();
    timeout(200);
    getmaxyx(stdscr, maxHeight, maxWidth);
    while(1){
        erase();
        //Draw star background
        starBackground(maxWidth, maxHeight);
        //Draw health
        char health[100];
        sprintf(health, "Health: %3d  Points: %ld", playerObject->health, playerObject->points);
        mvaddstr(0, 0, health);

        //For drawing the character sprite itself
	    charSprite(playerObject->currentPosition.x, playerObject->currentPosition.y);
        //Print missiles
        Missile * missilePrint = playerObject->missileArray;
        while(missilePrint != NULL){
            missileSprite(missilePrint->x, missilePrint->y);
            missilePrint = missilePrint->next;
        }
        //Print meteors
        Meteor * meteorPrint = meteorArray;
        while(meteorPrint != NULL){
            meteorSprite(meteorPrint->x, meteorPrint->y);
            meteorPrint = meteorPrint->next;
        }

        //Read key bindings for next movement
        refresh();

        key = getch();
        if(key == 'q') break;
        if(key == playerObject->userBindings.left) playerObject->currentPosition.x = playerObject->currentPosition.x - MOVEMENT_STEP;
        if(key == playerObject->userBindings.right) playerObject->currentPosition.x = playerObject->currentPosition.x + MOVEMENT_STEP;
        if(key == playerObject->userBindings.shoot){
            Missile * newMissile = (Missile *)malloc(sizeof(Missile));
            newMissile->x = playerObject->currentPosition.x;
            newMissile->y = maxHeight-2;
            newMissile->timeSinceLastMove = getEpochMill();
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
        if(randomNumber > METEOR_SPAWN_TRESHOLD){
            Meteor * newMeteor = (Meteor *)malloc(sizeof(Meteor));
            newMeteor->x = rand() % maxWidth;
            newMeteor->y = 3;
            newMeteor->point = rand()%((20+1)-5) + 5;
            newMeteor->prev = NULL;
            newMeteor->timeSinceLastMove = getEpochMill();
            if(meteorArray == NULL){
                newMeteor->next = NULL;
            } else {
                meteorArray->prev = newMeteor;
                newMeteor->next = meteorArray;
            }
            meteorArray = newMeteor;
        }
        //Logic for meteor out of bounds
        Meteor * meteorMovementPlaceholder = meteorArray;
        while(meteorMovementPlaceholder != NULL){
            unsigned long long currentTime = getEpochMill();
            if(currentTime - meteorMovementPlaceholder->timeSinceLastMove > 500){
                meteorMovementPlaceholder->y++;
                meteorMovementPlaceholder->timeSinceLastMove = currentTime;
            }
            
            if(meteorMovementPlaceholder->y > maxHeight - SCREEN_BOUND_MAX){
                playerObject->health = playerObject->health - 10;
                if(playerObject->health <= 0) goto DONE;
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
            unsigned long long currentTime = getEpochMill();
            if(currentTime - movementPlaceholder->timeSinceLastMove > 100){
                movementPlaceholder->y--;
                movementPlaceholder->timeSinceLastMove = currentTime;
            }
            if(movementPlaceholder->y < SCREEN_BOUND_MIN){
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
        //Logic for missile and meteor collision
        Missile * currentMissile = playerObject->missileArray;
        while(currentMissile != NULL){
            int missileUpdate = 0;
            Meteor * currentMeteor = meteorArray;
            while(currentMeteor != NULL){
                //Get distance using trig
                double xDelta = abs(currentMeteor->x - currentMissile->x);
                double yDelta = abs(currentMeteor->y - currentMissile->y);
                double distance = sqrt(pow(xDelta, 2)+pow(yDelta, 2));
                if((int)distance <= 5){
                    playerObject->points = playerObject->points + currentMeteor->point;
                    missileUpdate = 1;
                    if(currentMeteor->prev == NULL && currentMeteor->next == NULL){
                        //When it is the only element in the array.
                        free(currentMeteor);
                        currentMeteor = NULL;
                        meteorArray = NULL;
                    } else if(currentMeteor->next == NULL && currentMeteor->prev != NULL){
                        //When it is the last element in the array.
                        currentMeteor = currentMeteor->prev;
                        free(currentMeteor->next);
                        currentMeteor->next = NULL;
                    } else if(currentMeteor->next != NULL && currentMeteor->prev == NULL){
                        //When it is the first element in the array.
                        meteorArray = currentMeteor->next;
                        meteorArray->prev = NULL;
                        free(currentMeteor);
                        currentMeteor = meteorArray;
                    } else {
                        //If it is somewhere in the middle of the array.
                        currentMeteor->prev->next = currentMeteor->next;
                        currentMeteor->next->prev = currentMeteor->prev;
                        Meteor * temp = currentMeteor->next;
                        free(currentMeteor);
                        currentMeteor = temp;
                    }
                } else {
                    currentMeteor = currentMeteor->next;
                }
            }
            if(missileUpdate){
                //Remove from array (MISSILE)
                if(currentMissile->prev == NULL && currentMissile->next == NULL){
                    //When it is the first element in the array.
                    free(currentMissile);
                    currentMissile = NULL;
                    playerObject->missileArray = NULL;
                } else if(currentMissile->next == NULL && currentMissile->prev != NULL){
                    //If it is the last element in the array.
                    currentMissile = currentMissile->prev;
                    free(currentMissile->next);
                    currentMissile->next = NULL;
                } else if(currentMissile->next != NULL && currentMissile->prev == NULL){
                    //If it is the first element in the array.
                    playerObject->missileArray = movementPlaceholder->next;
                    playerObject->missileArray->prev = NULL;
                    free(currentMissile);
                    currentMissile = playerObject->missileArray;
                } else {
                    //If it is somewhere in the middle of the array.
                    currentMissile->prev->next = currentMissile->next;
                    currentMissile->next->prev = currentMissile->prev;
                    Missile * temp = currentMissile->next;
                    free(currentMissile);
                    currentMissile = temp;
                }
            } else {
                currentMissile = currentMissile->next;
            }
        }
    }
DONE:
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
    Meteor * meteorArray = NULL;


    //Write main screen code bottom here.
    

    //Begin game.
    game(&testPlayer, meteorArray);

    
    //Cleanup
    endwin();
    return 0;

}
