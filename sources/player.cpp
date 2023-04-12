#include <iostream>
#include <string>
#include "player.hpp"
#include "card.hpp"

using namespace std;

namespace ariel
{    
    Player::Player(string name)
    {
        //initialize all variables
        this->name = name;
        this->cardsLeft = 0;
        this->cardWon = 0;
        this->numOfWins = 0;
    }

    int Player::stacksize() 
    {
        //return how much cards the player got left
        return this->cardsLeft;
    }

    int Player::cardesTaken() 
    {
        //return how much cards the player won
        return this->cardWon;
    }

    void Player::createPack(Card card)
    {
        //adding a crad to the player pile- this function called only when a game is generate
        this->pack.push(card);
        this->cardsLeft++;
    }

    Card Player::drawCard() 
    {
        //drawing a card from the top of the pile and deleting it, also updating the amount of cards left
        this->cardsLeft--;
        Card card = this->pack.top();
        this->pack.pop();
        return card;
    }

    void Player::getStatus()
    {
        //printing the player basic statistics: win rate, cards won, cards left, draw rate and amount of draws that happand.
        cout << this->status << endl;
    }

    void Player::setStatus(int numberOfGames)
    {
        //set the basic statistics: win rate, cards won, cards left, draw rate and amount of draws that happand.
        //win rate = how many games the player won in relation to the number of games that happened
        //draw rate = how many draws the player did in relation to the number of games that happened
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
        //return the player name
        return this->name;
    }

    void Player::winGame(int cards)
    {
        //function to update the number of winning each time the player wins a game
        //and update the number of card he won
        this->cardWon += cards;
        this->numOfWins++;
    }

    void Player::reMatch()
    {
        //Reset the data for a new game
        this->cardWon = 0;
        this->numOfWins = 0;
        this->status = "";
    }
}