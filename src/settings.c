#include "settings.h"
void settingsPage(int maxWidth, int maxHeight, Player * playerObject){
    timeout(-1);
    int xCenter = maxWidth/2;
    int yCenter = maxHeight/2;
    Bindings defaultBindings = {
        'a', 'd', ' '
    };
    while(true){
        erase();
        char leftKeyString[25];
        char rightKeyString[25];
        char fireKeyString[25];
        sprintf(leftKeyString, "[%c] Left Movement Key", playerObject->userBindings.left);
        sprintf(rightKeyString, "[%c] Right Movement Key", playerObject->userBindings.right);
        sprintf(fireKeyString, "[%c] Fire Missile Key", playerObject->userBindings.shoot);
        starBackground(maxWidth, maxHeight);
        mvaddstr(yCenter-5, xCenter-5, "SETTINGS");
        mvaddstr(yCenter-3, xCenter-12, leftKeyString);
        mvaddstr(yCenter-2, xCenter-12, rightKeyString);
        mvaddstr(yCenter-1, xCenter-12, fireKeyString);
        
        mvaddstr(yCenter+1, xCenter-17, "Press the key you want to change!");
        mvaddstr(yCenter+4, xCenter-15, "Press [W] to reset bindings.");
        mvaddstr(yCenter+5, xCenter-10, "Press [Q] to exit.");

        char exitkey = getch();
        erase();
        if(exitkey == 'q') break;
        if(exitkey == 'w') {
            playerObject->userBindings = defaultBindings;
            continue;
        } 
        if(exitkey == playerObject->userBindings.left){
            mvaddstr(yCenter, xCenter-20, "Press the key you want to bind LEFT to!");
            exitkey = getch();
            if(exitkey == 'q' || exitkey == 'w') continue;
            playerObject->userBindings.left = exitkey;
        }else if(exitkey == playerObject->userBindings.right){
            mvaddstr(yCenter, xCenter-21, "Press the key you want to bind RIGHT to!");
            exitkey = getch();
            if(exitkey == 'q' || exitkey == 'w') continue;
            playerObject->userBindings.right = exitkey;
        }else if(exitkey == playerObject->userBindings.shoot){
            mvaddstr(yCenter, xCenter-21, "Press the key you want to bind SHOOT to!");
            exitkey = getch();
            if(exitkey == 'q' || exitkey == 'w') continue;
            playerObject->userBindings.shoot = exitkey;
        } else {
            continue;
        }
    }
    return;
}