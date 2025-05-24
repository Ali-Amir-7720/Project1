#include "tiles.h"

class Utility :public Tiles {
private:
	bool is_mortgaged;
	int price;
public:
	Utility() :Tiles("", 0), is_mortgaged(false), price(0) {};
	Utility(bool) {

	};
};