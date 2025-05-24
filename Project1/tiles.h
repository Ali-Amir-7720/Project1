#ifndef TILES_H
#define TILES_h
#include"player.h"
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
		this->position =p;
	}
	virtual void onLand(Player& P)=0;
	int getPosition() const {
		return position;
	}
	virtual void display()const = 0;
	virtual ~Tile() {
		delete Tiles;
	}
	int getPosition() const {
		return position;
	}
};
#endif