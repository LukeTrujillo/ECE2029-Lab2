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
unsigned int led = 0x00;

// Main
void main()
{
    WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer. Always need to stop this!!

    initLeds();
    configureButtons();
    configDisplay();
    configKeypad();

    Graphics_clearDisplay(&g_sContext); // Clear the display

    // Write some text to the display
    Graphics_drawStringCentered(&g_sContext, "Welcome to", AUTO_STRING_LENGTH,
                                48, 25, TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext, "MSP430 HERO", AUTO_STRING_LENGTH,
                                48, 35, TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext, "Press * to start",
    AUTO_STRING_LENGTH,
                                48, 55, TRANSPARENT_TEXT);
    Graphics_flushBuffer(&g_sContext);

    _BIS_SR(GIE); // Global Interrupt enable

    TA2CTL = TASSEL_1 + MC_1 + ID_0;

    TA2CCR0 = 327;

    TA2CCTL0 = CCIE; // Enable interrupt for TA2CCR0

int loops = 0;
    while(loops < 30) {
        if(led == 0x0001) {
            BuzzerOn(13,1);
        } else {
            BuzzerOn(13,1);
        }
    }
    BuzzerOff();
}

// Example syntax for TimerA2 ISR
#pragma vector=TIMER2_A0_VECTOR
__interrupt void TIMER_A2_ISR(void)
{
    led ^= BIT0;
}

void configureButtons()
{
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

unsigned int readButtons()
{
    //buttons on P7.0(S1), P7.4 (S2), P2.4 (S3), P3.7 (S4)
    return ~(~(P7IN & (BIT0)) | ~(P3IN & (BIT6) >> 3) | ~(P2IN & (BIT2))
            | ~(P7IN & (BIT4)));
}
void configUserLED(char inbits)
{
    P1SEL &= ~(BIT0); //set select pin to 0, digital io on
    P4SEL &= ~(BIT7);
    P1DIR |= (BIT0); //set direction pin to 1, output
    P4DIR |= (BIT7);
    //turn target off, then set to inbitsTarget
    P1OUT = (P1OUT & ~(BIT0)) | (inbits & BIT0); //set p1.0 to inbitsBIT0
    P4OUT = (P4OUT & ~(BIT7)) | (inbits & BIT1); //set p4.7 to inbitsBIT1
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

    volatile unsigned int i, j;	// volatile to prevent removal in optimization
                                // by compiler. Functionally this is useless code

    for (j = 0; j < numLoops; j++)
    {
        i = 1000;					// SW Delay
        while (i > 0)				// could also have used while (i)
            i--;
    }
}
