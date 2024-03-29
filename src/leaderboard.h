#ifndef LEADERBOARD_H
#define LEADERBOARD_H
#include "definition.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

typedef struct Entry {
    char username[20];
    int score;
} Entry;

void writeLeaderboard(Player * playerObject);
void displayLeaderboard(int maxWidth, int maxHeight);

#endif