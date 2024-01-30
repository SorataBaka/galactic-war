#include "game.h"
void game(Player * playerObject, Meteor * meteorArray) {
    int maxHeight, maxWidth;
    char key;
    erase();
    getmaxyx(stdscr, maxHeight, maxWidth);

    int laserActive = 0;
    unsigned long long timeSinceLastLaser = 0;

    
    Position startingPosition = {maxWidth/2, maxHeight};
    playerObject->streak = 0;
    playerObject->health = 100;
    playerObject->points = 0;
    playerObject->currentPosition = startingPosition;
    //Reset all arrays if its filled with something;
    while(playerObject->missileArray != NULL){
        Missile * temp = playerObject->missileArray;
        playerObject->missileArray = playerObject->missileArray->next;
        free(temp);
    }
    while(meteorArray != NULL){
        Meteor * temp = meteorArray;
        meteorArray = meteorArray->next;
        free(temp);
    }



    keyBindings(maxWidth, maxHeight, playerObject);
    while(1){
        timeout(200);
        erase();
        //Draw star background
        starBackground(maxWidth, maxHeight);

        //Print missiles
        Missile * missilePrint = playerObject->missileArray;
        int missileLength = 0;
        while(missilePrint != NULL){
            missileSprite(missilePrint->x, missilePrint->y);
            missilePrint = missilePrint->next;
            missileLength++;
        }
        //Print meteors
        Meteor * meteorPrint = meteorArray;
        int meteorLength = 0;
        while(meteorPrint != NULL){
            meteorSprite(meteorPrint->x, meteorPrint->y);
            meteorPrint = meteorPrint->next;
            meteorLength++;
        }
        //Draw laser if active

        if(laserActive) laserAnimation(playerObject->currentPosition.x, maxHeight);
        //For drawing the character sprite itself
	    charSprite(playerObject->currentPosition.x, playerObject->currentPosition.y);

        //Draw health and other informations
        mvprintw(0, 0, "Health: %3d\nPoints: %ld\nMissiles: %d/12\nStreak: %3d", playerObject->health, playerObject->points, 12-missileLength, playerObject->streak);
        mvprintw(maxHeight-2, maxWidth-30, "[%c] LASER : %s", playerObject->userBindings.laser,playerObject->streak >= 20 ? "READY": "NOT READY");
        mvprintw(maxHeight-3, maxWidth-30, "[%c] BOMB  : %s", playerObject->userBindings.bomb ,playerObject->streak >=30 ? "READY" : "NOT READY");

        refresh();

        //Read key bindings for next movement
        key = getch();
        if(key == 'q') break;
        if(key == playerObject->userBindings.left && playerObject->currentPosition.x > 5) playerObject->currentPosition.x = playerObject->currentPosition.x - MOVEMENT_STEP;
        if(key == playerObject->userBindings.right && playerObject->currentPosition.x < maxWidth-5) playerObject->currentPosition.x = playerObject->currentPosition.x + MOVEMENT_STEP;
        if(key == playerObject->userBindings.laser && laserActive == false && playerObject->streak >= 30){
            laserActive = true;
            playerObject->streak = 0;
            timeSinceLastLaser = getEpochMill();
        }
        if(key == playerObject->userBindings.bomb && playerObject->streak >= 50){
            playerObject->streak = 0;        
            while(meteorArray != NULL){
                playerObject->points = playerObject->points + meteorArray->point;
                Meteor * temp = meteorArray;
                meteorArray = meteorArray->next;
                free(temp);
            }
            continue;
        }
        if(key == playerObject->userBindings.shoot && missileLength < MAX_ACTIVE_MISSILE){
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
        if(getEpochMill() - timeSinceLastLaser >= 3000 && laserActive == true){
            timeSinceLastLaser = 0;
            laserActive = false;
        }
        //Logic for laser and meteor logic
        if(laserActive == true){
            Meteor * currentMeteor = meteorArray;
            while(currentMeteor != NULL){
                //Get distance using trig
                if(abs(currentMeteor->x - playerObject->currentPosition.x) <= 4){
                    playerObject->points = playerObject->points + currentMeteor->point;
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
        }


        //Logic for meteor generation
        int randomNumber = rand() % 1000;
        if(randomNumber > METEOR_SPAWN_TRESHOLD){
            Meteor * newMeteor = (Meteor *)malloc(sizeof(Meteor));
            newMeteor->x = (rand() % ((maxWidth-20+1))) + 20;
            newMeteor->y = 0;
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
                playerObject->streak = 0;
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
            if(currentTime - movementPlaceholder->timeSinceLastMove > 90){
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
                    playerObject->streak++;
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
                    playerObject->missileArray = currentMissile->next;
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