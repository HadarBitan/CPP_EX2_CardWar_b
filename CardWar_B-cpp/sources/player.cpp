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

    void Player::createPack(Card cards[])
    {
        this->pack = cards;
    }

    Card Player::drawCard() 
    {
        if(this->cardsLeft == 0)
            return NULL;
        int num = rand() % 26;
        while(this->pack[num] == NULL)
        {
            num = rand() % 26;
        }
        this->cardsLeft--;
        Card card = this->pack[num];
        this->pack[num] = NULL;
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