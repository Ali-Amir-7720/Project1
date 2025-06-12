#ifndef RAILWAY_H
#define RAILWAY_H
#include "Tiles.h"
#include "player.h"
class Railways :public Tiles {
private:
	int price;
	int rent;
	bool is_bought;
	bool is_mortgaged;
	Player* owner;
public:
	Railways() :Tiles(), price(0), rent(0), is_bought(false), is_mortgaged(false), owner(nullptr) {};
	Railways(string n, int pos, int rent, int pr) :Tiles(n, pos), price(pr), is_bought(true),rent(rent), is_mortgaged(false), owner(nullptr) {};
	void onLand(Player& P)override {
		if (!is_bought) {
			char c;
			cout << "Would You Like to buy " << getName() << " at " << getPosition() << endl << " y/n.";
			cin >> c;
			if (c == 'y' || c == 'Y') {
				if (P.deductMoney(price) == true) {
					owner = &P;
					is_bought = true;
					P.addRailway(this);
					P.addRailway();
				}
				else {
					cout << "Not enough money to buy " << getName() << endl;
				}
			}
		}
		else if (owner != &P && !is_mortgaged) {
			int rent = 50 * P.getRailwaysCount();
			cout << "You landed on " << owner->getName() << "'s railway. Pay rent : " << rent << endl;
			if (!P.deductMoney(rent)) {
				cout << "Cannot pay rent. Might go bankrupt!" << endl;
			}
			else {
				owner->addMoney(rent);
			}
		}
		else if (owner == &P) {
			cout << "You landed on your own railway: " << getName() << "." << endl;
		}
	}
	void MoveToOwnedRailway(Player& player, const vector<Tiles*>& board) {
		vector<int> ownedRailwayPositions;
		for (int pos : {5, 15, 25, 35}) {
			if (pos == player.getPosition()) continue;
			Railways* r = dynamic_cast<Railways*>(board[pos]);
			if (r && r->getOwner() == &player) {
				ownedRailwayPositions.push_back(pos);
			}
		}

		if (ownedRailwayPositions.empty()) {
			cout << "You don't own any other railways to move to.\n";
			return;
		}

		cout << "You own the following railways:\n";
		for (size_t i = 0; i < ownedRailwayPositions.size(); ++i) {
			Railways* r = dynamic_cast<Railways*>(board[ownedRailwayPositions[i]]);
			cout << i + 1 << ". " << r->getName() << " at position " << ownedRailwayPositions[i] << endl;
		}

		cout << "Enter the number of the railway you want to move to: ";
		int choice;
		cin >> choice;

		if (choice >= 1 && choice <= (int)ownedRailwayPositions.size()) {
			int targetPos = ownedRailwayPositions[choice - 1];
			player.setPosition(targetPos);
			board[targetPos]->onLand(player);
		}
		else {
			cout << "Invalid choice.\n";
		}
	}
	void Mortgage(Player& P) {
		if (owner != &P) {
			cout << "You Do not own it." << endl;
			return;
		}
		if (is_mortgaged) {
			cout << "Already mortgaged." << endl;
			return;
		}
		if (P.jailStatus()) {
			cout << "You can't mortgage from jail." << endl;
			return;
		}

		is_mortgaged = true;
		int value = price / 2;
		P.addMoney(value);
		cout << getName() << "Property mortgaged for $" << value << "." << endl;
		P.removeRailway();
	}
	void unmortgage(Player& P) {
		if (owner != &P || !is_mortgaged) {
			cout << "Unmortgage not allowed." << endl;
			return;
		}

		int cost = price * 0.6;
		if (P.deductMoney(cost)) {
			is_mortgaged = false;
			cout << "Unmortgaged successfully." << endl;
			P.addRailway();
		}
		else {
			cout << "Not enough money to unmortgage." << endl;
		}
	}
	Player* getOwner()const {
		return owner;
	}
	void display() const override {
		cout << "[RAILWAY] Name: " << getName()
			<< ", Position: " << getPosition()
			<< ", Price: $" << price
			<< ", Rent: $" << rent
			<< ", Owned: " << (is_bought ? "Yes" : "No")
			<< ", Mortgaged: " << (is_mortgaged ? "Yes" : "No")
			<< ", Owner: " << (owner ? owner->getName() : "None") << endl;
	}
};
#endif
