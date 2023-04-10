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
        cout << this->status;
    }

    void Player::setStatus(int numberOfGames)
    {
        int winRate, drawRate, amountOfDraws;
        winRate = (this->numOfWins / numberOfGames) * 100;
        amountOfDraws = 26 - this->cardsLeft;
        drawRate = (amountOfDraws / numberOfGames) * 100;
        this->status = this->name + ": \nWin Rate- " + (char)winRate + 
        "%\nCards Won- " + (char)this->cardWon +
        "\nCards Left- " + (char)this->cardsLeft +
        "\nAmount Of Draws- " + (char)amountOfDraws +
        "\nDraw Rate- " + (char)drawRate + "%";
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