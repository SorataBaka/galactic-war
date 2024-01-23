#ifndef DRAW_H
#define DRAW_H
#include <stdlib.h>
#include <ncurses.h>
void charSprite(int x, int y);
void missileSprite(int x, int y);
void meteorSprite(int x, int y);
void starBackground(int maxWidth, int maxHeight);
#endif