#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Tiles.h"
#include "Property.h"
#include "Railway.h"
#include "Utility.h"
#include "GoToJail.h"
#include "Go.h"
#include "Jail.h"
#include "FreeParking.h"
#include "CommunityChest.h"
#include "Tax.h"

using namespace std;

class Board {
private:
    vector<Tiles*> _tiles;

public:
    Board() {
        _tiles.resize(40);
        _tiles[0] = new GO("GO", 0);
         _tiles[1] = new Property("Mediterranean Avenue", 1, 60, 12);
         _tiles[2] = new CommunityChest("Community Chest", 2);
         _tiles[3] = new Property("Baltic Avenue", 3, 60, 12);
         _tiles[4] = new Tax("Income Tax", 4, 200);
         _tiles[5] = new Railways("Reading Railroad", 5, 200, 25);
         _tiles[6] = new Property("Oriental Avenue", 6, 100,15);
         _tiles[7] = new CommunityChest("Chance", 7);
         _tiles[8] = new Property("Vermont Avenue", 8, 100, 14);
         _tiles[9] = new Property("Connecticut Avenue", 9, 120, 16);
         _tiles[10] = new Jail("Just Visiting / In Jail", 10);

         _tiles[11] = new Property("St. Charles Place", 11, 140, 19);
         _tiles[12] = new Utility("Electric Company", 12, 150);
         _tiles[13] = new Property("States Avenue", 13, 140, 19);
         _tiles[14] = new Property("Virginia Avenue", 14, 160, 12);
         _tiles[15] = new Railways("Pennsylvania Railroad", 15, 200, 25);
         _tiles[16] = new Property("St. James Place", 16, 180, 22);
         _tiles[17] = new CommunityChest("Community Chest", 17);
         _tiles[18] = new Property("Tennessee Avenue", 18, 180, 22);
         _tiles[19] = new Property("New York Avenue", 19, 200, 25);

         _tiles[20] = new FreeParking("Free Parking", 20);
         _tiles[21] = new Property("Kentucky Avenue", 21, 220, 28);
         _tiles[22] = new CommunityChest("Chance", 22);
         _tiles[23] = new Property("Indiana Avenue", 23, 220, 28);
         _tiles[24] = new Property("Illinois Avenue", 24, 240, 30);
         _tiles[25] = new Railways("B&O Railroad", 25, 200, 25);
         _tiles[26] = new Property("Atlantic Avenue", 26, 260, 32);
         _tiles[27] = new Property("Ventnor Avenue", 27, 260, 32);
         _tiles[28] = new Utility("Water Works", 28, 150);
         _tiles[29] = new Property("Marvin Gardens", 29, 280, 34);

         _tiles[30] = new GoToJail("Go To Jail", 30);
         _tiles[31] = new Property("Pacific Avenue", 31, 300, 26);
         _tiles[32] = new Property("North Carolina Avenue", 32, 300, 36);
         _tiles[33] = new CommunityChest("Community Chest", 33);
         _tiles[34] = new Property("Pennsylvania Avenue", 34, 320, 38);
         _tiles[35] = new Railways("Short Line", 35, 200, 25);
         _tiles[36] = new CommunityChest("Chance", 36);
         _tiles[37] = new Property("Park Place", 37, 350, 40);
         _tiles[38] = new Tax("Luxury Tax", 38, 100);
         _tiles[39] = new Property("Boardwalk", 39, 400, 50);
    }

    Tiles* getTile(int position) const {
        return _tiles[position % 40];
    }

    const vector<Tiles*>& getTiles() const {
        return _tiles;
    }

    ~Board() {
        for (Tiles* tile : _tiles) {
            delete tile;
        }
    }
};

#endif
