#ifndef GAMELOOP_H
#define GAMELOOP_H
#include<vector>
using namespace std;
#include "player.h"
#include "Board.h"
#include "dice.h"
class Gameloop {
private:
	vector<Player> P;
	Board b;
	Dice d;
	int n_p;
public:
	Gameloop() : n_p(0) {};
	void Initialization() {
		do {
			cout << "How Many Player Want To Play The Game.(Must Be Between 2 to 8)." << endl;
			cin >> n_p;
		} while (n_p < 2 || n_p> 8);
		for (int i = 0;i < n_p;i++){
			string n;
			cout << "Enter Player " << i + 1 << " name : " << endl;
			cin >> n;
			P.push_back(n);
	    }
	}
	void GameLoop() {
		bool game_over = false;
		int t_c=0;
		while (!game_over) {
			for (int i = 0;i < n_p;i++) {
				Player& c_p = P[i];
				if (!c_p.isBankrupt()) {
					cout << "It's " << c_p.getName() << " turn : " << endl;
					cout << "Press Enter To roll the dice." << endl;
					cin.ignore();
					cin.get();
					int d_r = d.rollDice();
					cout << c_p.getName() << " Rolled a " << d.getDice1() << " and a " << d.getDice2() << endl;
					c_p.Move(d_r);
					Tiles* c_t = b.getTile(c_p.getPosition());
					c_t->display();
					c_t->onLand(c_p);
					if (c_p.isBankrupt()) {
						cout << c_p.getName() << " has gone Bankrupt." << endl;
						//P.erase(c_p);
					}
					int a_p = 0;
					int last_idx = -1;
					for (int j = 0;j < P.size();j++) {
						if (!P[j].isBankrupt()) {
							a_p++;
							last_idx = j;
						}
					}
					if (a_p == 1) {
						cout << P[last_idx].getName() << " is the winner." << endl;
						game_over = true;
						break;
					}
				}
			}
			if(t_c>1000) {
				cout << "Game Ended In A draw As 1000 turns reached." << endl;
				game_over = true;
			}
		}
	}
};
#endif