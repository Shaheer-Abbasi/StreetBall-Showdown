#ifndef RAND_H
#define RAND_H

#include <random>

using namespace std;

inline bool roll(int percent){
    random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> dist(1,100);
    return dist(gen) <= percent;
}

#endif