#include <iostream>
#include <string>
#include "player.hpp"
#include "card.hpp"

using namespace std;

namespace ariel
{    
    Player::Player(string name)
    {
        this->name = name;
        this->cardsLeft = 0;
        this->cardWon = 0;
        this->numOfWins = 0;
    }

    int Player::stacksize() 
    {
        return this->cardsLeft;
    }

    int Player::cardesTaken() 
    {
        return this->cardWon;
    }

    void Player::createPack(Card card)
    {
        this->pack.push(card);
        this->cardsLeft++;
    }

    Card Player::drawCard() 
    {
        this->cardsLeft--;
        Card card = this->pack.top();
        this->pack.pop();
        return card;
    }

    void Player::getStatus()
    {
        cout << this->status << endl;
    }

    void Player::setStatus(int numberOfGames)
    {
        double winRate, drawRate;
        int amountOfDraws;
        winRate = (this->numOfWins * 100) / numberOfGames;
        amountOfDraws = 26 - this->cardsLeft;
        drawRate = (amountOfDraws * 100) / numberOfGames;
        this->status = this->name + ": \nWin Rate- " + std::to_string(winRate) + 
        "\nCards Won- " + std::to_string(this->cardWon) +
        "\nCards Left- " + std::to_string(this->cardsLeft) +
        "\nAmount Of Draws- " + std::to_string(amountOfDraws) +
        "\nDraw Rate- " + std::to_string(drawRate);
    }

    string Player::getName() const
    {
        return this->name;
    }

    void Player::winGame(int cards)
    {
        this->cardWon += cards;
        this->numOfWins++;
    }

}