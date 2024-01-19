#include "draw.h"
#include <ncurses.h>
void charSprite(int x, int y){
  mvaddstr(y-5, x-5, "    ww   ");
  mvaddstr(y-4, x-5, " v  ||  v");
  mvaddstr(y-3, x-5, " | #### |");
  mvaddstr(y-2, x-5, " ## ## ## ");
  mvaddstr(y-1, x-5, "##  ##  ##");
  return;
}
