#include "draw.h"
#include <ncurses.h>
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
}
