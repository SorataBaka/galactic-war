#include "util.h"
unsigned long long getEpochMill(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (unsigned long long)(tv.tv_sec)*1000 + (unsigned long long)(tv.tv_usec)/1000;
}