#include "Card.h"

using namespace std;

Card::Card(int number, int value)
{
    this->number = number;
    this->value = value;
    this->uid = "";
}

Card::~Card()
{
}

/******************
*   Accessors     *
*******************/

int Card::getNumber() {
    return this->number;
} 

int Card::getValue() {
    return this->value;
}

string Card::getBelongsTo() {
    return this->uid;
}

/******************
*    Mutators     *
*******************/

void Card::belongsTo(string uid) {
    this->uid = uid;
} 
