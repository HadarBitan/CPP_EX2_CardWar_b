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
        this->cardsLeft = 26;
        this->cardWon = 0;
    }

    int Player::stacksize() {return this->cardsLeft;}

    int Player::cardesTaken() {return this->cardWon;}

    void Player::createPack(Card card)
    {
        this->pack.push(card);
    }

    Card Player::drawCard() 
    {
        if(!this->pack.empty())
            return NULL;
        this->cardsLeft--;
        Card card = this->pack.top();
        this->pack.pop();
        return card;
    }

    void Player::getStatus()
    {
        cout << this->status;
    }

    void Player::setStatus(){}

    string Player::getName() const
    {
        return this->name;
    }
}