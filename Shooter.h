#pragma once
#ifndef SHOOTER_H
#define SHOOTER_H

#include "BasketballPlayer.h"

using namespace std;
using std::string;

class Shooter : public BasketballPlayer{
    public:
        Shooter();
        Shooter(string, int, int, int, int);
        int attack();
        bool defend();
        int specialMove();
        void rest();
        void levelUp();
        void print();
        void save(const string& filename);
        void load(const string& filename);
        ~Shooter();
        int getStamina() const { return stamina; }
    private:
        int streakChance;
        int madeShots;
};

#endif