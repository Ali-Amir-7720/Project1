//#ifndef GO_H
//#define GO_H
//#include "tiles.h"
//#include "player.h"
//class GO : public Tiles {
//private:
//	int amount=200;
//public:
//	GO() :Tiles("", 0) {};
//	GO(const string n, int pos) :Tiles(n, pos) {};
//	void onLand(Player& P)override {
//		P.addMoney(amount);
//		cout << P.getName() << " landed on GO and received $" << amount << "." << endl;
//	}
//	void PassGOReward(Player& P) {
//		P.addMoney(amount);
//		cout << P.getName() << " passed GO and received $" << amount << "." << endl;
//	}
//	void display() const override {
//		cout << "[GO] Name: " << getName()
//			<< ", Position: " << getPosition()
//			<< ", Reward: $" << amount << endl;
//	}
//};
//#endif#pragma once
class GO : public Tiles {
private:
	int amount = 200;
public:
	GO() :Tiles("", 0) {};
	GO(const string n, int pos) :Tiles(n, pos) {};

	void onLand(Player& P)override {
		P.addMoney(amount);
		cout << P.getName() << " landed on GO and received $" << amount << "." << endl;
	}

	void PassGOReward(Player& P) {
		P.addMoney(amount);
		cout << P.getName() << " passed GO and received $" << amount << "." << endl;
	}

	void display() const override {
		cout << "[GO] Name: " << getName()
			<< ", Position: " << getPosition()
			<< ", Reward: $" << amount << endl;
	}
};

