#ifndef JAIL_H
#define JAIL_H
#include "tiles.h"
class Jail :public Tiles {
private:

public:
	Jail() :Tiles("", 0) {};
	Jail(string n, int p):Tiles(n, p) {};
};
#endif