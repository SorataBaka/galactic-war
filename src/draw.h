#ifndef DRAW_H
#define DRAW_H
#include <stdlib.h>
#include <ncurses.h>
#include "definition.h"
#include <stdio.h>

void charSprite(int x, int y);
void missileSprite(int x, int y);
void meteorSprite(int x, int y);
void starBackground(int maxWidth, int maxHeight);
void keyBindings(int maxWidth, int maxHeight, Player * playerObject);
void laserAnimation(int x, int maxHeight);
#endif