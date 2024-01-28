#include "draw.h"
void charSprite(int x, int y){
  mvaddstr(y-5, x-5, "    ww   ");
  mvaddstr(y-4, x-5, " v  ||  v");
  mvaddstr(y-3, x-5, " | #### |");
  mvaddstr(y-2, x-5, " ## ## ## ");
  mvaddstr(y-1, x-5, "#W  ##  W#");
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
  char leftBindingText[20];
  char rightBindingText[20];
  char fireBindingText[20];
  sprintf(leftBindingText, "[%c] move left", playerObject->userBindings.left);
  sprintf(rightBindingText, "[%c] move right", playerObject->userBindings.right);
  sprintf(fireBindingText, "[%c] fire missile", playerObject->userBindings.shoot);

  mvaddstr(yCenter-1, xCenter-10, leftBindingText);
  mvaddstr(yCenter, xCenter-10, rightBindingText);
  mvaddstr(yCenter+1, xCenter-10, fireBindingText);
  mvaddstr(yCenter+4, xCenter-13, "Press any key to continue");

  timeout(-1);
  getch();
  return;
}
