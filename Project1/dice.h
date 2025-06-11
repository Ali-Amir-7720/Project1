#ifndef DICE_H
#define DICE_H
#include "player.h"
#include<cstdlib>
using namespace std;
class Dice {
private:
    int d_1, d_2;
public:
    Dice() : d_1( 0), d_2 (0){};
    int rollDice() {
            d_1 = rand() % 6 + 1;
            d_2 = rand() % 6 + 1;
            int d = d_1 + d_2;
            return d;
    }
    bool isEqual() {
        if (d_1 == d_2) {
            return true;
        }
        return false;
    }
    int getDice1()const {
        return d_1;
    }
    int getDice2()const {
        return d_2;
    }
};
#endif