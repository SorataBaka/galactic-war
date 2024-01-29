#ifndef UTIL_H
#define UTIL_H
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>

unsigned long long getEpochMill();
char  * getString(int x, int y, int length);
#endif