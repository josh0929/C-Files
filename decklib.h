/*
File Name:            decklib.c
Author:               Joshua Suarez

=============================================================================

Description:          Library containing neccessary functions to simulate a
                      deck of 52 cards with the capability of creating a deck,
                      shuffling the deck, displaying the deck and dealing from
                      the deck to a user-specified number of players.

=============================================================================
*/

#include <stdio.h>          //Library for standar input/output
#include <time.h>           //Library that allows for retreival of current time
#include <stdlib.h>         //Imports rand() and srand() functions for random num
#include <locale.h>
#include "deck.h"
#include <wchar.h>          //The wchar.h header allows definition of wide
                            //character types for UNICODE suit characters

//enumeration constants represent card suit
enum Suit {
    HEARTS,
    DIAMONDS,
    SPADES,
    CLUBS
};

//Function prototypes
void createDeck( int deck[SUIT_HIGH][RANK_HIGH] );
void shuffleDeck( int deck[SUIT_HIGH][RANK_HIGH] );
void printDeck( int deck[SUIT_HIGH][RANK_HIGH] );
int playHand( int players, int handSize, int deck[SUIT_HIGH][RANK_HIGH] );
void printCard( int card );




/*
    Function:   void createDeck()

    Purpose:    Consists of constructing a new deck of 52 individual cards.
                A two-dimensional 13-by-4 array is used as the implementation
                method to represent the deck and each position of the array
                represents an individual card. A 2-D array is used based on the
                fact that each individual card is a permutation of two factors:

                    - The rank [A, 2, 3, …., J, Q, K] or [1 - 13]

                    - The suit [♡, ♢, ♧, ♤] which, in this case for the purpose
                      of the program, is represented in numerical form like
                      [1 - 4].

                For the array’s two dimensions, the vertical dimension
                represents the suit and the horizontal represents the
                rank. The following is an example of what is described above:

                          1(A) - 2  - 3  - ... - 11(J) - 12(Q) - 13(K)
                     1♡   [ ]  [ ]  [ ]   ...    [ ]     [ ]     [ ]
                     2♢   [ ]  [ ]  [ ]   ...    [ ]     [ ]     [ ]
                     3♧    [ ]  [ ]  [ ]  ...    [ ]     [ ]     [ ]
                     4♤    [ ]  [ ]  [ ]  ...    [ ]     [ ]     [ ]

                In conclusion, the array will consist of 4 rows and 13 columns
                which will give us 52 cards, hence 4 * 13 = 52.Each location is
                a combination of the row id, e.g. A or 1, and the corresponding
                column, e.g. 2, which is position row[1]|col[2] and represents
                card 2♡. Each card is represented by a unique number from
                [1 - 52] at each array position.

    @param deck 2-D array that represents the deck to be created

    @return void

*/
void createDeck( int deck[SUIT_HIGH][RANK_HIGH] ) {
    int row;
    int col;
    int card = INIT;      //card for each position

    //Initialize all 2-D array positions to 0
    for(row = SUIT_LOW; row < SUIT_HIGH; row++) {

        for(col = RANK_LOW; col < RANK_HIGH; col++) {
            deck[row][col] = INIT;
        }//end for loop ==============================

    }//end for loop ==================================

    //Populate array horizontally with numbers in sequence from 1 to 52
    for(row = SUIT_LOW; row < SUIT_HIGH; row++) {

        for(col = RANK_LOW; col < RANK_HIGH; col++) {
            deck[row][col] = ++card;
        }//end for loop =============================

    }//end for loop =================================
}


/*
    Function:   void shuffleDeck()

    Purpose:    Accept an organized deck and randomly reposition the
                values. A two-dimensional array is passed via the function
                arguments and is traversed horizontally at each row. At each
                iteration, a random row and column is calculated. The random
                row and column numbers are stored and used to swap with the
                value located at the original row and column position defined
                by the for loop. A time() function is used to determine the
                amount of seconds that have passed sin January 1st, 1970, and
                is used to seed the random function to produce a random integer
                at each iteration.

    Citations:  How to program C - Deitel & Deitel - pg-177

    @param deck 2-D array that represents the deck to be shuffled

    @return void

*/
void shuffleDeck( int deck[SUIT_HIGH][RANK_HIGH] ) {
    int row;
    int col;          //row and column of array
    int randomRow;
    int randomCol;    //random row and col of the array

    srand( time(NULL) );  //seed the rand() function

    for(row = SUIT_LOW; row < SUIT_HIGH; row++) {

        for(col = RANK_LOW; col < RANK_HIGH; col++) {
            int temp = deck[row][col];

            //get random position
            randomRow = rand() % SUIT_HIGH;
            randomCol = rand() % RANK_HIGH;

            //swap random position with current position
            deck[row][col] = deck[randomRow][randomCol];
            deck[randomRow][randomCol] = temp;
        }//end for loop =================================

    }//end for loop =====================================
}


/*
    Function:   void printDeck()

    Purpose:    Traverses the deck and prints card at each position displaying
                a total of 8 cards per line until all cards have been printed.
                Reminder that at each position the value is a number from 1 to
                52. This value is stred and passed to the printCard() function
                that detrmines the appropriate rank and suit and prints the
                card. Example display:

                [  1♣ ][  6♠ ][ 13♣ ][ 12♦ ][  7♥ ][  8♥ ][  2♦ ][ 10♣ ]
                [  6♦ ][  4♦ ][  5♠ ][ 12♥ ][  9♦ ][  6♥ ][  3♦ ][ 13♠ ]
                [  1♦ ][  5♣ ][  8♠ ][  4♠ ][  6♣ ][ 10♠ ][  3♠ ][  7♣ ]
                [ 12♣ ][  7♠ ][  8♣ ] etc...


    @param deck 2-D array that represents the deck to be displayed

    @return void

*/
void printDeck( int deck[SUIT_HIGH][RANK_HIGH] ) {
    int row;
    int col;
    int rowCount = INIT; //count maintained to print 10 cards per row

    for(row = SUIT_LOW; row < SUIT_HIGH; row++) {

        for(col = RANK_LOW; col < RANK_HIGH; col++) {
            int currentCard = deck[row][col];

            if(rowCount < ROW_LIMIT) {
                printCard( currentCard );
                rowCount++;
            }
            else {
                printCard( currentCard );
                rowCount = INIT;
                wprintf(L"%s\n", "");
            }
        }//end for loop ===============================

    }//end for loop ===================================

    wprintf(L"%s\n\n", "");
}


/*
    Function:   int playHand()

    Purpose:

    @param      players - amount of players
                handSize - amoutn of cards per player

    @return int 0 if successful or 1 if failed

*/
int playHand( int players, int handSize, int deck[SUIT_HIGH][RANK_HIGH] ) {

    if(players * handSize > DECK_SIZE || players * handSize < 1) {
        return 1; //Not enough cards to play. Exit function
    }
    else {
        int row = SUIT_LOW;
        int col = RANK_LOW;
        int playerCount = 1;  //initialize to minimum 1 player

        while(playerCount <= players) {
            wprintf(L"Player %d hand:\n", playerCount);
            int cardCount = INIT; //count cards handed out per hand

            for(; row < SUIT_HIGH; row++) {
                for(; col < RANK_HIGH; col++) {
                    if( cardCount < handSize ) {
                        int card = deck[row][col];
                        deck[row][col] = -1;  //-1 to represent empty array position
                        printCard( card );

                        cardCount++;
                    }
                    else {
                        break;
                    }
                }//end column for loop ================
                if( col == RANK_HIGH && cardCount < handSize ) {
                    col = RANK_LOW;
                }
                else {
                    break;
                }
            }//end row for loop =======================

            wprintf(L"%s\n\n", "");
            playerCount++;
        }//end while loop =============================

        return 0;
    }
}


/*
    Function:   int printCard()

    Purpose:    Accepts an integer which represnts the card to be printed. The
                function first determines the rank which is produced by the
                result of the modulus of the number and the maximum rank (13).
                Since the deck is originally populated sequentially, each row
                represents a suit with all columns of that row representing the
                rank of that suit. The method used to find the suit is to
                compare to find the range in which the number falls (for example,
                if the number falls between 1-13 the suit is HEARTS).

    Citations:  N/A

    @param int card -card to be printed

    @return void

*/
void printCard( int card ) {
    int rank = card % RANK_HIGH; //get rank of current number
    wchar_t suit = INIT;

    setlocale(LC_CTYPE, "");

    if(rank == 0) {
        rank = RANK_HIGH;
    }

    //Print correct suit unicode character and rank
    if( card >= HEART_RANGE_LOW &&
      card <= HEART_RANGE_HIGH ) {
        suit = HEART_SYMBOL;
    }
    else if( card >= DIAMOND_RANGE_LOW &&
      card <= DIAMOND_RANGE_HIGH ) {
        suit = DIAMOND_SYMBOL;
    }
    else if( card >= SPADES_RANGE_LOW &&
      card <= SPADES_RANGE_HIGH ) {
        suit = SPADES_SYMBOL;
      }
    else if( card >= CLUBS_RANGE_LOW &&
      card <= CLUBS_RANGE_HIGH ) {
        //currentCard falls between CLUBS_RANGE LOW && HIGH
        suit = CLUBS_SYMBOL;
    }
    else {
        suit = JOKER_SYMBOL;
    }

    wprintf(L" [%3d%lc ] ", rank, suit);
}
