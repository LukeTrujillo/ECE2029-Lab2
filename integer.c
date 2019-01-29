#include "msp430.h"
#include <stdlib.h>
#define MAX_PTS 300 //constant defined for the number of inputs and outputs
#define M 8 //constant defined and used for performing operations
#define SHIFT 3 // // the amount to shift the numbers by
#define SPAN 2500 // this is the range of numbers to randomly generate
#define OFFSET 499 //this is how much to offset the generated numbers by
// IMPORTANT: Luke Trujillo Box #655
void main(void)
{ // Give total size (in bytes) of these variables as declared
    int in[MAX_PTS];  // declare an array of 300 integers for the input
    int out[MAX_PTS]; // similarly declare an array of 300 integers for the output
    volatile int i, a; // declare variables to use inside of the loop.
    long int sum; //keep a running vairable of the sum of the outpur
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

    for (i = 0; i < MAX_PTS; i++) // iterate through the loop 300 times (once for each index in in[] and out[])
    {
        in[i] = (rand() % SPAN) - OFFSET; //generate a random number between -499 and 2000 (inclusive), store it inside of the ith index of in
        if (i < M) // if i is less than 8
            out[i] = 0; //set the output to be 0
        else // if i is greater than 8
        {
            sum = 0; //reset the sum to be 0 for the new sum occurring
            for (a = 0; a < M; a++) // iterate 8 times
                sum += in[i - a]; // each time add one of the last 8 numbers to the sum
            out[i] = sum >> SHIFT; // //then right shift 3 times and store that inside of the out array
        }
    }
    return 0;
}
