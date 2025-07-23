#pragma once
#ifndef SLASHER_H
#define SLASHER_H

#include "BasketballPlayer.h"

using namespace std;
using std::string;

class Slasher : public BasketballPlayer{
    public:
        Slasher();
        Slasher(string, int, int, int, int);
        int attack();
        bool defend();
        int specialMove();
        void rest();
        void levelUp();
        void print();
        void save(const string& filename);
        void load(const string& filename);
        ~Slasher();
        int getStamina() const { return stamina; }
    private:
        int andOneChance;
};

#endif