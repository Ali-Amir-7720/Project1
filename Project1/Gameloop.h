#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <vector>
#include <iomanip>
#include <iostream>
using namespace std;

#include "player.h"
#include "Board.h"
#include "dice.h"

const int CELL_WIDTH = 16;
const int NUM_CELLS = 11;

class Gameloop {
private:
    vector<Player*> P;
    Board b;
    Dice d;
    int n_p;

public:
    Gameloop() : n_p(0) {}

    void drawCell(const string& text) {
        cout << "|" << setw(CELL_WIDTH) << left << text << string(CELL_WIDTH - text.length(), ' ');
    }

    void displayMonopolyBoard() {
        const string topRow[NUM_CELLS] = {
            "GO", "Mediterranean", "Community", "Baltic", "Income Tax",
            "Reading RR", "Oriental", "Chance", "Vermont", "Connecticut", "Jail"
        };

        const string leftCol[NUM_CELLS - 2] = {
            "Go To Jail", "Pacific", "Community", "N. Carolina", "Pennsylvania",
            "Short Line", "Chance", "Park Place", "Luxury Tax"
        };

        const string rightCol[NUM_CELLS - 2] = {
            "New York", "Free Parking", "Kentucky", "Chance", "Indiana",
            "Illinois", "B&O RR", "Atlantic", "Water Works"
        };

        const string bottomRow[NUM_CELLS] = {
            "Boardwalk", "Luxury Tax", "Park Place", "Chance", "Short Line",
            "Pennsylvania", "N. Carolina", "Community", "Pacific", "Go To Jail", "Start"
        };

        cout << string((CELL_WIDTH + 1) * NUM_CELLS + 1, '-') << endl;

        for (int i = 0; i < NUM_CELLS; ++i) drawCell(topRow[i]);
        cout << "|" << endl;

        for (int i = 0; i < NUM_CELLS - 2; ++i) {
            drawCell(leftCol[i]);
            cout << setw((CELL_WIDTH + 1) * (NUM_CELLS - 2)) << " ";
            drawCell(rightCol[i]);
            cout << "|" << endl;
        }

        for (int i = NUM_CELLS - 1; i >= 0; --i) drawCell(bottomRow[i]);
        cout << "|" << endl;

        cout << string((CELL_WIDTH + 1) * NUM_CELLS + 1, '-') << endl;
    }

    void Initialization() {
        do {
            cout << "How Many Players Want To Play The Game (2 to 8): ";
            cin >> n_p;
        } while (n_p < 2 || n_p > 8);

        for (int i = 0; i < n_p; i++) {
            string n;
            cout << "Enter Player " << i + 1 << " name: ";
            cin >> n;
            P.push_back(new Player(n));
        }
    }

    void handleUtilityMortgageOptions(Player* player) {
        vector<Utility*> utilities = player->getUtilities();
        if (utilities.empty()) return;

        while (true) {
            cout << "Utility Management for " << player->getName() << ":\n";
            cout << "1. Mortgage Utilities\n";
            cout << "2. Unmortgage Utilities\n";
            cout << "3. Done\n";
            cout << "Enter your choice: ";
            int choice;
            cin >> choice;

            switch (choice) {
            case 1:
                for (Utility* u : utilities) {
                    if (!u->isMortgaged()) {
                        cout << "Do you want to mortgage " << u->getName() << "? (y/n): ";
                        char ans;
                        cin >> ans;
                        if (ans == 'y' || ans == 'Y') u->Mortgage(*player);
                    }
                }
                break;

            case 2:
                for (Utility* u : utilities) {
                    if (u->isMortgaged()) {
                        cout << "Do you want to unmortgage " << u->getName() << "? (y/n): ";
                        char ans;
                        cin >> ans;
                        if (ans == 'y' || ans == 'Y') u->unmortgage(*player);
                    }
                }
                break;

            case 3:
                return;

            default:
                break;
            }
        }
    }

    void handleRailwayMortgageOptions(Player* player) {
        vector<Railways*> railways = player->getRailways();
        if (railways.empty()) return;

        while (true) {
            cout << "Railway Management for " << player->getName() << ":\n";
            cout << "1. Mortgage Railways\n";
            cout << "2. Unmortgage Railways\n";
            cout << "3. Done\n";
            cout << "Enter your choice: ";
            int choice;
            cin >> choice;

            switch (choice) {
            case 1:
                for (Railways* r : railways) {
                    if (!r->isMortgaged()) {
                        cout << "Do you want to mortgage " << r->getName() << "? (y/n): ";
                        char ans;
                        cin >> ans;
                        if (ans == 'y' || ans == 'Y') r->Mortgage(*player);
                    }
                }
                break;

            case 2:
                for (Railways* r : railways) {
                    if (r->isMortgaged()) {
                        cout << "Do you want to unmortgage " << r->getName() << "? (y/n): ";
                        char ans;
                        cin >> ans;
                        if (ans == 'y' || ans == 'Y') r->unmortgage(*player);
                    }
                }
                break;

            case 3:
                return;

            default:
                break;
            }
        }
    }

    void handleBuildingOptions(Player* player) {
        vector<Property*> props = player->getProperties();
        if (props.empty()) return;

        while (true) {
            cout << "Player " << player->getName() << ", do you want to:\n";
            cout << "1. Build Houses\n";
            cout << "2. Sell Houses\n";
            cout << "3. Mortgage Property\n";
            cout << "4. Unmortgage Property\n";
            cout << "5. Done\n";
            cout << "Enter your choice: ";
            int choice;
            cin >> choice;

            switch (choice) {
            case 1:
                for (Property* p : props) {
                    cout << "Do you want to build on " << p->getName() << "? (y/n): ";
                    char ans;
                    cin >> ans;
                    if (ans == 'y' || ans == 'Y') p->buildHouse(player, props);
                }
                break;

            case 2:
                for (Property* p : props) {
                    cout << "Do you want to sell houses on " << p->getName() << "? (y/n): ";
                    char ans;
                    cin >> ans;
                    if (ans == 'y' || ans == 'Y') p->sellHouse(player);
                }
                break;

            case 3:
                for (Property* p : props) {
                    if (!p->isMortgaged()) {
                        cout << "Do you want to mortgage " << p->getName() << "? (y/n): ";
                        char ans;
                        cin >> ans;
                        if (ans == 'y' || ans == 'Y') p->mortgage(*player);
                    }
                }
                break;

            case 4:
                for (Property* p : props) {
                    if (p->isMortgaged()) {
                        cout << "Do you want to unmortgage " << p->getName() << "? (y/n): ";
                        char ans;
                        cin >> ans;
                        if (ans == 'y' || ans == 'Y') p->unmortgage(*player);
                    }
                }
                break;

            case 5:
                return;

            default:
                break;
            }
        }
    }

    void GameLoop() {
        bool game_over = false;
        int turn_count = 0;

        while (!game_over) {
            for (int i = 0; i < n_p; i++) {
                Player* c_p = P[i];
                displayMonopolyBoard();

                if (!c_p->isBankrupt()) {
                    cout << "It's " << c_p->getName() << "'s turn:\n";

                    Tiles* t = b.getTile(c_p->getPosition());
                    t->display();

                    cout << "Your credit: " << c_p->getMoney() << endl;
                    cout << "Current Position: " << c_p->getPosition() << endl;

                    if (!c_p->jailStatus()) {
                        handleBuildingOptions(c_p);
                        handleRailwayMortgageOptions(c_p);
                        handleUtilityMortgageOptions(c_p);
                    }

                    cout << "Press Enter to roll dice.";
                    cin.ignore();
                    cin.get();

                    int prev = c_p->getPosition();
                    int r = d.rollDice();
                    c_p->setLastDice(d);
                    d.displayRoll();
                    if (c_p->jailStatus()) {
                        if (d.isEqual()) {
                            cout << "You rolled a double and are released from jail!" << endl;
                            c_p->ReleasefromJail();
                            c_p->Move(r);
                        }
                        else if (c_p->getJailTurns() >= 2) {
                            cout << "You have served 3 turns in jail. You're now released." << endl;
                            c_p->ReleasefromJail();
                            c_p->Move(r);
                        }
                        else {
                            cout << "You're in jail and didn't roll a double. Stay in jail." << endl;
                            c_p->IncrementJailTurns();
                        }
                    }
                    else {
                        c_p->Move(r);
                    }
                    int newpos = c_p->getPosition();

                    if (newpos < prev) {
                        Tiles* go = b.getTile(0);
                        go->onLand(*c_p);
                        cout << "You Have passed GO. 200 Added." << endl;
                        c_p->addMoney(200);
                    }

                    Tiles* newTile = b.getTile(newpos);
                    newTile->display();
                    newTile->onLand(*c_p);

                    cout << "Updated credit: " << c_p->getMoney() << endl;

                    if (c_p->isBankrupt()) {
                        cout << c_p->getName() << " has gone bankrupt!\n";
                    }

                    int alive = 0;
                    int last = -1;
                    for (int j = 0; j < P.size(); j++) {
                        if (!P[j]->isBankrupt()) {
                            alive++;
                            last = j;
                        }
                    }

                    if (alive == 1) {
                        cout << P[last]->getName() << " wins the game!\n";
                        game_over = true;
                        break;
                    }
                }
            }

            turn_count++;
            if (turn_count > 1000) {
                cout << "Game ended in a draw after 1000 turns.\n";
                game_over = true;
            }
        }

        for (Player* p : P) delete p;
    }
};

#endif
