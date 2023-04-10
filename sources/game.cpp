#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <stdexcept>
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
        vector<Card> tempPack(52);
        string symbols[] = {"HEART", "CLUB", "DIAMOND", "SPADE"};
        int index = 0;
        for(int i = 1; i <= 13; i++)
        {
            for(int k = 0; k < 4; k++)
            {
                Card card(i, symbols[k]);
                tempPack.at(index++) = card;
            }
        }
        for(int i = 0; i < 26; i++)
        {
            int num1 = rand() % tempPack.size() + 1;
            this->p1.createPack(tempPack.at(num1));
            tempPack.erase(tempPack.begin() + num1);
            int num2 = rand() % tempPack.size() + 1;
            this->p2.createPack(tempPack.at(num2));
            tempPack.erase(tempPack.begin() + num2);
        }
    }

    void Game::playTurn() 
    {
        //case: both players run out of cards
        if(this->p1.stacksize() == 0 && this->p2.stacksize() == 0)
        {
            if(this->p1.cardesTaken() > this->p2.cardesTaken())
            {
                this->winner = this->p1.getName();
                this->turns.push("the game ended, the winner is " + this->winner);
                throw std::exception();
                return;
            }
            else
            {
                if(this->p1.cardesTaken() < this->p2.cardesTaken())
                {
                    this->winner = this->p2.getName();  
                    this->turns.push("the game ended, the winner is " + this->winner);
                    throw std::exception();
                    return;   
                }
                else
                {
                    //if it's a tie will let the wu=inner be tie and we'll throw exception in the function printWiner
                    this->winner = "tie";
                    this->turns.push("the game ended in a tie");
                    throw std::exception();
                    
                    return;
                }          
            }
        }    

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
            //before starting a war we need to check if the player have cards
            if(this->p1.stacksize() == 0 && this->p2.stacksize() == 0)
            {
                this->p1.winGame(1);
                this->p2.winGame(1);
                if(this->p1.cardesTaken() > this->p2.cardesTaken())
                {
                    this->winner = this->p1.getName();
                    this->turns.push("the game ended, the winner is " + this->winner);
                    throw std::exception();
                    return;
                }
                else
                {
                    if(this->p1.cardesTaken() < this->p2.cardesTaken())
                    {
                        this->winner = this->p2.getName(); 
                        this->turns.push("the game ended, the winner is " + this->winner); 
                        throw std::exception();
                        return;   
                    }
                    else
                    {
                        //if it's a tie will let the wu=inner be tie and we'll throw exception in the function printWiner
                        this->winner = "tie";
                        this->turns.push("the game ended in a tie");
                        throw std::exception();
                        return;
                    }          
                }
            }

            //after we verfied all the players still have cards we can continue in the war
            this->playWar(1);
        }
    }

    void Game::playWar(int round)
    {
        //we draw a card for the upside down card
        Card c1 = this->p1.drawCard();
        Card c2 = this->p2.drawCard();
        //checking if the players still have cards
        //case: both players run out of cards
        if(this->p1.stacksize() == 0 && this->p2.stacksize() == 0)
        {
            this->p1.winGame(2 * round);
            this->p2.winGame(2 * round);
            if(this->p1.cardesTaken() > this->p2.cardesTaken())
            {
                this->winner = this->p1.getName();
                this->turns.push("the game ended, the winner is " + this->winner);
                throw std::exception();
                return;
            }
            else
            {
                if(this->p1.cardesTaken() < this->p2.cardesTaken())
                {
                    this->winner = this->p2.getName();  
                    this->turns.push("the game ended, the winner is " + this->winner);
                    throw std::exception();
                    return;   
                }
                else
                {
                    //if it's a tie will let the wu=inner be tie and we'll throw exception in the function printWiner
                    this->winner = "tie";
                    this->turns.push("the game ended in a tie");
                    throw std::exception();
                    return;
                }          
            }
        }

        //if both of the players still have cards we play the open card and check what each of the players got
        c1 = this->p1.drawCard();
        c2 = this->p2.drawCard();
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
            //before continue with the war we need to check if the player have cards
            //case: both players run out of cards
            if(this->p1.stacksize() == 0 && this->p2.stacksize() == 0)
            {
                this->p1.winGame(1 + (2 * round));
                this->p2.winGame(1 + (2 * round));
                if(this->p1.cardesTaken() > this->p2.cardesTaken())
                {
                    this->winner = this->p1.getName();
                    this->turns.push("the game ended, the winner is " + this->winner);
                    throw std::exception();
                    return;
                }
                else
                {
                    if(this->p1.cardesTaken() < this->p2.cardesTaken())
                    {
                        this->winner = this->p2.getName();  
                        this->turns.push("the game ended, the winner is " + this->winner);
                        throw std::exception();
                        return;   
                    }
                    else
                    {
                        //if it's a tie will let the wu=inner be tie and we'll throw exception in the function printWiner
                        this->winner = "tie";
                        this->turns.push("the game ended in a tie");
                        throw std::exception();
                        return;
                    }          
                }
            }

            //after we verfied all the players still have cards we can continue in the war
            this->playWar(round + 1);
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
        if(this->winner == "tie")
        {
            throw std::exception();
        }
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


