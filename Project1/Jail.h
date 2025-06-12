#ifndef JAIL_H
#define JAIL_H
#include "Tiles.h"
class Jail :public Tiles {
private:

public:
	Jail() :Tiles("", 0) {};
	Jail(string n, int p):Tiles(n, p) {};
	void onLand(Player& P)override {
		cout << "You Are Just Visiting Jail." << endl;
	}
	void display() const override {
		cout << "[JAIL] Name: " << getName()
			<< ", Position: " << getPosition() << endl;
	}
};
#endif