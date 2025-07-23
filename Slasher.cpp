#include "Slasher.h"
#include "Rand.h"
#include <iostream>
#include <fstream>
#include <random>

using namespace std;
using std::string;

Slasher::Slasher() : BasketballPlayer("Player", 110, 0, 0){
    andOneChance = 1;
}

Slasher::Slasher(string name, int stamina, int level, int xp, int andOneChance) : BasketballPlayer(name, stamina, level, xp) {
    this->andOneChance = andOneChance;
}

int Slasher::attack(){
    stamina -= 10;

    bool shotMade = roll(85);
    
    if(shotMade){
        bool getFouled = roll(andOneChance);
        if(getFouled) {
            cout << name << " finished the lay and went to the line for an extra point!" << endl;
            return 3;
        } else {
            cout << name << " drove past the opponent and made the lay for 2 points! " << endl;
            return 2;
        }   
    } else {
        cout << "Uh-oh, " << name << " missed that one!" << endl;
        return 0;
    }
}

int Slasher::specialMove(){
    stamina -= 15;

    bool shotMade = roll(95);

    if(shotMade){
        andOneChance = roll(10);
        if(andOneChance) {
            cout << name << " threw down a tough hammer on the opponent and went to the line!" << endl;
            return 3;
        } else {
            cout << "What a dunk!" << endl;
            return 2;
        }   
    } else {
        cout << "Such an unfortunate miss!" << endl;
        return 0;
    }
}

bool Slasher::defend(){
    stamina -= 15;
    bool steal = roll(5);
    if(steal){
        cout << "Woah! " << name << " stole the opponents ball!" << endl;
        return true;
    } else {
        cout << "No steal this time." << endl;
    }
    return false;
}

void Slasher::rest(){
    cout << name << " took a breather to recovered some stamina" << endl;
    stamina += 5;
}

void Slasher::levelUp(){
    stamina = 110;
    andOneChance++;
    if(andOneChance > 10){
        andOneChance = 10;
    }
    cout << "And-One chance increased to " << andOneChance << "%!" << endl;
}

void Slasher::print() {
    cout << "Class: Slasher" << endl;
    BasketballPlayer::print();
    cout << "And-One Chance: " << andOneChance << "%" << endl;
}

//to-do: save and load functions
void Slasher::save(const string& filename) {
    ofstream output;
    output.open(filename);
    if(output.is_open()){
        output << "Slasher" << endl;
        output << name << endl;
        output << stamina << endl;
        output << level << endl;
        output << xp << endl;
        output << andOneChance << endl;
        output.close();
    }
}

void Slasher::load(const string& filename) {
    ifstream input;
    input.open(filename);
    if(input.is_open()){
        string type;
        getline(input, type);
        getline(input, name);
        input >> stamina >> level >> xp >> andOneChance;
        stamina = 100;
        level = 1;
        xp = 0;
        andOneChance = 4;
        input.close();
    }
}

Slasher::~Slasher(){}