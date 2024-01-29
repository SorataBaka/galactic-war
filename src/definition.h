#ifndef DEFINITION_H
#define DEFINITION_H


#define true 1
#define false 0

#define MOVEMENT_STEP 3
#define METEOR_SPAWN_TRESHOLD 920
#define SCREEN_BOUND_MIN 3
#define SCREEN_BOUND_MAX 3

typedef struct {
    char left;
    char right;
    char shoot;
} Bindings;

typedef struct {
    int x;
    int y;
} Position;

typedef struct Missile {
    int x;
    int y;
    unsigned long long timeSinceLastMove;
    struct Missile * next;
    struct Missile * prev;
} Missile;

typedef struct Meteor {
    int x;
    int y;
    unsigned long long timeSinceLastMove;
    int point;
    struct Meteor * next;
    struct Meteor * prev;
    
} Meteor;

typedef struct {
    char username[20];
    int health;
    Bindings userBindings;
    Position currentPosition;
    struct Missile * missileArray;
    long int points;
} Player;


#endif