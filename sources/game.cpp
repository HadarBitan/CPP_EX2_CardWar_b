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
    Game::Game(Player & p1, Player & p2)
    {
        this->p1 = &p1;
        this->p2 = &p2;
        this->divideCards();
        this->numberOfGames = 0;
    }
    
    void Game::divideCards() 
    {
        vector<Card> tempPack;
        string symbols[] = {"HEART", "CLUB", "DIAMOND", "SPADE"};
        for(int i = 1; i <= 13; i++)
        {
            for(int k = 0; k < 4; k++)
            {
                Card card(i, symbols[k]);
                tempPack.push_back(card);
            }
        }
        for(int i = 0; i < 26; i++)
        {
            int num1 = rand() % (int)tempPack.size() + 1;
            this->p1->createPack(tempPack[(unsigned)num1]);
            tempPack.erase(tempPack.begin() + num1);
            int num2 = rand() % (int)tempPack.size() + 1;
            this->p2->createPack(tempPack[(unsigned)num2]);
            tempPack.erase(tempPack.begin() + num2);
        }
    }

    void Game::playTurn() 
    {
        if(this->p1 == this->p2)
            throw std::exception();
        //case: both players run out of cards
        if(this->p1->stacksize() == 0 && this->p2->stacksize() == 0)
        {
            if(this->p1->cardesTaken() > this->p2->cardesTaken())
            {
                this->winner = this->p1->getName();
                this->turns.push("the game ended, the winner is " + this->winner);
                throw std::exception();
            }
            else
            {
                if(this->p1->cardesTaken() < this->p2->cardesTaken())
                {
                    this->winner = this->p2->getName();  
                    this->turns.push("the game ended, the winner is " + this->winner);
                    throw std::exception();
                }
                else
                {
                    //if it's a tie will let the wu=inner be tie and we'll throw exception in the function printWiner
                    this->winner = "tie";
                    this->turns.push("the game ended in a tie");
                    throw std::exception();
                }          
            }
        }    
        this->numberOfGames += 1;
        Card c1 = this->p1->drawCard();
        Card c2 = this->p2->drawCard();
        if(c1.getCardNumber() == 1 && c2.getCardNumber() == 2)
        {
            this->p2->winGame(2);
            string stat = this->p1->getName() + " played Ace of " + c1.getCardSymbol() + " " +
            this->p2->getName() + " played 2 of " + c2.getCardSymbol() + ". " + this->p2->getName() + " wins.";
            this->turns.push(stat);
            return;
        }
        if(c1.getCardNumber() == 2 && c2.getCardNumber() == 1)
        {
            this->p1->winGame(2);
            string stat = this->p1->getName() + " played 2 of " + c1.getCardSymbol() + " " +
            this->p2->getName() + " played Ace of " + c2.getCardSymbol() + ". " + this->p1->getName() + " wins.";
            this->turns.push(stat);
            return;
        }
        if(c1.getCardNumber() == 1 && c2.getCardNumber() > 2)
        {
            string numberName;
            if(c2.getCardNumber() == 11)
                numberName = "Jack";
            if(c2.getCardNumber() == 12)
                numberName = "Queen";
            if(c2.getCardNumber() == 13)
                numberName = "King";
            else
                numberName = std::to_string(c2.getCardNumber());
            this->p1->winGame(2);
            string stat = this->p1->getName() + " played Ace of " + c1.getCardSymbol() + " " +
            this->p2->getName() + " played " + numberName + " of " + c2.getCardSymbol() + ". " + this->p1->getName() + " wins.";
            this->turns.push(stat);
            return;
        }
        if(c2.getCardNumber() == 1 && c1.getCardNumber() > 2)
        {
            this->p2->winGame(2);
            string numberName;
            if(c1.getCardNumber() == 11)
                numberName = "Jack";
            if(c1.getCardNumber() == 12)
                numberName = "Queen";
            if(c1.getCardNumber() == 13)
                numberName = "King";
            else
                numberName = std::to_string(c1.getCardNumber());

            string stat = this->p2->getName() + " played Ace of " + c2.getCardSymbol() + " " +
            this->p1->getName() + " played " + numberName + " of " + c1.getCardSymbol() + ". " + this->p2->getName() + " wins.";
            this->turns.push(stat);
            return;
        }
        if(c1.getCardNumber() > c2.getCardNumber())
        {
            this->p1->winGame(2);
            string numberName1, numberName2;
            if(c1.getCardNumber() == 11)
                numberName1 = "Jack";
            if(c1.getCardNumber() == 12)
                numberName1 = "Queen";
            if(c1.getCardNumber() == 13)
                numberName1 = "King";
            else
                numberName1 = std::to_string(c1.getCardNumber());

            if(c2.getCardNumber() == 11)
                numberName2 = "Jack";
            if(c2.getCardNumber() == 12)
                numberName2 = "Queen";
            if(c2.getCardNumber() == 13)
                numberName2 = "King";
            else
                numberName2 = std::to_string(c2.getCardNumber());

            string stat = this->p1->getName() + " played " + numberName1 + " of " + c1.getCardSymbol() + " " +
            this->p2->getName() + " played " + numberName2 + " of " + c2.getCardSymbol() + ". " + this->p1->getName() + " wins.";
            this->turns.push(stat);
            return;
        }
        if(c1.getCardNumber() < c2.getCardNumber())
        {
            this->p2->winGame(2);
            string numberName1, numberName2;
            if(c1.getCardNumber() == 11)
                numberName1 = "Jack";
            if(c1.getCardNumber() == 12)
                numberName1 = "Queen";
            if(c1.getCardNumber() == 13)
                numberName1 = "King";
            else
                numberName1 = std::to_string(c1.getCardNumber());

            if(c2.getCardNumber() == 11)
                numberName2 = "Jack";
            if(c2.getCardNumber() == 12)
                numberName2 = "Queen";
            if(c2.getCardNumber() == 13)
                numberName2 = "King";
            else
                numberName2 = std::to_string(c2.getCardNumber());

            string stat = this->p1->getName() + " played " + numberName1 + " of " + c1.getCardSymbol() + " " +
            this->p2->getName() + " played " + numberName2 + " of " + c2.getCardSymbol() + ". " + this->p2->getName() + " wins.";
            this->turns.push(stat);
            return;
        }
        if(c1.getCardNumber() == c2.getCardNumber())
        {
            //before starting a war we need to check if the player have cards
            if(this->p1->stacksize() == 0 && this->p2->stacksize() == 0)
            {
                this->p1->winGame(1);
                this->p2->winGame(1);
                if(this->p1->cardesTaken() > this->p2->cardesTaken())
                {
                    this->winner = this->p1->getName();
                    this->turns.push("the game ended, the winner is " + this->winner);
                    return;
                }
                else
                {
                    if(this->p1->cardesTaken() < this->p2->cardesTaken())
                    {
                        this->winner = this->p2->getName(); 
                        this->turns.push("the game ended, the winner is " + this->winner); 
                        return;
                    }
                    else
                    {
                        //if it's a tie will let the wu=inner be tie and we'll throw exception in the function printWiner
                        this->winner = "tie";
                        this->turns.push("the game ended in a tie");
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
        Card c1 = this->p1->drawCard();
        Card c2 = this->p2->drawCard();
        //checking if the players still have cards
        //case: both players run out of cards
        if(this->p1->stacksize() == 0 && this->p2->stacksize() == 0)
        {
            this->p1->winGame(2 * round);
            this->p2->winGame(2 * round);
            if(this->p1->cardesTaken() > this->p2->cardesTaken())
            {
                this->winner = this->p1->getName();
                this->turns.push("the game ended, the winner is " + this->winner);
                return;
            }
            else
            {
                if(this->p1->cardesTaken() < this->p2->cardesTaken())
                {
                    this->winner = this->p2->getName();  
                    this->turns.push("the game ended, the winner is " + this->winner);
                    return;
                }
                else
                {
                    //if it's a tie will let the wu=inner be tie and we'll throw exception in the function printWiner
                    this->winner = "tie";
                    this->turns.push("the game ended in a tie");
                    return;
                }          
            }
        }

        //if both of the players still have cards we play the open card and check what each of the players got
        c1 = this->p1->drawCard();
        c2 = this->p2->drawCard();
        if(c1.getCardNumber() == 1 && c2.getCardNumber() == 2)
        {
            this->p2->winGame(2 * (1 + (2 * round)));
            string stat = this->p1->getName() + " played Ace of " + c1.getCardSymbol() + " " +
            this->p2->getName() + " played 2 of " + c2.getCardSymbol() + ". " + this->p2->getName() + " wins.";
            this->turns.push(stat);
            return;
        }
        if(c1.getCardNumber() == 2 && c2.getCardNumber() == 1)
        {
            this->p1->winGame(2 * (1 + (2 * round)));
            string stat = this->p1->getName() + " played 2 of " + c1.getCardSymbol() + " " +
            this->p2->getName() + " played Ace of " + c2.getCardSymbol() + ". " + this->p1->getName() + " wins.";
            this->turns.push(stat);
            return;
        }
        if(c1.getCardNumber() == 1 && c2.getCardNumber() > 2)
        {
            this->p1->winGame(2 * (1 + (2 * round)));
            string numberName;
            if(c2.getCardNumber() == 11)
                numberName = "Jack";
            if(c2.getCardNumber() == 12)
                numberName = "Queen";
            if(c2.getCardNumber() == 13)
                numberName = "King";
            else
                numberName = std::to_string(c2.getCardNumber());

            string stat = this->p1->getName() + " played Ace of " + c1.getCardSymbol() + " " +
            this->p2->getName() + " played " + numberName + " of " + c2.getCardSymbol() + ". " + this->p1->getName() + " wins.";
            this->turns.push(stat);
            return;
        }
        if(c2.getCardNumber() == 1 && c1.getCardNumber() > 2)
        {
            this->p2->winGame(2 * (1 + (2 * round)));
            string numberName;
            if(c1.getCardNumber() == 11)
                numberName = "Jack";
            if(c1.getCardNumber() == 12)
                numberName = "Queen";
            if(c1.getCardNumber() == 13)
                numberName = "King";
            else
                numberName = std::to_string(c1.getCardNumber());

            string stat = this->p2->getName() + " played Ace of " + c2.getCardSymbol() + " " +
            this->p1->getName() + " played " + numberName + " of " + c1.getCardSymbol() + ". " + this->p2->getName() + " wins.";
            this->turns.push(stat);
            return;
        }
        if(c1.getCardNumber() > c2.getCardNumber())
        {
            this->p1->winGame(2 * (1 + (2 * round)));
            string numberName1, numberName2;
            if(c1.getCardNumber() == 11)
                numberName1 = "Jack";
            if(c1.getCardNumber() == 12)
                numberName1 = "Queen";
            if(c1.getCardNumber() == 13)
                numberName1 = "King";
            else
                numberName1 = std::to_string(c1.getCardNumber());

            if(c2.getCardNumber() == 11)
                numberName2 = "Jack";
            if(c2.getCardNumber() == 12)
                numberName2 = "Queen";
            if(c2.getCardNumber() == 13)
                numberName2 = "King";
            else
                numberName2 = std::to_string(c2.getCardNumber());

            string stat = this->p1->getName() + " played " + numberName1 + " of " + c1.getCardSymbol() + " " +
            this->p2->getName() + " played " + numberName2 + " of " + c2.getCardSymbol() + ". " + this->p1->getName() + " wins.";
            this->turns.push(stat);
            return;
        }
        if(c1.getCardNumber() < c2.getCardNumber())
        {
            this->p2->winGame(2 * (1 + (2 * round)));
            string numberName1, numberName2;
            if(c1.getCardNumber() == 11)
                numberName1 = "Jack";
            if(c1.getCardNumber() == 12)
                numberName1 = "Queen";
            if(c1.getCardNumber() == 13)
                numberName1 = "King";
            else
                numberName1 = std::to_string(c1.getCardNumber());

            if(c2.getCardNumber() == 11)
                numberName2 = "Jack";
            if(c2.getCardNumber() == 12)
                numberName2 = "Queen";
            if(c2.getCardNumber() == 13)
                numberName2 = "King";
            else
                numberName2 = std::to_string(c2.getCardNumber());

            string stat = this->p1->getName() + " played " + numberName1 + " of " + c1.getCardSymbol() + " " +
            this->p2->getName() + " played " + numberName2 + " of " + c2.getCardSymbol() + ". " + this->p2->getName() + " wins.";
            this->turns.push(stat);
            return;
        }
        if(c1.getCardNumber() == c2.getCardNumber())
        {
            //before continue with the war we need to check if the player have cards
            //case: both players run out of cards
            if(this->p1->stacksize() == 0 && this->p2->stacksize() == 0)
            {
                this->p1->winGame(1 + (2 * round));
                this->p2->winGame(1 + (2 * round));
                if(this->p1->cardesTaken() > this->p2->cardesTaken())
                {
                    this->winner = this->p1->getName();
                    this->turns.push("the game ended, the winner is " + this->winner);
                    return;
                }
                else
                {
                    if(this->p1->cardesTaken() < this->p2->cardesTaken())
                    {
                        this->winner = this->p2->getName();  
                        this->turns.push("the game ended, the winner is " + this->winner);
                        return;   
                    }
                    else
                    {
                        //if it's a tie will let the wu=inner be tie and we'll throw exception in the function printWiner
                        this->winner = "tie";
                        this->turns.push("the game ended in a tie");
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
        cout << this->turns.top() << endl;
    }

    void Game::playAll() 
    {
        while(this->p1->stacksize() > 0 && this->p2->stacksize() > 0)
        {
            this->playTurn();
        }
        if(this->p1->cardesTaken() > this->p2->cardesTaken())
        {
            this->winner = this->p1->getName();
            this->turns.push("the game ended, the winner is " + this->winner);
        }
        else
        {
            if(this->p1->cardesTaken() < this->p2->cardesTaken())
            {
                this->winner = this->p2->getName();  
                this->turns.push("the game ended, the winner is " + this->winner);
            }
            else
            {
                //if it's a tie will let the wu=inner be tie and we'll throw exception in the function printWiner
                this->winner = "tie";
                this->turns.push("the game ended in a tie");
            }          
        }
    }

    void Game::printWiner() 
    {
        cout << this->winner << endl;
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
        this->p1->setStatus(this->numberOfGames);
        this->p2->setStatus(this->numberOfGames);
        this->p1->getStatus();
        this->p2->getStatus();
    }
}


