#ifndef TAX_H
#define TAX_H
#include "tiles.h"
class Tax:public Tiles {
private:
	int tax;
public:
	Tax() :Tiles("", 0), tax(0) {};
	Tax(string n, int pos, int t) :Tiles(n, pos), tax(t) {};
	void onLand(Player& P)override {
		cout << "You Landed On " << getName() << " Pay : " << getTax() << endl;
		if (P.deductMoney(tax) == true) {
			cout << getTax() << " Deducted from your account " << endl;
		}
		else {
			cout << "Cannot Deduct.insufficient balance." << endl;
		}
	}
	int getTax() const {
		return tax;
	}
};
#endif