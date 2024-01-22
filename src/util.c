#include "util.h"
long int diffMillisecond(struct timeval before, struct timeval after){
    return (long int)(after.tv_sec - after.tv_sec) * 1000.0f + (after.tv_usec - before.tv_usec) / 1000.0f;
}