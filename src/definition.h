#ifndef DEFINITION_H
#define DEFINITION_H


#define true 1
#define false 0

#define MOVEMENT_STEP 3
#define METEOR_SPAWN_TRESHOLD 900 // Min of 0 and max of 1000. Lower number, higeher spawn threshold
#define SCREEN_BOUND_MIN 0
#define SCREEN_BOUND_MAX 6
#define MAX_ACTIVE_MISSILE 12
#define BOMB_STREAK_MIN 50
#define LASER_STREAK_MIN 30
#define LASER_TIME_LEN 3000 //In milliseconds
#define METEOR_MOVEMENT_SPEED 500
#define MISSILE_MOVEMENT_SPEED 90
#define COLLISION_BOUNDARY 5

typedef struct {
    char left;
    char right;
    char shoot;
    char bomb;
    char laser;
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
    int streak;
} Player;


#endif