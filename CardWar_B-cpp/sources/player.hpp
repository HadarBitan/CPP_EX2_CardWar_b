#ifndef PLAYER_HPP
#define PLAYER_HPP

#pragma once

#include <iostream>
#include <string>
#include "card.hpp"

using namespace std;

namespace ariel
{
    class Player
    {
    private:
        string name;
        int cardsLeft;
        int cardWon;
        Card pack[26];
        string status;

    public:
        Player(string name);

        int stacksize();
        int cardesTaken();
        Card drawCard();
        void createPack(Card cards[]);
        void getStatus();
        void setStatus();
        string getName() const;
        void winGame(int cards)
        {
            this->cardWon += cards;
        }
    };
}

#endif