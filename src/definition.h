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

typedef struct {
    Position missilePosition;
} Missile;

typedef struct {
    char username[20];
    int health;
    Bindings userBindings;
    Position currentPosition;
    Missile * missileArray;
    long int points;
} Player;


typedef struct {
    Position meteorPosition;
    int point;
    int movementCountdown;
} Meteor;

#endif