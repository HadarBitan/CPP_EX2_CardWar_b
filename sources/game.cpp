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
        //initialize all variables and dividing the cards to both players
        this->p1 = &p1;
        this->p2 = &p2;     
        //Reset the data for a new game
        this->p1->reMatch();
        this->p2->reMatch();   
        this->divideCards();
        this->numberOfGames = 0;
    }
    
    void Game::divideCards() 
    {
        //generate a fill pack of cards using vector(so we'll have the delete function)
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
        //division of the cards, 26 cards for each player
        for(int i = 0; i < 26; i++)
        {
            //geneate a random number between 1 and the size of the vector using rand()
            int num1 = rand() % (int)tempPack.size() + 1;
            //adding the card to the pack of the player
            this->p1->createPack(tempPack[(unsigned)num1]);
            //delete the card we gave the player from the vector
            tempPack.erase(tempPack.begin() + num1);
            //doing the same steps as we did above to the second player
            int num2 = rand() % (int)tempPack.size() + 1;
            this->p2->createPack(tempPack[(unsigned)num2]);
            tempPack.erase(tempPack.begin() + num2);
        }
    }

    void Game::playTurn() 
    {
        //if the players are the same then throw exception
        if(this->p1 == this->p2)
            throw std::exception();
        //case: both players run out of cards
        //checking if the players have cards to play, if not then update the winner and the turns stack and throw exception
        if(this->p1->stacksize() == 0 && this->p2->stacksize() == 0)
        {
            //checking which player won and updating the winner and the turns stack
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
        //update the number of games played and draw card from each player
        this->numberOfGames += 1;
        Card c1 = this->p1->drawCard();
        Card c2 = this->p2->drawCard();
        //case: player 1 got ace and player 2 got 2, 2 wins so player 2 gets 2 cards we update the turn status and exit the function
        if(c1.getCardNumber() == 1 && c2.getCardNumber() == 2)
        {
            this->p2->winGame(2);
            string stat = this->p1->getName() + " played Ace of " + c1.getCardSymbol() + " " +
            this->p2->getName() + " played 2 of " + c2.getCardSymbol() + ". " + this->p2->getName() + " wins.";
            this->turns.push(stat);
            return;
        }
        //case: player 1 got 2 and player 2 got ace, 2 wins so player 1 gets 2 cards we update the turn status and exit the function
        if(c1.getCardNumber() == 2 && c2.getCardNumber() == 1)
        {
            this->p1->winGame(2);
            string stat = this->p1->getName() + " played 2 of " + c1.getCardSymbol() + " " +
            this->p2->getName() + " played Ace of " + c2.getCardSymbol() + ". " + this->p1->getName() + " wins.";
            this->turns.push(stat);
            return;
        }
        //case: player 1 got ace and player 2 got something bigger then 2, ace wins so player 1 gets 2 cards we update the turn status and exit the function
        if(c1.getCardNumber() == 1 && c2.getCardNumber() > 2)
        {
            //Extract the string from the number of the card, to add the royal cards if the player played one of them
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
        //case: player 2 got ace and player 1 got something bigger then 2, ace wins so player 2 gets 2 cards we update the turn status and exit the function
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
        //case: player 1 got number bigger then player 2 got, player 1 wins so player 1 gets 2 cards we update the turn status and exit the function
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
        //case: player 2 got number bigger then player 1 got, player 2 wins so player 1 gets 2 cards we update the turn status and exit the function
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
        //case: both player got the same number then we have war
        if(c1.getCardNumber() == c2.getCardNumber())
        {
            //before starting a war we need to check if the player have cards
            if(this->p1->stacksize() == 0 && this->p2->stacksize() == 0)
            {
                //if they don't have more cards then each player gets his own pile and the game is over
                this->p1->winGame(1);
                this->p2->winGame(1);
                //checking which player won and updating the winner and the turns stack
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

            //after we verfied all the players still have cards we can continue in the war we give the recursive function the number of round we at
            //round - each time the player have the same number and we need to go into war
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
            //if they don't have more cards then each player gets his own pile and the game is over
            this->p1->winGame(2 * round);
            this->p2->winGame(2 * round);
            //checking which player won and updating the winner and the turns stack
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
                //if they don't have more cards then each player gets his own pile and the game is over
                this->p1->winGame(1 + (2 * round));
                this->p2->winGame(1 + (2 * round));
                //checking which player won and updating the winner and the turns stack
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
                        //if it's a tie will let the winner be tie and we'll throw exception in the function printWiner
                        this->winner = "tie";
                        this->turns.push("the game ended in a tie");
                        return;
                    }          
                }
            }

            //after we verfied all the players still have cards we can continue in the war, we go into the next round
            this->playWar(round + 1);
        }
    }

    void Game::printLastTurn() 
    {
        //printing the first string in the stack of turns
        cout << this->turns.top() << endl;
    }

    void Game::playAll() 
    {
        //as long as the packs don't runs out we play(calling the playturn function which play one turn)
        while(this->p1->stacksize() > 0 && this->p2->stacksize() > 0)
        {
            this->playTurn();
        }
        //checking which player has won and updatting the winner and the turns stack
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
        //printing the winner and if we get a tie we print it and throw an error
        cout << this->winner << endl;
        if(this->winner == "tie")
        {
            throw std::exception();
        }
    }

    void Game::printLog() 
    {
        //printing the turns one by one and adding it to the temp stack
        stack<string> temp;
        while(!this->turns.empty())
        {
            string turn = this->turns.top();
            temp.push(turn);
            cout << turn << endl;
            this->turns.pop();
        }
        //move all turns from the temp stack to the turns stack
        while(!temp.empty())
        {
            string turn = temp.top();
            this->turns.push(turn);
            temp.pop();
        }
    }

    void Game::printStats() 
    {
        //updating the status of both players
        this->p1->setStatus(this->numberOfGames);
        this->p2->setStatus(this->numberOfGames);
        //printing the status of both players
        this->p1->getStatus();
        this->p2->getStatus();
    }
}


