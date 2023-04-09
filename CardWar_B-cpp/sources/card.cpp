#include <iostream>
#include <string>
#include "card.hpp"

using namespace std;

namespace ariel
{
    Card::Card(int number, string symbol) 
    {
        this->number = number;
        this->symbol = symbol;
    }

    int Card::getCardNumber() const {return this->number;}

    string Card::getCardSymbol() const {return this->symbol;}
}