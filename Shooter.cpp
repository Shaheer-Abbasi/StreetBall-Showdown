#include "Shooter.h"
#include "Rand.h"
#include <iostream>
#include <fstream>
#include <random>

using namespace std;
using std::string;

Shooter::Shooter() : BasketballPlayer("Player", 100, 0, 0){
    madeShots = 0;
    streakChance = 1;
}

Shooter::Shooter(string name, int stamina, int level, int xp, int streakChance) : BasketballPlayer(name, stamina, level, xp) {
    madeShots = 0;
    this->streakChance = streakChance;
}

int Shooter::attack(){
    stamina -= 5;

    bool shotMade;
    if(madeShots < 1){
        shotMade = roll(70);
    } else {
        int improvedRate = 70 + (madeShots * streakChance);
        if(improvedRate > 85){
            shotMade = roll(85);
        } else {
            shotMade = roll(improvedRate);
        }
    }
    
    if(shotMade){
        cout << name << " knocked down a pull-up jumper for 2 points!" << endl;
        madeShots++;
        return 2;
    } else {
        cout << "Uh-oh, " << name << " missed that one!" << endl;
        madeShots = 0;
        return 0;
    }
}

int Shooter::specialMove(){
    stamina -= 15;
    bool shotMade = roll(90);
    if(shotMade){
        cout << "Bang! Bang!" << name << " swished from way downtown for 3 points!" << endl;
        madeShots++;
        return 3;
    } else {
        cout << "No! " << name << ", that is not the shot!" << endl;
        madeShots = 0;
        return 0;
    }
}

bool Shooter::defend(){
    stamina -= 10;
    bool steal = roll(10);
    if(steal){
        cout << "Woah! " << name << " stole the opponents ball!" << endl;
        return true;
    } else {
        cout << "No steal this time." << endl;
    }
    return false;
}

void Shooter::rest(){
    cout << name << " took a breather to recovered some stamina" << endl;
    stamina += 10;
}

void Shooter::levelUp(){
    stamina = 100;
    streakChance++;
    if(streakChance > 10){
        streakChance = 10;
    }
    cout << "Streak boost increased to " << streakChance << "%!" << endl;
}

void Shooter::print() {
    cout << "Class: Shooter" << endl;
    BasketballPlayer::print(); // call base class
    cout << "Streak Boost Chance: " << streakChance << "%" << endl;
    cout << "Current Streak: " << madeShots << " made shot(s)" << endl;
}

//to-do: save and load functions
void Shooter::save(const string& filename) {
    ofstream output;
    output.open(filename);
    if(output.is_open()){
        output << "Shooter" << endl;
        output << name << endl;
        output << stamina << endl;
        output << level << endl;
        output << xp << endl;
        output << streakChance << endl;
        output.close();
    }
}

void Shooter::load(const string& filename) {
    ifstream input;
    input.open(filename);
    if(input.is_open()){
        string type;
        getline(input, type);
        getline(input, name);
        input >> stamina >> level >> xp >> streakChance;
        stamina = 110;
        level = 1;
        xp = 0;
        streakChance = 4;
        input.close();
    }
}

Shooter::~Shooter(){}