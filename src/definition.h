#ifndef DEFINITION_H
#define DEFINITION_H


#define true 1
#define false 0

typedef struct {
    char left;
    char right;
    char shoot;
} Bindings;

typedef struct {
    int x;
    int y;
} Position;

struct Missile {
    int x;
    int y;
    struct Missile * next;
};

typedef struct {
    char username[20];
    int health;
    Bindings userBindings;
    Position currentPosition;
    struct Missile * missileArray;
    long int points;
} Player;


typedef struct {
    Position meteorPosition;
    int point;
    int movementCountdown;
} Meteor;

#endif