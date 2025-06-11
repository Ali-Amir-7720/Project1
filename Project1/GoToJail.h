#ifndef GOTOJAIL_H
#define GOTOJAIL_H
#include "tiles.h"
class GoToJail :public Tiles {
public:
	GoToJail() :Tiles("", 0) {};
	GoToJail(string n, int p) :Tiles(n, p) {};
	void onLand(Player& P) {
		P.JailStatus();
		cout << P.getName() << " sent To Jail." << endl;
	}
};
#endif
