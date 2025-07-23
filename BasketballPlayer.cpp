#include "BasketballPlayer.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
using std::string;

BasketballPlayer::BasketballPlayer(){
    name = "";
    stamina = 0;
    level = 0;
    xp = 0;
}

BasketballPlayer::BasketballPlayer(string name, int stamina, int level, int xp){
    this->name = name;
    this->stamina = stamina;
    this->level = level;
    this->xp = xp;
}

void BasketballPlayer::gainXP(int amt){
    xp += amt;
    if(xp >= level * 50){
        level++;
        cout << "You have reached level " << level << "!" << endl;
        levelUp();
    }
}

void BasketballPlayer::print(){
    cout << "Name is " << name << endl;
    cout << "Stamina is " << stamina << endl;
    cout << "Level is " << level << endl;
    cout << "XP is " << xp << endl;
}

BasketballPlayer::~BasketballPlayer(){}