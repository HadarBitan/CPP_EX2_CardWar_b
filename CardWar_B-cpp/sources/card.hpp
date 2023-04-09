#ifndef CARD_HPP
#define CARD_HPP

#pragma once

#include <iostream>
#include <string>

using namespace std;

namespace ariel
{
    class Card
    {
    private:
        int number;
        string symbol;

    public:
        Card(int number, string symbol);
        int getCardNumber() const;
        string getCardSymbol() const;
    };
}

#endif