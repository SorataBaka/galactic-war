#ifndef MAINSCREEN_H
#define MAINSCREEN_H
#include "game.h"
#include "endscreen.h"
#include "definition.h"
#include "leaderboard.h"
#include "settings.h"
#include <ncurses.h>
#include "draw.h"
void mainScreen(Player * playerObject, Meteor * meteorArray,  int maxHeight, int maxWidth);
#endif