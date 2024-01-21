#include "util.h"
#include "definition.h"
void spliceMissile(Player *playerObject, int targetIndex){
    if(playerObject->missileArray != NULL && targetIndex == 0){
        free(playerObject->missileArray);
        playerObject->missileArray = NULL;
    }
}