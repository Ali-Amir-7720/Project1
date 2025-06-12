#ifndef TILES_H
#define TILES_H
class Player;
#include<string>
using namespace std;
class Tiles {
private:
	string name;
	int position;
public:
	Tiles() :name(""), position(0) {};
	Tiles(string n, int p) {
		this->name = n;
		this->position = p;
	}
	virtual void onLand(Player& P) = 0;
	int getPosition() const {
		return position;
	}

	string getName()const {
		return name;
	}
	virtual void display() const = 0;
};
#endif