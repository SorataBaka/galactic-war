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