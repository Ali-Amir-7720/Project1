#ifndef PROPERTY_H
#define PROPERTY_H

#include "Tiles.h"
class Player;
#include <iostream>
using namespace std;
class Property : public Tiles {
private:
    int price;
    bool is_bought;
    Player* owner;
    int houses_count;
    bool is_hotel;
    int base_rent;
    bool is_mortgaged;

public:
    Property() : Tiles("", 0), price(0), is_bought(false), owner(nullptr),
        houses_count(0), is_hotel(false), base_rent(0), is_mortgaged(false) {
    }

    Property(string n, int pos, int p, int br) :
        Tiles(n, pos), price(p), is_bought(false), owner(nullptr),
        houses_count(0), is_hotel(false), base_rent(br), is_mortgaged(false) {
    }

    void onLand(Player& P) override {
        if (!is_bought) {
            cout << "You landed on " << getName() << ". Would you like to buy it for $" << price << "? (y/n): ";
            char choice;
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                if (P.deductMoney(price)) {
                    is_bought = true;
                    owner = &P;
                    P.addProperty(this);
                    cout << "You bought " << getName() << "!" << endl;
                }
                else {
                    cout << "Not enough money to buy." << endl;
                }
            }
            return;
        }

        if (owner != &P && !is_mortgaged) {
            int rent = base_rent + houses_count * (base_rent / 2);
            cout << "You landed on " << getName() << " owned by " << owner->getName()
                << ". You owe $" << rent << " in rent." << endl;
            if (P.deductMoney(rent)) {
                owner->addMoney(rent);
            }
        }
    }

    void display() const override {
        cout << "Property: " << getName()
            << " | Position: " << getPosition()
            << " | Price: $" << price
            << " | Base Rent: $" << base_rent;
        if (is_bought) {
            cout << " | Owner: " << owner->getName()
                << " | Houses: " << houses_count
                << " | Hotel: " << (is_hotel ? "Yes" : "No")
                << " | Mortgaged: " << (is_mortgaged ? "Yes" : "No");
        }
        else {
            cout << " | Available to Buy";
        }
        cout << endl;
    }

    bool isMortgaged() const {
        return is_mortgaged;
    }

    void upgradeProperty(Player& P) {
        if (owner != &P) {
            cout << "You don't own this property." << endl;
            return;
        }

        if (P.jailStatus()) {
            cout << "You can't upgrade while in jail." << endl;
            return;
        }

        char choice;
        cout << "Would you like to upgrade " << getName() << "? (y/n): ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            int amount;
            cout << "How many houses do you want to build (max 4, 5 = hotel)? ";
            cin >> amount;

            if (amount <= 0 || (houses_count + amount) > 5) {
                cout << "Invalid number of upgrades." << endl;
                return;
            }

            int cost = amount * (price / 2);
            if (P.deductMoney(cost)) {
                houses_count += amount;
                is_hotel = (houses_count == 5);
                cout << "Upgraded successfully. Current houses: " << houses_count << endl;
            }
            else {
                cout << "Not enough money to upgrade." << endl;
            }
        }
    }

    void mortgage(Player& P) {
        if (owner != &P) {
            cout << "You don't own this property." << endl;
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
        cout << "Property mortgaged for $" << value << "." << endl;
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
};

#endif