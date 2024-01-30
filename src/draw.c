#include "draw.h"
void charSprite(int x, int y){
  mvaddstr(y-6, x-5, "    ww   ");
  mvaddstr(y-5, x-5, " v  ||  v");
  mvaddstr(y-4, x-5, " | #### |");
  mvaddstr(y-3, x-5, " ## ## ## ");
  mvaddstr(y-2, x-5, "#W  ##  W#");
  return;
}
void missileSprite(int x, int y){
  mvaddstr(y, x, "^");
  return;
}

void meteorSprite(int x, int y){
  mvaddstr(y, x-2,   " **** ");
  mvaddstr(y+1, x-2, "******");
  mvaddstr(y+2, x-2, " ****");
  return;
}
void starBackground(int maxWidth, int maxHeight){
  for (int i = 0; i < 5; ++i) {
    int x = rand() % maxWidth;
    int y = rand() % maxHeight;
    mvaddch(y, x, '.');
  }
  return;
}
void keyBindings(int maxWidth, int maxHeight, Player * playerObject){
  int yCenter = maxHeight/2;
  int xCenter = maxWidth/2;

  mvprintw(yCenter-1, xCenter-10, "[%c] move left", playerObject->userBindings.left);
  mvprintw(yCenter, xCenter-10, "[%c] move right", playerObject->userBindings.right);
  mvprintw(yCenter+1, xCenter-10, "[%c] fire missile", playerObject->userBindings.shoot);
  mvprintw(yCenter+2, xCenter-10, "[%c] Activate Laser", playerObject->userBindings.laser);
  mvprintw(yCenter+3, xCenter-10, "[%c] Detonate Bomb", playerObject->userBindings.bomb);
  mvprintw(yCenter+4, xCenter-10, "[Q] Quit game");
  mvaddstr(yCenter+6, xCenter-13, "Press any key to continue.");

  timeout(-1);
  getch();
  return;
}

void laserAnimation(int x, int maxHeight){
  for(int i = 0 ; i <= maxHeight; i++){
    mvaddstr(i, x-4, "-=+#+=-");
  }
  return;
}