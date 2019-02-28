/*
File Name:            deckmain.c
Author:               Joshua Suarez
Panther ID:           6041323
Assignment:           Assignment 3

Course Name/Number:   Programming III - COP-4338
Instructor:           William Feild Jr.
Due Date:             February 26th 2019

    I hereby certify that this collective work is my own and
    none of it is the work of any other person or entity.

    ______________________________________ [Signature]

=============================================================================

Description:          The following program is a simulation of a conventional
                      deck of cards consisting of 52 cards (13 ranks and 4 suits)
                      in which a deck is created in order of suit and rank. This
                      simulation will be capable of creating a new deck,
                      shuffling the deck, displaying both the original or the
                      shuffled deck and dealing a user-specified number of cards
                      per hand to a user-specified number of players.

              Input - Input will be provided by the user via command-line
                      arguments. A total of three arguments are needed for
                      program execution consisting of the program name, the
                      number of cards per player to be dealt and the number of
                      players.

             Output - Output will display the original deck of cards upon
                      creation consisting of the 52-card deck in order of SUIT
                      and RANK. A shuffle function, shuffles the deck randomly
                      and a second display of the deck is shown with the card
                      shuffled randomly. Lastly, each players hand is displayed
                      showing each card dealt to each player from the top of the
                      deck.


Known Bugs:           Validation provides incorrect feedback while validating
                      letters versus numbers.

Compile               Two options are available to compile:
                          - Use gcc compiler by typing in the following
                          commands into your shell:
                              - gcc -o deckmain deck.h decklib.h deckmain.c

                          - Use makefile including with this package by typing
                          in the following commands:
                              -

Execution:            Only three parameters are required. To execute, enter the
                      following commands:
                          - ./deckmain (The program)
                          - [Number of players]
                          - [Number of cards per player to be dealt]

                          - EXAMPLE:
                              ./deckmain 5 6

=============================================================================
*/

#include <stdio.h>            //Library for standar input/output
#include <ctype.h>            //Utilized for type conversion methods atoi()
#include "decklib.h"          //user defined header containing all functions
#include "deck.h"             //user defined header containing all symbolic
                              //constants needed for program calculations

#define INT_ASCII_LOW 48      //ASCII decimal value for number 0
#define INT_ASCII_HIGH 57     //ASCII decimal value for number 9
#define ARGS_TOTAL 3          //Minimum command-line arguments required for
                              //program execution

int main(int argc, char const *argv[]) {
    int INPUT_PLAYERS;  //Const to store user input for amount of players
    int INPUT_HAND;     //Constant to store user input for hand size

    //input validation ========================================================
    if( argc != ARGS_TOTAL ) {
        puts("Usage: deckmain [Hand] [Players]\n");
    }
    else {
        int arg_one = *argv[1];
        int arg_two = *argv[2];

        //validate if char is a number
        if( (arg_one < INT_ASCII_LOW && arg_one > INT_ASCII_HIGH) ||
          (arg_two < INT_ASCII_LOW && arg_two > INT_ASCII_HIGH) ) {
            puts("Error. Arguments must be numbers only.");
        }
        else {
            int hand = atoi(argv[1]);
            int players = atoi(argv[2]);

            //range validation for amount of players and hand size per player
            if( players * hand > DECK_SIZE ) {
                puts("Error. Insuficient cards available to play for the amount");
                puts("of players or hand size specified. Only 52 card deck.");
                puts("Please try again\n");

            }
            //final validation made to check if any of the numbers are 0
            else if( players * hand < 1 ) {
                puts("Numbers must be above 0");
                puts("Please try again\n");
            }
        }
    }//end of input validation ================================================

    INPUT_HAND = atoi(argv[1]);
    INPUT_PLAYERS = atoi(argv[2]);

    int deck[SUIT_HIGH][RANK_HIGH];

    //Create the deck and display
    createDeck( deck );
    printDeck( deck );

    //Shuffle the deck and display
    shuffleDeck( deck );
    printDeck( deck );

    //Create hands for the players
    playHand( INPUT_PLAYERS, INPUT_HAND, deck );

    return 0;
}
