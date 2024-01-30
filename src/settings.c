#include "settings.h"
void settingsPage(int maxWidth, int maxHeight, Player * playerObject){
    timeout(-1);
    int xCenter = maxWidth/2;
    int yCenter = maxHeight/2;
    Bindings defaultBindings = {
        'a', 'd', ' ', 'x', 'c'
    };
    while(true){
        erase();
        starBackground(maxWidth, maxHeight);
        mvaddstr(yCenter-5, xCenter-5, "SETTINGS");
        mvprintw(yCenter-3, xCenter-12, "[%c] Left Movement Key", playerObject->userBindings.left);
        mvprintw(yCenter-2, xCenter-12,  "[%c] Right Movement Key", playerObject->userBindings.right);
        mvprintw(yCenter-1, xCenter-12, "[%c] Fire Missile Key", playerObject->userBindings.shoot);
        mvprintw(yCenter, xCenter-12, "[%c] Activate Laser Key", playerObject->userBindings.laser);
        mvprintw(yCenter+1, xCenter-12, "[%c] Detonate Bomb Key", playerObject->userBindings.bomb);
        
        mvaddstr(yCenter+3, xCenter-17, "Press the key you want to change!");
        mvaddstr(yCenter+5, xCenter-15, "Press [W] to reset bindings.");
        mvaddstr(yCenter+6, xCenter-10, "Press [Q] to exit.");

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
        }else if(exitkey == playerObject->userBindings.laser){
            mvaddstr(yCenter, xCenter-21, "Press the key you want to bind LASER to!");
            exitkey = getch();
            if(exitkey == 'q' || exitkey == 'w') continue;
            playerObject->userBindings.laser = exitkey;
        }else if(exitkey == playerObject->userBindings.bomb){
            mvaddstr(yCenter, xCenter-21, "Press the key you want to bind BOMB to!");
            exitkey = getch();
            if(exitkey == 'q' || exitkey == 'w') continue;
            playerObject->userBindings.bomb = exitkey;
        } else {
            continue;
        }
    }
    return;
}