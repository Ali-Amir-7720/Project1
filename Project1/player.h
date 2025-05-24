#ifndef PLAYER_H
#define PLAYER_H
#include<vector>
#include "Tiles.h"
#include "dice.h"
#include "Property.h"
class Player {
private:
	int money;
	string name;
	int pos;
	vector<Property*> owned_property;
	bool jail_status;
	int jail_turns;
public:
	Player() :money(0), name(""), jail_turns(0) {};
	Player(const string n) {
		this->name = n;
		money = 5000;
		jail_status = false;
		jail_turns = 0;
	}
	string getName()const {
		return name;
	}
	int getMoney()const {
		return money;
	}
	bool jailStatus()const {
		return jail_status;
	}
    const vector<Property*>& getProperties () const {
		return owned_property;
	}
	void Move(int steps) {
		Dice d;
		steps = d.rollDice();
		pos = (pos + steps)%40;
	}
	void setPosition(int p) {
		pos = p % 40;
	}
	void addMoney(int amount) {
		money += amount;
	}
	bool deductMoney(int amount) {
		if (amount > money) {
			cout << "Not Enough Money.";
			return false;
		}
		cout << "/n.Money Deducted.";
		money -= amount;
		return true;
	}
	void addProperty(Property* p) {
		cout << "PropertyBought" << endl;
		owned_property.push_back(p);
	}
	void removeProperty(Property* p) {
		//owned_properties.erase(remove(owned_properties.begin(), owned_properties.end(), property),
		//	owned_properties.end());//2 errors
	}
	void jailStatus() {
		jail_status = true;
		pos = 10;
		jail_turns = 3;
		cout << "Player " << name << " is sent to jail.";
	}
	bool isBankrupt() {
		if (money >= 0) {
			return false;
		}
        for (int i = 0;i < (int)owned_property.size();i++) {
			Property* p = owned_property[i];
			if (!p->isMortgaged()) {
				return false;
			}
		}
		return true;
	}
};
#endif