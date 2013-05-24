/* Kody Alan Kantor
 *
 * Blackjack game.
 *
 * This game allows a user to play blackjack.
 *
 * File scope variables:
 *  short cards[]
 *   This contains the deck of cards. Aces are only worth one, face
 *   cards are represented by the number '10'
 *
 * Methods:
 * bool askTheUser(char *)
 *  Asks the user a yes/no question. Returns a boolean true for 'yes',
 *  and a boolean false for 'no.' Used for starting the game, asking
 *  if the user would like to hit/stay.
 *
 * int main(void)
 *  Starts the game, controls the game depending on the responses
 *  of the user.
 *  
 * int drawCard(void)
 *  Draws a random card from the deck. Then sets the card value to -1,
 *  so that it cannot be drawn again.
 *
 * void playBlackJack(void)
 *  Actually plays the blackjack game. It keeps track of scores,
 *  knows the rules of the game, etc.
 *
 *
 * Mod History:
 *  5-21-13: Original Compilation
 *  5-23-13: Added playBlackJack method.
 *
 * Future work:
 *  Write a file of the statistics of each game.
 *  Have more than one deck.
 *  Shuffle the deck, rather than generating a random number to pick
 *      from the deck
 */


#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

bool    askTheUser (char *);
short   drawCard   (void);
void    discard    (int);
void    playBlackJack(void);

// File scope variable //
short cards[] = {1,2,3,4,5,6,7,8,9,10,10,10,10,
               1,2,3,4,5,6,7,8,9,10,10,10,10,
               1,2,3,4,5,6,7,8,9,10,10,10,10,
               1,2,3,4,5,6,7,8,9,10,10,10,10};

int main (void)
{
    bool        userInput;
    
    srand (time(NULL));
    while(askTheUser("Would you like to play blackjack? (Yes or No) "))
    {
        playBlackJack();
    }

    return      0;
}

void playBlackJack()
{
    short card0,        card1;
    short dealer0,      dealer1;
    short playerTotal,  dealerTotal;

    card0       =   drawCard();
    card1       =   drawCard();
    dealer0     =   drawCard();
    dealer1     =   drawCard();
    
    playerTotal =   card0   +   card1;
    dealerTotal =   dealer0 +   dealer1;

    printf("Your cards are: %d, and %d.\nYour total is %d.\nDealer has %d and an unknown card.\n", card0, card1, playerTotal, dealer0);
    
    if(playerTotal == 21)
    {
        puts("You have 21!");
    }
    else
    {
        while(playerTotal < 21)
        {
            if(askTheUser("Would you like to hit? (Yes or No) "))
            {
                card0       =   drawCard();
                playerTotal =   playerTotal + card0;
                printf      ("\n\nYou drew a %d.\nYour total is now %d\n", card0, playerTotal);
            }
            else break;
        }
        if(playerTotal > 21)
        {
            puts("You bust!");
        }
        else if(playerTotal == 21)
        {
            puts("You got 21!");
        }
        else printf ("Your total is %d.\n",    playerTotal);
    }
    if(playerTotal <= 21)
    {
        while(dealerTotal < 17)
        {
            dealer0     =   drawCard();
            dealerTotal =   dealerTotal + dealer0;
            printf("\n\nThe dealer drew a %d.\nDealer's total is now %d\n", dealer0, dealerTotal);
        }
        if(dealerTotal > 21)
        {
            puts("The dealer busts!");
        }
        else if(dealerTotal == 21)
        {
            puts("Dealer got 21!");
        }
    }
    printf("Your total: %d\nDealer's total: %d\n", playerTotal, dealerTotal);
}

short drawCard(void)
{
    short             randomNumber;
    short             i;
    short             result;

    randomNumber    =   rand() % 52;

    if(cards[randomNumber] < 0)
    {
        while(randomNumber < 52)
        {
            if(cards[randomNumber] > 0)
            {
                result  =   cards[randomNumber];
                discard(randomNumber);
                break;
            }

            randomNumber++;

            if(randomNumber >= 52)
            {
                randomNumber = randomNumber % 52;
            }
        }
    }
    else
    {
        result  =   cards[randomNumber];
        discard(cards[randomNumber]);
    }

    return result;
}

void discard(int cardPosition)
{
    cards[cardPosition] = -1;
}

bool askTheUser (char * message)
{
    bool        result;
    char        inputString[10];
    int         i;
    
    do
    {
        printf  (message);
        gets    (inputString);
        for(i = 0; i < sizeof(inputString); i++)
        {
            inputString[i]  =   tolower(inputString[i]);
            //changes the new string to lowercase
        }
        if(strcmp(inputString, "yes") == 0 || strcmp(inputString, "y") == 0)
        {
            result      =   true;
            break;
            //if the result is 'yes' or 'y,' the loop will stop
        }
        else if(strcmp(inputString, "no") == 0 || strcmp(inputString, "n") == 0)
        {
            result      =   false;
            break;
            //if the result is 'no' or 'n,' the loop will stop
        }
    }//end loop to ask the user;
    while(true);
    
    return  result;
}
