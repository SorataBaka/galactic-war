#include "definition.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

int main(){
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
    
}
