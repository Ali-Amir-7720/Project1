#ifndef UTILITY_H
#define UTILITY_H

#include "tiles.h"
#include <iostream>
using namespace std;

class Utility : public Tiles {
private:
    int price;
    bool is_mortgaged;
    bool is_bought;
    Player* owner;

public:
    Utility() : Tiles("", 0), price(0), is_mortgaged(false), is_bought(false), owner(nullptr) {}

    Utility(string n, int pos, int p) :
        Tiles(n, pos), price(p), is_mortgaged(false), is_bought(false), owner(nullptr) {
    }

    void onLand(Player& P) override {
        if (!is_bought) {
            char c;
            cout << "You landed on utility: " << getName() << ". Buy for $" << price << "? (y/n): ";
            cin >> c;
            if (c == 'y' || c == 'Y') {
                if (P.deductMoney(price)) {
                    is_bought = true;
                    owner = &P;
                    P.addProperty(this);
                    cout << "Utility bought!" << endl;
                }
                else {
                    cout << "Not enough money to buy utility." << endl;
                }
            }
        }
        else if (owner != &P && !is_mortgaged) {
            Dice d;
            int roll = d.rollDice();
            int rent = roll * 4; 
            cout << "You rolled " << roll << ". Pay rent $" << rent << " to " << owner->getName() << "." << endl;
            if (P.deductMoney(rent)) {
                owner->addMoney(rent);
            }
        }
    }

    void display() const override {
        cout << "Utility: " << getName()
            << " | Position: " << getPosition()
            << " | Price: $" << price;

        if (is_bought) {
            cout << " | Owner: " << owner->getName()
                << " | Mortgaged: " << (is_mortgaged ? "Yes" : "No");
        }
        else {
            cout << " | Available to Buy";
        }
        cout << endl;
    }
    void Mortgage(Player& P) {
        if (owner != &P) {
            cout << "You Do not own it." << endl;
            return;
        }
        if (is_mortgaged) {
            cout << "Already mortgaged." << endl;
            return;
        }
        if (P.jailStatus()) {
            cout << "You can't mortgage from jail." << endl;
            return;
        }

        is_mortgaged = true;
        int value = price / 2;
        P.addMoney(value);
        cout << getName() << "Property mortgaged for $" << value << "." << endl;
    }
    void unmortgage(Player& P) {
        if (owner != &P || !is_mortgaged) {
            cout << "Unmortgage not allowed." << endl;
            return;
        }

        int cost = price * 0.6;
        if (P.deductMoney(cost)) {
            is_mortgaged = false;
            cout << "Unmortgaged successfully." << endl;
        }
        else {
            cout << "Not enough money to unmortgage." << endl;
        }
    }
    bool isMortgaged() const {
        return is_mortgaged;
    }
};

#endif