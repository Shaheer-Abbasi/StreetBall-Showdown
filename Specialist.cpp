#include "Specialist.h"
#include "Rand.h"
#include <iostream>
#include <fstream>
#include <random>

using namespace std;
using std::string;

Specialist::Specialist() : BasketballPlayer("Player", 105, 0, 0){
    ankleBreakerChance = 1;
}

Specialist::Specialist(string name, int stamina, int level, int xp, int ankleBreakerChance) : BasketballPlayer(name, stamina, level, xp) {
    this->ankleBreakerChance = ankleBreakerChance;
}

int Specialist::attack(){
    stamina -= 5;

    bool shotMade;
    
    bool hitCrossOver = roll(ankleBreakerChance);
    if(hitCrossOver){
        cout << "What a crossover!" << endl;
        shotMade = true;
    } else {
        shotMade = roll(80);
    }

    if(shotMade){
        cout << name << " banked that shot in for 2 points!" << endl;
        return 2;
    } else {
        cout << "Uh-oh, " << name << " missed that one!" << endl;
        return 0;
    }
}

int Specialist::specialMove(){
    stamina -= 10;
    bool shotMade = roll(99);
    if(shotMade){
        cout << name << " put him on skates! And hit the step back 3!" << endl;
        return 3;
    } else {
        cout << "Oh no!" << name << " dribilled!" << endl;
        return 0;
    }
}

bool Specialist::defend(){
    stamina -= 15;
    bool steal = roll(30);
    if(steal){
        cout << "Woah! " << name << " stole the opponents ball!" << endl;
        return true;
    } else {
        cout << "No steal this time." << endl;
    }
    return false;
}

void Specialist::rest(){
    cout << name << " took a breather to recovered some stamina" << endl;
    stamina += 7;
}

void Specialist::levelUp(){
    stamina = 105;
    ankleBreakerChance++;
    if(ankleBreakerChance > 10){
        ankleBreakerChance = 10;
    }
    cout << "Ankle-Breaker chance increased to " << ankleBreakerChance << "%!" << endl;
}

void Specialist::print() {
    cout << "Class: Specialist" << endl;
    BasketballPlayer::print();
    cout << "Ankle Breaker Chance: " << ankleBreakerChance << "%" << endl;
}

//to-do: save and load functions
void Specialist::save(const string& filename) {
    ofstream output;
    output.open(filename);
    if(output.is_open()){
        output << "Specialist" << endl;
        output << name << endl;
        output << stamina << endl;
        output << level << endl;
        output << xp << endl;
        output << ankleBreakerChance << endl;
        output.close();
    }
}

void Specialist::load(const string& filename) {
    ifstream input;
    input.open(filename);
    if(input.is_open()){
        string type;
        getline(input, type);
        getline(input, name);
        input >> stamina >> level >> xp >> ankleBreakerChance;
        stamina = 105;
        level = 1;
        xp = 0;
        ankleBreakerChance = 4;
        input.close();
    }
}

Specialist::~Specialist(){}