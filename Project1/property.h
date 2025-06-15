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
    char colour;
    int same_colour;
public:
    Property() : Tiles("", 0), price(0), is_bought(false), owner(nullptr),
        houses_count(0), is_hotel(false), base_rent(0), is_mortgaged(false),same_colour(0) {
    }
    int getHouses() {
        return houses_count;
    }
    Property(string n, int pos, int p, int br,char c,int sc) :
        Tiles(n, pos), price(p), is_bought(false), owner(nullptr),
        houses_count(0), is_hotel(false), base_rent(br), is_mortgaged(false),colour(c),same_colour(sc) {
    }
    Player* getOwner() {
        return owner;
    }
    char getColour()const {
        return colour;
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
            if (is_hotel) {
                int rent = base_rent + 5 * (base_rent / 2);
                cout << "You landed on " << getName() << " owned by " << owner->getName()
                    << ". You owe $" << rent << " in rent." << endl;
                if (P.deductMoney(rent)) {
                    owner->addMoney(rent);
                }
            }
            else {
                int rent = base_rent + houses_count * (base_rent / 2);
                cout << "You landed on " << getName() << " owned by " << owner->getName()
                    << ". You owe $" << rent << " in rent." << endl;
                if (P.deductMoney(rent)) {
                    owner->addMoney(rent);
                }
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
    bool buildHouse(Player* P, const vector<Property*>& player_props) {
        int owned_same_color = 0;

        for (Property* p : player_props) {
            if (p->getColour() == colour && p->getOwner() == P)
                owned_same_color++;
        }

        if (owned_same_color < same_colour) {
            cout << "You do not own the full color set." << endl;
            return false;
        }

        if (is_hotel) {
            cout << "Cannot build. Already a hotel on this property." << endl;
            return false;
        }

        if (houses_count == 4) {
            char upgrade;
            cout << "This property has 4 houses. Upgrade to hotel? (y/n): ";
            cin >> upgrade;

            if ((upgrade == 'y' || upgrade == 'Y') && P->deductMoney(price / 2)) {
                is_hotel = true;
                cout << "Hotel built!" << endl;
                return true;
            }
            else {
                cout << "Hotel upgrade cancelled or not enough money." << endl;
                return false;
            }
        }

        int choice;
        cout << "How many houses do you want to build (1-" << (4 - houses_count) << "): ";
        cin >> choice;

        if (choice < 1 || choice >(4 - houses_count)) {
            cout << "Invalid number of houses." << endl;
            return false;
        }

        int cost = (price / 2) * choice;

        if (P->deductMoney(cost)) {
            houses_count += choice;
            cout << "Built " << choice << " house(s). Total: " << houses_count << endl;
            return true;
        }
        else {
            cout << "Not enough money." << endl;
            return false;
        }
    }


    bool sellHouse(Player* P) {
        if (is_hotel) {
            char sellHotel;
            cout << "This property has a hotel. Do you want to sell it for $" << (price / 4) << "? (y/n): ";
            cin >> sellHotel;
            if (sellHotel == 'y' || sellHotel == 'Y') {
                is_hotel = false;
                houses_count = 4;
                P->addMoney(price / 4);
                cout << "Hotel sold. Downgraded to 4 houses. You received $" << (price / 4) << endl;
                return true;
            }
            else {
                cout << "Hotel sale cancelled." << endl;
                return false;
            }
        }

        if (houses_count == 0) {
            cout << "No houses to sell on this property." << endl;
            return false;
        }

        int choice;
        cout << "This property has " << houses_count << " house(s). How many do you want to sell? ";
        cin >> choice;

        if (choice < 1 || choice > houses_count) {
            cout << "Invalid number of houses." << endl;
            return false;
        }

        houses_count -= choice;
        int earned = (price / 4) * choice;
        P->addMoney(earned);
        cout << "Sold " << choice << " house(s). You received $" << earned << ". Remaining houses: " << houses_count << endl;
        return true;
    }

    void mortgage(Player& P) {
        if (owner != &P) {
            cout << "You don't own this property." << endl;
            return;
        }
        if (houses_count > 0) {
            cout << "Cannot Mortgage.Sell the houses first." << endl;
            cout << "You have " << houses_count << " Houses." << endl;
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