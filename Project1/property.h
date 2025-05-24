#ifndef PROPERTY_H
#define PROPERTY_H
#include "tiles.h"
#include<iostream>
class Property :public Tiles {
private:
	int price;
	bool is_bought;
	Player* owner;
	int houses_count;
	bool is_hotel;
	int base_rent;
	bool is_mortgaged;
	//int upgrade_cost;
public:
	Property() :Tiles("",0), price(0), is_bought(false) {};
	Property(string n, int pos, int p) :Tiles(n, pos), price(p), is_bought(false){};
	void onLand(Player& P)override {
		char p;
		if (!is_bought) {
			cout << "Would You Like to buy this property? y(Yes)." << endl;
			cin >> p;
			if (p == 'y' || p == 'Y') {
				if (P.deductMoney(price) == true)
				{
					is_bought = true;
					owner->addProperty(P);
				}
				else {
					cout << "Cannot Buy Property." << endl;
				}
			}
			return;
		}
		if (owner != &P) {
			if (houses_count == 0) {
				P->deductMoney(base_rent);
				owner->addMoney(base_rent);
			}
			else if (houses_count == 1) {
				P->deductMoney(base_rent*1.5);
				owner->addMoney(base_rent*1.5);
			}
			else if (houses_count == 2) {
				P->deductMoney(base_rent * 2.5);
				owner->addMoney(base_rent*2.5);
			}
			else if (houses_count == 3) {
				P->deductMoney(base_rent * 3.5);
				owner->addMoney(base_rent*3.5);
			}
			else if (houses_count == 4) {
				P->deductMoney(base_rent * 4.5);
				owner->addMoney(base_rent*4.5);
			}
			else {
				P->deductMoney(base_rent * 6.5);
				owner->addMoney(base_rent*6.5);
			}
		}
	}
	void display()const override {
		cout << Tiles(name,position);
	}
	void upgradeProperty(Player & P) {
		if (owner == &P) {
			if (P.jailStatus() == true) {
				cout << "You cannot build.You're in jail.";
				return;
			}
			char p;
			cout << "Would you like to upgrade your property? (y/n): ";
			cin >> p;

			if (p == 'y' || p == 'Y') {
				cout << "How many houses do you want to build? ";
				int l;
				cin >> l;

				if (l > 0 && (houses_count + l) <= 5) {
					houses_count += l;
					int cost = static_cast<int>(price * l * 0.5);
					if (owner->deductMoney(cost)) {
						cout << "Successfully built " << l << " house(s)." << endl;
					}
					else {
						houses_count -= l; 
						cout << "Upgrade cancelled due to insufficient funds." << endl;	
					   }
					}
				else {
					cout << "Invalid number of houses. You can only have up to 5 total." << endl;
				}
			}
			else {
				cout << "Upgrade cancelled." << endl;
			}
		}
		else {
			cout << "You do not own this property." << endl;
		}
	}
	bool Mortgage(Player& P) {
		if (owner != &P) {
			cout << "You do not own this property.";
			return false;
		}
		if (is_mortgaged) {
			cout << "You've already mortgaged this Property.";
			return false;
		}
		if (P.jailStatus() == true) {
			cout << "You cannot mortgage in jail.";
			return false;
		}
		is_mortgaged = true;
		int mm = static_cast<int>(price*0.5);
		owner.addMoney(mm);
		cout << "Property Successfully Mortgaged.";
		return true;
	}
	bool Unmortgage(Player& P) {
		if (is_mortgaged) {
			if (owner == &P) {
				int um = static_cast<int>(price*0.6);
				if (P.deductMoney(um)) {
					is_mortgaged = false;
					cout << "Property Successfuly Unmortgaged.";
					return true;
				}
				else {
					cout << "Cannot Unmortgage Property.Not enough Money ";
					return false;
				}
			}
			else {
				cout << "You do not own this property.";
				return false;
			}
		}
		else {
			cout << "Property Is not Mortgaged.";
			return false;
		}
	}
	bool isMortgaged() const {
	/*	if (is_mortgaged) {
			return true;
		}
		return false;*/
		return is_mortgaged;
	}
};
#endif