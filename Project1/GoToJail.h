#ifndef GOTOJAIL_H
#define GOTOJAIL_H
#include "tiles.h"
class GoToJail :public Tiles {
public:
	GoToJail() :Tiles("", 0) {};
	GoToJail(string n, int p) :Tiles(n, p) {};
	void onLand(Player& P) {
		P.goToJail();
		cout << P.getName() << " sent To Jail." << endl;
	}
	void display() const override {
		cout << "[GO TO JAIL] Name: " << getName()
			<< ", Position: " << getPosition() << endl;
	}

};
#endif
