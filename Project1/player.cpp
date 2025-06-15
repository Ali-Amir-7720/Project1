#include "Player.h"
#include "dice.h"
#include "property.h"
#include "utility.h"
#include "railway.h"
Player::Player() : money(0), r_c(0), name(""), jail_turns(0), pos(0), jail_status(false) {}

Player::Player(const string n) {
    this->name = n;
    r_c = 0;
    money = 5000;
    jail_status = false;
    jail_turns = 0;
    pos = 0;
}
int Player::getJailTurns()const {
    return jail_turns;
}
void Player::ReleasefromJail() {
    jail_status = false;
    jail_turns = 0;
}

int Player::getPosition() const {
    return pos;
}

string Player::getName() const {
    return name;
}

int Player::getMoney() const {
    return money;
}

bool Player::jailStatus() const {
    return jail_status;
}
const vector<Utility*>&Player:: getUtilities() const {
    return owned_utility;
}
const vector<Railways*>& Player::getRailways() const {
    return owned_railway;
}
const vector<Property*>& Player::getProperties() const {
    return owned_property;
}
void Player::utilityCount() {
    u_c++;
}
void Player::removeUtility() {
    u_c--;
}
int Player::getUC() {
    return u_c;
}
bool Player::checkpos(int steps) {
    int old_pos = pos;
    pos = (pos + steps) % 40;

    return pos < old_pos;
}
void Player::Move(int steps) {
    pos = (pos + steps) % 40;
}
void Player::setPosition(int p) {
    pos = p % 40;
}
void Player::setLastDice(Dice &d) {
    last_roll = &d;
}
void Player::addMoney(int amount) {
    money += amount;
}
Dice* Player::getlastRoll()const {
    return last_roll;
}
bool Player::deductMoney(int amount) {
    if (amount > money) {
        cout << "Not Enough Money.";
        return false;
    }
    cout << "\nMoney Deducted.";
    money -= amount;
    return true;
}

void Player::goToJail() {
    jail_status = true;
    pos = 10;
    jail_turns = 0;
    cout << "Player " << name << " is sent to jail.";
}
void Player::addProperty(Property* t) {
    owned_property.push_back(t);
    cout << t->getName() << " at Position: " << t->getPosition() << endl;
}
void Player::addUtility(Utility* u) {
    owned_utility.push_back(u);
    cout << "Utility added: " << u->getName() << " at Position: " << u->getPosition() << endl;
}

void Player::addRailway(Railways* r) {
    owned_railway.push_back(r);
    r_c++; 
    cout << "Railway added: " << r->getName() << " at Position: " << r->getPosition() << endl;
}

bool Player::isBankrupt() {
    if (money >= 0) {
        return false;
    }

    for (Property* p : owned_property) {
        if (!p->isMortgaged() || p->getHouses() > 0) {
            return false;
        }
    }

    for (Utility* u : owned_utility) {
        if (!u->isMortgaged()) {
            return false;
        }
    }

    for (Railways* r : owned_railway) {
        if (!r->isMortgaged()) {
            return false;
        }
    }

    return true;
}

void Player::IncrementJailTurns() {
    jail_turns++;
}

void Player::removeRailway() {
    r_c--;
}

void Player::addRailway() {
    r_c++;
}

int Player::getRailwaysCount() const {
    return r_c;
}
