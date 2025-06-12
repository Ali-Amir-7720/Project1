#ifndef COMMUNITYCHEST_H
#define COMMUNITYCHEST_H
#include "tiles.h"
#include "player.h"
#include<cstdlib>
class CommunityChest :public Tiles {
private:
	int draw;
public:
	CommunityChest() :Tiles("", 0),draw(0) {};
	CommunityChest(string n, int p) :Tiles(n, p), draw(0) {};
	void onLand(Player& P)override {
		draw = rand() % 7 + 1;
		if (draw == 1) {
			cout << "Move To Go and Collect 200." << endl;
			P.Move(0);
			//method implemented for 200 adding in go class
		}
		else if (draw == 2) {
			cout << "Go To Jail." << endl;
			P.goToJail();
		}
		else if (draw == 3) {
			cout << "Bank pays you dividend of $50" << endl;
			P.addMoney(50);
		}
		else if (draw==4) {
			cout << "Your building and loan matures.Collect $150." << endl;
			P.addMoney(150);
		}
		else if (draw == 5) {
			cout << "Pay poor tax of $15" << endl;
			P.deductMoney(15);
		}
		else if (draw == 6) {
			cout << "Its Your Birthday.Collect 200." << endl;
			P.addMoney(200);
		}
		else {
			cout << "Your Have been found Guilty in corruption.Pay 200." << endl;
			P.deductMoney(200);
		}
	}
	void display() const override {
		cout << "[COMMUNITY CHEST] Name: " << getName()
			<< ", Position: " << getPosition() << endl;
	}
};
#endif