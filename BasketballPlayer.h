#pragma once
#ifndef BASKETBALLPLAYER_H
#define BASKETBALLPLAYER_H

#include <string>

using namespace std;
using std::string;

class BasketballPlayer {
    public:
        BasketballPlayer();
        BasketballPlayer(string name, int stamina, int level, int xp);
        virtual int attack() = 0;
        virtual bool defend() = 0;
        virtual int specialMove() = 0;
        void gainXP(int amt);
        virtual void levelUp() = 0;
        virtual void rest() = 0;
        virtual void save(const string &filename) = 0;
        virtual void load(const string &filename) = 0;
        virtual void print();
        virtual ~BasketballPlayer();
        int getStamina() const { return stamina; }
    protected:
        string name;
        int stamina;
        int level;
        int xp;
};

#endif