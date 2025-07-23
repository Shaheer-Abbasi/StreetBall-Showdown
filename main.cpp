#include "BasketballPlayer.cpp"
#include "Shooter.cpp"
#include "Slasher.cpp"
#include "Specialist.cpp"
#include <iostream>
#include <fstream>

using namespace std;


/// Generates a random opponent based on the current round number.
/// The current round number in the tournament.
/// return A pointer to a BasketballPlayer object representing the opponent.
BasketballPlayer* generateOpponent(int round) {
    string name = "Opponent" + to_string(round);
    int type = rand() % 3;
    int stamina = rand() % 16 + 85;
    int xp = 0;
    int level = 1;

    if (type == 0) return new Shooter(name, stamina, level, xp, 1);       
    if (type == 1) return new Slasher(name, stamina, level, xp, 2);      
    return new Specialist(name, stamina, level, xp, 2);                  
}


/// Runs a match between the player and an opponent. The match consists of a series of turns where each player takes actions.
/// The player can choose to attack, use a special move, defend, or rest. The opponent's actions are determined randomly.
/// The match continues until either the player or opponent runs out of stamina or the maximum number of turns is reached.
/// The player gains experience points based on their performance in the match. If the match ends in a tie, overtime rounds are played.
/// The player can also choose to save their progress after each round of the tournament.
bool runMatch(BasketballPlayer* Player, BasketballPlayer* Opponent) {
    int playerScore = 0;
    int opponentScore = 0;
    const int maxTurns = 20;
    bool skipOpponentTurn = false;

    for (int turn = 1; turn <= maxTurns; ++turn) {
        cout << "\n--- Turn " << turn << " ---" << endl;

        if (turn % 2 == 1) {
            cout << "Your move!" << endl;
            cout << "1: Attack\n2: Special Move\n3: Steal On Next Turn\n4: Rest\nChoose: ";
            int choice;
            cin >> choice;

            int points = 0;
            switch (choice) {
                case 1: points = Player->attack(); break;
                case 2: points = Player->specialMove(); break;
                case 3: 
                    if(Player->defend()){
                        skipOpponentTurn = true;
                    }
                    break;
                case 4: Player->rest(); break;
                default: cout << "Invalid move.\n"; continue;
            }

            playerScore += points;
            Player->gainXP(points);

            if (Player->getStamina() <= 0) {
                cout << " You are too exhausted to continue!\n";
                cout << "You lose the match.\n";
                break;
            }
        } else {
            if(skipOpponentTurn){
                cout << "Opponent lost their turn due to your defense!" << endl;
                skipOpponentTurn = false;
            } else {
                cout << "Opponent is making a move..." << endl;
                int aiMove = rand() % 3;
                int points = 0;

                switch (aiMove) {
                    case 0: points = Opponent->attack(); break;
                    case 1: points = Opponent->specialMove(); break;
                    case 2: Opponent->rest(); break;
            }

            opponentScore += points;
            Opponent->gainXP(points);
            }
        }

        cout << "Score Update - You: " << playerScore << " | Opponent: " << opponentScore << "\n";
        cout << "Your stamina: " << Player->getStamina() << "\n";
    }

    cout << "\n--- Game Over ---" << endl;
    cout << "Final Score:\nYou: " << playerScore << " | Opponent: " << opponentScore << endl;

    if (playerScore > opponentScore) {
        cout << "You win the match!" << endl;
        Player->gainXP(100); 
        return true;
    } else if (playerScore < opponentScore) {
        cout << "You lost the match." << endl;
        Player->gainXP(30); 
        return false;
    } else {
        cout << "\nThe game is tied at " << playerScore << " - entering OVERTIME!\n";

        const int maxOTRounds = 3;
        int otRound = 1;

        while (playerScore == opponentScore && otRound <= maxOTRounds) {
            cout << "\n--- Overtime Round " << otRound << " ---" << endl;

            cout << "Your overtime move!" << endl;
            cout << "1: Attack\n2: Special Move\n3: Try To Steal On Opponent's Possession\n4: Rest\nChoose: ";
            int choice;
            cin >> choice;

            int points = 0;
            switch (choice) {
                case 1: points = Player->attack(); break;
                case 2: points = Player->specialMove(); break;
                case 3: Player->defend(); break;
                case 4: Player->rest(); break;
                default: cout << "Invalid move.\n"; continue;
            }

            playerScore += points;
            Player->gainXP(points);

            cout << "Opponent takes an overtime turn...\n";
            int aiMove = rand() % 3;
            int aiPoints = 0;
            switch (aiMove) {
                case 0: aiPoints = Opponent->attack(); break;
                case 1: aiPoints = Opponent->specialMove(); break;
                case 2: Opponent->rest(); break;
            }

            opponentScore += aiPoints;

            cout << "Score after OT Round " << otRound << " - You: " << playerScore << " | Opponent: " << opponentScore << "\n";
            otRound++;
        }

        if (playerScore == opponentScore) {
            cout << "\nAfter 3 overtime rounds, it's still tied...\n";
            cout << "Performing a coin toss to determine the winner...\n";

            bool coinToss = rand() % 2;
            if (coinToss) {
                cout << "The coin favored you!" << endl;
                playerScore++;
            } else {
                cout << "The coin favored your opponent..." << endl;
                opponentScore++;
            }
        }

        cout << "\nOvertime complete!\n";
    }
    return true;
}

/// Runs the tournament for the player. The tournament consists of 5 rounds, and the player must win each round to advance.
/// After each round, the player has the option to save their progress. If the player loses a match, they are eliminated from the tournament.
/// If the player wins all 5 rounds, they are declared the Streetball Champion.
bool runTournament(BasketballPlayer* Player) {
    const int totalRounds = 5;

    for (int round = 1; round <= totalRounds; ++round) {
        cout << "\n============================" << endl;
        cout << "Round " << round << " of the Tournament" << endl;
        cout << "============================\n" << endl;

        BasketballPlayer* Opponent = generateOpponent(round);
        cout << "Your opponent is: " << endl;
        Opponent->print();

        bool won = runMatch(Player, Opponent);

        delete Opponent;

        if (!won) {
            cout << "\nYou were eliminated from the tournament. Better luck next time!" << endl;
            char saveChoice;
            cout << "Would you like to save your character? (y/n): ";
            cin >> saveChoice;

            if (saveChoice == 'y' || saveChoice == 'Y') {
                string filename;
                cout << "Enter filename to save your game: ";
                cin >> filename;
                Player->save(filename);
                cout << "Game saved successfully!" << endl;
            }
            return false; 
        } else {
            cout << "\nCongrats! You advanced to the next round!" << endl;

            char saveChoice;
            cout << "Would you like to save your character? (y/n): ";
            cin >> saveChoice;

            if (saveChoice == 'y' || saveChoice == 'Y') {
                string filename;
                cout << "Enter filename to save your game: ";
                cin >> filename;
                Player->save(filename);
                cout << "Game saved successfully!" << endl;
            }
        }
    }

    cout << "\nYou won all 5 rounds and are the Streetball Champion!\n" << endl;
    return true; 
}

/// Loads a player from a file. The file should contain the player's type and attributes.
/// The first line of the file should contain the type of player (Shooter, Slasher, or Specialist).
BasketballPlayer* loadPlayer(string filename){
    string type;
    ifstream input;
    input.open(filename);
    getline(input, type);
    input.close();

    BasketballPlayer* Player = nullptr;

    if(type == "Shooter"){
        Player = new Shooter();
        Player->load(filename);
    }
    if(type == "Slasher"){
        Player = new Slasher();
        Player->load(filename);
    }       
    if(type == "Specialist"){
        Player = new Specialist();
        Player->load(filename);
    }   

    return Player;
}

/// Creates a new character for the player. The player can choose between three types of characters: Shooter, Slasher, or Specialist.
/// The player is prompted to enter their name, and a new character is created based on their choice.
BasketballPlayer* createCharacter(){
    int choice;
    string name;
    cout << "I knew you had it in you!\n Before you start hooping, what kind of player are you?" << endl;
    cout << "1: Shooter - A high stamina mid-range threat that can knock down a deep three!" << endl;
    cout << "2: Slasher - A low stamina bruiser who can destroy the rim!" << endl;
    cout << "3: Specialist - A medium stamina shifty presence that can cross up anyone!" << endl;
    cin >> choice;
    cin.ignore();
    cout << "Wow! I can't wait to see you compete! Whats your name?" << endl;
    getline(cin, name);
    cout << "Great! Your name is " << name << endl;

    BasketballPlayer* Player = nullptr;

    if(choice == 1){
        Player = new Shooter(name, 110, 1, 0, 4);
    } else if(choice == 2){
        Player = new Slasher(name, 100, 1, 0, 5);
    } else if(choice == 3){
        Player = new Specialist(name, 105, 1, 0, 5);
    } else {
        return nullptr;
    }

    return Player;
}

/// Displays the starting menu for the game. The player can choose to create a new character, load an existing character, or exit the game.
BasketballPlayer* displayStartingMenu(){
    int option;
    cout << "\nWelcome to the annual All-American Streetball Tournament! Are you ready to prove yourself against the competition?" << endl;
    cout << "Create a new character - 1" << endl;
    cout << "Load an existing character - 2" << endl;
    cout << "Exit - 3" << endl;
    string filename;
    cin >> option;

    BasketballPlayer* Player = nullptr;

    switch(option){
        case 1:
            Player = createCharacter();
            break;
        case 2:
            cout << "Please enter the name of your save file: " << endl;
            cin >> filename;
            Player = loadPlayer(filename);
            break;
        case 3:
            cout << "Exiting the game..." << endl;
            break;
        default:
            break;
    }

    return Player;
}

int main(){
    BasketballPlayer* Player = nullptr;

    while (true) {
        Player = displayStartingMenu();

        if (Player == nullptr) {
            cout << "Exiting the game..." << endl;
            break;
        }

        bool wonTournament = runTournament(Player);

        delete Player; 

        if (!wonTournament) {
            cout << "\nWould you like to try again? Returning to the starting menu...\n" << endl;
        } else {
            cout << "\nCongratulations on winning the tournament! Exiting the game...\n" << endl;
            break;
        }
    }

    return 0;
}