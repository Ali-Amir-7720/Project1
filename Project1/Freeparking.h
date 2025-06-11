#ifndef FREEPARKING_H
#define FREEPARKINGH_H
#include "tiles.h"
class FreeParking :public Tiles {
private:

public:
	FreeParking() :Tiles("", 0) {};
	FreeParking(string n, int pos) :Tiles(n, pos) {};
};
#endif
