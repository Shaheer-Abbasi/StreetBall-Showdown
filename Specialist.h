#pragma once
#ifndef SPECIALIST_H
#define SPECIALIST_H

#include "BasketballPlayer.h"

using namespace std;
using std::string;
 
class Specialist : public BasketballPlayer{
    public:
        Specialist();
        Specialist(string, int, int, int, int);
        int attack();
        bool defend();
        int specialMove();
        void rest();
        void levelUp();
        void print();
        void save(const string& filename);
        void load(const string& filename);
        ~Specialist();
        int getStamina() const { return stamina; }
    private:
        int ankleBreakerChance;
};

#endif