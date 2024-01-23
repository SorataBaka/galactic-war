#include "endscreen.h"

void endScreen(int maxWidth, int maxHeight, Player * playerObject){
    erase();
    timeout(-1);
    mvprintw((maxHeight/2), (maxWidth/2)-5,"GAME OVER");
    mvprintw((maxHeight/2)+3, (maxWidth/2)-10,"FINAL SCORE: %6d", playerObject->points);
    mvprintw((maxHeight/2)+6, (maxWidth/2)-14,"Press any key to continue..");
    refresh();
    getch();
    return;

}
