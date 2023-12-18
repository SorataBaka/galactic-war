#ifndef DEFINITON_H
#define DEFINITON_H
#define true 1
#define false 0
// Opposites equal to 9
typedef enum {
    up = 1,
    left = 2,
    up_left = 3,
    up_right = 4,
    down_left = 5, 
    down_right = 6,
    right = 7,
    down = 8
} Trajectory;

typedef struct {
    char up;
    char down;
    char left;
    char right;
    char shoot;
} Bindings;

typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    int id;
    char username[10];
    int score;
    Bindings user_bindings;
    Position pos;
    Trajectory trajectory;
} Player;
#endif