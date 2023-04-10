#ifndef PLAYER_HPP
#define PLAYER_HPP

#pragma once

#include <iostream>
#include <string>
#include <stack>
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
        int numOfWins;
        stack<Card> pack;
        string status;

    public:
        Player(string name);

        int stacksize();
        int cardesTaken();
        Card drawCard();
        void createPack(Card card);
        void getStatus();
        void setStatus(int numberOfGames);
        string getName() const;
        void winGame(int cards);
    };
}

#endif