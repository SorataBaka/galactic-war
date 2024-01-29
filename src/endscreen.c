#include "endscreen.h"

void endScreen(int maxWidth, int maxHeight, Player * playerObject){
    int xCenter = maxWidth/2;
    int yCenter = maxHeight/2;
    erase();
    timeout(-1);
    mvprintw((yCenter), (xCenter)-5,"GAME OVER");
    mvprintw((yCenter)+3, (xCenter)-10,"FINAL SCORE: %6ld", playerObject->points);
    mvprintw((yCenter)+6, (xCenter)-14,"Press any key to continue..");
    refresh();
    getch();

    erase();
    mvprintw(yCenter-1, xCenter-12, "Please input your name:");
    refresh();
    move(yCenter, xCenter-10);
    nodelay(stdscr, FALSE);
	echo();
    scanw("%19s", playerObject->username);
    refresh();
    noecho();
    nodelay(stdscr, TRUE);
    


    return;

}
