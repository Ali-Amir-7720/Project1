#ifndef FREEPARKING_H
#define FREEPARKING_H
#include "Tiles.h"
class FreeParking :public Tiles {
private:

public:
	FreeParking() :Tiles("", 0) {};
	FreeParking(string n, int pos) :Tiles(n, pos) {};
	void onLand(Player& P)override {
		cout << P.getName() << " Is At " << getName() << " Position : " << getPosition() << endl;
	}
	void display() const override {
		cout << "[FREE PARKING] Name: " << getName()
			<< ", Position: " << getPosition() << endl;
	}

};
#endif
