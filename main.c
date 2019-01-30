/************** ECE2049 DEMO CODE ******************/
/**************  9 January 2019   ******************/
/***************************************************/

#include <msp430.h>

/* Peripherals.c and .h are where the functions that implement
 * the LEDs and keypad, etc are. It is often useful to organize
 * your code by putting like functions together in files.
 * You include the header associated with that file(s)
 * into the main file of your project. */
#include "peripherals.h"

// Function Prototypes
void swDelay(char numLoops);
void configureButtons();
unsigned int readButtons();

void configUserLED(char inBits);

// Declare globals here

// Main
void main() {
    WDTCTL = WDTPW | WDTHOLD;    // Stop watchdog timer. Always need to stop this!!

    configureButtons();
    unsigned int x = 0;
    while(1) {
        x = readButtons();

       continue;
    }
}

void configureButtons() {
    //buttons on P7.0, P7.4, P2.4, P3.6

    //configure switches for IO
    P7SEL &= ~(BIT0 | BIT4);
    P2SEL &= ~(BIT2);
    P3SEL &= ~(BIT6);

    //set them up for input
    P7DIR &= ~(BIT0 | BIT4);
    P2DIR &= ~(BIT2);
    P3DIR &= ~(BIT6);

    //enable the pull resistors
    P7REN |= (BIT0 | BIT4);
    P2REN |= (BIT2);
    P3REN |= (BIT6);

    //specify that they should be pull resistors
    P7OUT &= ~(BIT0 | BIT4);
    P2OUT &= ~(BIT2);
    P3OUT &= ~(BIT6);
}

unsigned int readButtons() {
    //buttons on P7.0(S1), P7.4 (S2), P2.4 (S3), P3.7 (S4)
    return ~(~(P7IN & (BIT0)) | ~(P3IN & (BIT6) >> 3) | ~(P2IN & (BIT2)) | ~(P7IN & (BIT4)));
}
void configUserLED(char inBits) {
    P6SEL &= ~(BIT4 | BIT2 | BIT1 | BIT3);
    P6DIR |= (BIT4 | BIT2 | BIT1 | BIT3);
    P6OUT |= ((inBits << 3) & BIT4) | ((inBits << 1) & BIT2) | ((inBits >> 2) & BIT1) | ((inBits & BITS3));
}


void swDelay(char numLoops)
{
	// This function is a software delay. It performs
	// useless loops to waste a bit of time
	//
	// Input: numLoops = number of delay loops to execute
	// Output: none
	//
	// smj, ECE2049, 25 Aug 2013

	volatile unsigned int i,j;	// volatile to prevent removal in optimization
			                    // by compiler. Functionally this is useless code

	for (j=0; j<numLoops; j++)
    {
    	i = 50000 ;					// SW Delay
   	    while (i > 0)				// could also have used while (i)
	       i--;
    }
}
