#include "msp430.h"
#include <stdlib.h>
#define MAX_PTS 300 //symbolic constant defining MAX_PTS as 300
// IMPORTANT: Luke Trujillo Box #655
/*void main(void)
{ // Give total size (in bytes) of these variables as declared

    int in[MAX_PTS]; // declare an array of 300 integers for the input
    float out[MAX_PTS]; // similarly declare an array of 300 floats for the output
    volatile int i, a, SPAN = 2500, OFFSET = 499, M = 8; // declare variables to use inside of the loop.

    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    for (i = 0; i < MAX_PTS; i++) // iterate through the loop 300 times (once for each index in in[] and out[])
    {
        in[i] = (rand() % SPAN) - OFFSET; //generate a random number between -499 and 2000 (inclusive), store it inside of the ith index of in
        if (i < M) // if i is less than 8
            out[i] = 0.0; //set the output to be 0
        else // if i is greater than 8
        {
            out[i] = 0.0; // set the output to be 0
            for (a = 0; a < M; a++) // iterate 8 times
                out[i] += (float) in[i - a]; // add the last 8 numbers to out[i]
            out[i] = out[i] / M; // then divide that number by 8 for good measure
        }
    }
    return 0;
}*/
