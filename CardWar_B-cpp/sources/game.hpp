#ifndef GAME_HPP
#define GAME_HPP

#pragma once


#include <iostream>
#include <string>
#include <stack>
#include "player.hpp"
#include "card.hpp"

using namespace std;

namespace ariel
{
    class Game
    {
    private:
        Player p1;
        Player p2;
        string winner;
        stack<string> turns;

    public:
        Game(Player first_player, Player second_player) :p1(first_player), p2(second_player) {};
        void generatePack();
        void divideCards();
        void playTurn();
        void printLastTurn();
        void playAll();
        void printWiner();
        void printLog();
        void printStats();
    };
}

#endif
