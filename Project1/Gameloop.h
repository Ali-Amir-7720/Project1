#ifndef GAMELOOP_H
#define GAMELOOP_H
#include<vector>
#include<iomanip>
using namespace std;
#include "player.h"
#include "Board.h"
#include "dice.h"
const int CELL_WIDTH = 16;   // Cell width for uniform square appearance
const int NUM_CELLS = 11;    // Number of tiles per side (standard Monopoly)

class Gameloop {
private:
	vector<Player> P;
	Board b;
	Dice d;
	int n_p;
public:

	void drawCell(const string& text) {
		cout << "|" << setw(CELL_WIDTH) << left << (text + string(CELL_WIDTH - text.length() - 1, ' ')) << " ";
	}

	void displayMonopolyBoard() {
		// Top side (left to right)
		const string topRow[NUM_CELLS] = {
			"GO", "Mediterranean", "Community", "Baltic", "Income Tax",
			"Reading RR", "Oriental", "Chance", "Vermont", "Connecticut", "Jail"
		};

		// Left column (bottom to top)
		const string leftCol[NUM_CELLS - 2] = {
			"Go To Jail", "Pacific", "Community", "N. Carolina", "Pennsylvania",
			"Short Line", "Chance", "Park Place", "Luxury Tax"
		};

		// Right column (top to bottom)
		const string rightCol[NUM_CELLS - 2] = {
			"New York", "Free Parking", "Kentucky", "Chance", "Indiana",
			"Illinois", "B&O RR", "Atlantic", "Water Works"
		};

		// Bottom row (right to left)
		const string bottomRow[NUM_CELLS] = {
			"Boardwalk", "Luxury Tax", "Park Place", "Chance", "Short Line",
			"Pennsylvania", "N. Carolina", "Community", "Pacific", "Go To Jail", "Start"
		};

		// Print top border
		cout << string((CELL_WIDTH + 1) * NUM_CELLS + 1, '-') << endl;

		// Print top row
		for (int i = 0; i < NUM_CELLS; ++i) {
			drawCell(topRow[i]);
		}
		cout << "|" << endl;

		// Print middle rows (left and right columns)
		for (int i = 0; i < NUM_CELLS - 2; ++i) {
			drawCell(leftCol[i]);  // Left side

			// Middle space
			cout << setw((CELL_WIDTH + 1) * (NUM_CELLS - 2) + 1) << " ";

			drawCell(rightCol[i]); // Right side
			cout << "|" << endl;
		}

		// Print bottom row (reversed)
		for (int i = NUM_CELLS - 1; i >= 0; --i) {
			drawCell(bottomRow[i]);
		}
		cout << "|" << endl;

		// Print bottom border
		cout << string((CELL_WIDTH + 1) * NUM_CELLS + 1, '-') << endl;
	}
	Gameloop() : n_p(0) {};
	void Initialization() {
		do {
			cout << "How Many Player Want To Play The Game.(Must Be Between 2 to 8)." << endl;
			cin >> n_p;
		} while (n_p < 2 || n_p> 8);
		for (int i = 0;i < n_p;i++) {
			string n;
			cout << "Enter Player " << i + 1 << " name : " << endl;
			cin >> n;
			P.push_back(n);
		}
	}
	void GameLoop() {
		bool game_over = false;
		int t_c = 0;
		while (!game_over) {
			for (int i = 0;i < n_p;i++) {
				Player& c_p = P[i];
				displayMonopolyBoard();
				if (!c_p.isBankrupt()) {
					cout << "It's " << c_p.getName() << " turn : " << endl;
					cout << "Press Enter To roll the dice." << endl;
					cin.ignore();
					cin.get();
					int d_r = d.rollDice();
					d.displayRoll();
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
			if (t_c > 1000) {
				cout << "Game Ended In A draw As 1000 turns reached." << endl;
				game_over = true;
			}
		}
	}
};
#endif