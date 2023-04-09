#include <iostream>
#include <string>
#include <stack>
#include "player.hpp"
#include "card.hpp"
#include "game.hpp"

using namespace std;

namespace ariel
{
    Game::Game(Player p1, Player p2) :p1(p1), p2(p2)
    {
        this->p1 = p1;
        this->p2 = p2;
        this->divideCards();
    }

    void Game::divideCards() 
    {
        Card tempPack[52];
        string symbols[4] = {"HEART, CLUB, DIAMOND, SPADE"};
        int index = 0;
        for(int i = 1; i <= 13; i++)
        {
            for(int k = 0; k < 4; k++)
            {
                Card card(i, symbols[k]);
                tempPack[index++] = card;
            }
        }
        Card p1pack[26];
        Card p2pack[26];
        int index1 = 0, index2 = 0;
        for(int i = 0; i < 26; i++)
        {
            int num1 = rand() % 52 + 1;
            while(tempPack[num1] == NULL)
            {
                num1 = rand() % 52 + 1;
            }
            p1pack[index1++] = tempPack[num1];
            tempPack[num1] = NULL;
            int num2 = rand() % 52 + 1;
            while(num2 != num1 && tempPack[num2] == NULL)
            {
                num2 = rand() % 52 + 1;
            }
            p2pack[index2++] = tempPack[num2];
            tempPack[num2] = NULL;
        }
        this->p1.createPack(p1pack);
        this->p2.createPack(p2pack);
    }

    void Game::playTurn() 
    {
        Card c1 = this->p1.drawCard();
        Card c2 = this->p2.drawCard();
        if(c1.getCardNumber() == 1 && c2.getCardNumber() == 2)
        {
            this->p2.winGame(1);
            string stat = this->p1.getName() + " played 1 of " + c1.getCardSymbol() + " " +
            this->p2.getName() + " played 2 of " + c2.getCardSymbol() + ". " + this->p2.getName() + " wins.";
            this->turns.push(stat);
            return;
        }
        if(c1.getCardNumber() == 2 && c2.getCardNumber() == 1)
        {
            this->p1.winGame(1);
            string stat = this->p1.getName() + " played 2 of " + c1.getCardSymbol() + " " +
            this->p2.getName() + " played 1 of " + c2.getCardSymbol() + ". " + this->p1.getName() + " wins.";
            this->turns.push(stat);
            return;
        }
        if(c1.getCardNumber() == 1 && c1.getCardNumber() != c2.getCardNumber())
        {
            this->p1.winGame(1);
            string stat = this->p1.getName() + " played 1 of " + c1.getCardSymbol() + " " +
            this->p2.getName() + " played " + (char)c2.getCardNumber() + " of " + c2.getCardSymbol() + ". " + this->p1.getName() + " wins.";
            this->turns.push(stat);
            return;
        }
        if(c2.getCardNumber() == 1 && c1.getCardNumber() != c2.getCardNumber())
        {
            this->p2.winGame(1);
            string stat = this->p2.getName() + " played 1 of " + c2.getCardSymbol() + " " +
            this->p1.getName() + " played " + (char)c1.getCardNumber() + " of " + c1.getCardSymbol() + ". " + this->p2.getName() + " wins.";
            this->turns.push(stat);
            return;
        }
        if(c1.getCardNumber() > c2.getCardNumber())
        {
            this->p1.winGame(1);
            string stat = this->p1.getName() + " played " + (char)c1.getCardNumber() + " of " + c1.getCardSymbol() + " " +
            this->p2.getName() + " played " + (char)c2.getCardNumber() + " of " + c2.getCardSymbol() + ". " + this->p1.getName() + " wins.";
            this->turns.push(stat);
            return;
        }
        if(c1.getCardNumber() < c2.getCardNumber())
        {
            this->p2.winGame(1);
            string stat = this->p1.getName() + " played " + (char)c1.getCardNumber() + " of " + c1.getCardSymbol() + " " +
            this->p2.getName() + " played " + (char)c2.getCardNumber() + " of " + c2.getCardSymbol() + ". " + this->p2.getName() + " wins.";
            this->turns.push(stat);
            return;
        }
        if(c1.getCardNumber() == c2.getCardNumber())
        {
            
        }
    }

    void Game::printLastTurn() 
    {
        cout << this->turns.top();
    }

    void Game::playAll() 
    {
        while(this->p1.drawCard() != NULL || this->p2.drawCard() != NULL)
        {
            this->playTurn();
        }
    }

    void Game::printWiner() 
    {
        cout << this->winner;
    }

    void Game::printLog() 
    {
        stack<string> temp;
        while(!this->turns.empty())
        {
            string turn = this->turns.top();
            temp.push(turn);
            cout << turn << endl;
            this->turns.pop();
        }
        while(!temp.empty())
        {
            string turn = temp.top();
            this->turns.push(turn);
            temp.pop();
        }
    }

    void Game::printStats() 
    {
        this->p1.getStatus();
        this->p2.getStatus();
    }
}


