/*
File Name:            temperatureChart.c
Author:               Joshua Suarez
Panther ID:           6041323
Assignment:           Assignment 1

Course Name/Number:   Programming III - COP-4338
Instructor:           William Feilds Jr.
Due Date:             January 29th 2019

    I hereby certify that this collective work is my own and
    none of it is the work of any other person or entity.

    ______________________________________ [Signature]

=============================================================================

Description:          This program will produce a table conversion chart
                      containing the conversion of temperatures from
                      Farenheit to Celcius and from Celius to Farenheit
                      with temperature values ranging from -80.0 to 320.0

              Input - The user is required to enter an integer
                      to indicate the step of each record. The STEP
                      refers to the number by which the temperature
                      will increase for each conversion. E.g The user
                      enters step '5', the output will be

             Output - The program will display a list of records
                      (lines) of which each record will contain the
                      conversion of temperature from Farenheit to Celcius
                      and from Celcius to Farenheit producing a complete
                      table. Each line will start with the initial Farenheit
                      and will increment according to the STEP number
                      provided as input by the user. The table will calculate
                      temperatures starting at -80.0 and continue to
                      increment until 320.0 degrees (inclusive).
                      Example output when step is '5':

                      Farenheit   Celcius   Farenheit   Celcius
                      =========   =======   =========   =======
                          -80.0     -62.0       -80.0    -112.0
                          -75.0     -59.4       -80.0    -103.0
                              .         .           .         .
                              .         .           .         .
            Process - 1. Program prompts user to enter value from 1 - 9
                            -If value provided is below 1 or above 9, the
                            program will continue to prompt until correct
                            value is provided.

                      2. Program will display temperature conversion
                      chart starting with Farenheit temperature -80.0
                      and display conversion of Farenheit to Celcius
                      and Celius to Farenheit until temperature reaches
                      320.0 F.


Known Bugs:           Program expects an integer from the range of 1
                      through 9 to be inserted as input from user.
                      Range is validated, however no validation is
                      provided to check if an ASCII character was
                      inserted instead of an integer.

=============================================================================
*/

#include <stdio.h>

#define STEP_MIN 1      /* Step minimum boundary */
#define STEP_MAX 10     /* Step maximum boundary */
#define FALSE 0         /* FALSE set to 0 to indicate false value */
#define TRUE 1          /* TRUE set to 1 to indicate true value */
#define MIN_TEMP -80    /* Temperature minimum value set -80.0 degrees */
#define MAX_TEMP 320    /* Temperature maximum value set 320.0 degrees */
#define MAX_LINES 10    /* Maximum number of records printed before*/
                        /* inserting new line  */

double farToCel (double far);
double celToFar (double cel);


int main() {
    double fahr, celsius;
    int lines = 0;
    int STEP;

    //user input
    printf("%s", "Please enter the step number between [1-9]");
    printf("%s", "and press [ENTER]: ");
    int isNumber = scanf("%d", &STEP);

    while (STEP < STEP_MIN || STEP > STEP_MAX || isNumber == FALSE){
        printf("%s", "\nPlease try again. Number must be ");
        printf("%s", "within range [1-9]: ");
        scanf("%d", &STEP);
    }//end while loop===============================================


    //Print table header
    printf("\n%10s%10s%10s%12s\n", "Farenheit", "Celcius", "Celcius",
    "Farenheit");
    printf("%10s%10s%10s%12s\n", "=========", "=======", "=======",
    "=========");

    //Print table info
    for (fahr = MIN_TEMP; fahr <= MAX_TEMP; fahr += STEP) {

        //must print groups of 10 records separated by blank lines
        if (lines != MAX_LINES) {

            celsius = farToCel(fahr);
            printf("%10.1f%10.1f", fahr, celsius);

            celsius = fahr;
            double tempFahr = MIN_TEMP;

            tempFahr = celToFar(celsius);
            printf("%10.1f%12.1f\n", celsius, tempFahr);

            lines++; //increment number of lines printed by 1
        }
        else {
            printf("\n"); //print blank line after 10 records
            lines = 0;
        }
    }//end for loop ==========================================

    return 0;
}

/*
    Function: double farToCel()

    Purpose:  farToCel stands for Farenheit to Celius. This Function
              accepts a floating point value as a parameter which is
              the temperature in farenheit. The farenheit temperature
              is converted to Celcius using the following formula:

              Celcius = (Farenheit - 32) / (9/5)

              ~Citation:
              -The C Programming Language - Author: [Kernigham/Richie]

    @param far Temperature in Farenheit

    @return Temperature in Celius
*/
double farToCel (double far) {

    double celsius = 5.0 * (far - 32) / 9.0;

    return celsius;
}


/*
    Function: double celToFar()

    Purpose:  celToFar stands for Celius to Farenheit. This Function
              accepts a floating point value as a parameter which is
              the temperature in Celcius. The Celcius temperature
              is converted to Farenheit using the following formula:

              Farenheit = ( 9/5 ) * Celcius + 32

              ~Citation:
              -The C Programming Language - Author: [Kernigham/Richie]

    @param far Temperature in Farenheit

    @return Temperature in Celius
*/
double celToFar(double cel) {

    double farenheit = ( 9.0 / 5.0 ) * cel + 32;

    return farenheit;
}
