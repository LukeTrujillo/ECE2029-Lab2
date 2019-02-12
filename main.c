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

void showLED(unsigned int);

void configUserLED();
void writeLED(unsigned int);
void buzz(unsigned int);

void makeSong();

// Declare globals here
unsigned int led = 0x00;

struct Note
{
    int frequency, duration;
};
void playNote(struct Note not);

struct Note song[10];

volatile int nextBeat = 0;

// Main
void main()
{
   WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer. Always need to stop this!!
   _BIS_SR(GIE);

    configUserLED();
    configureButtons();
    makeSong();

    //setup the timer here

    int index = 0;

    TA2CTL = TASSEL_1 | MC_1 | ID_0;
    TA2CCR0 = 327;

    TA2CCTL0 = CCIE;

    while (index < 10)
    {
        if (nextBeat)
        {
            nextBeat = 0;

            if (song[index].duration > 0)
            {
                song[index].duration--;
            }
            else
            {
                index++;
            }

        }
        playNote(song[index]);
    }
}
void playNote(struct Note note)
{
    BuzzerOn(note.frequency, 100);

    if (note.frequency <= 494)
    {
        writeLED(1);
    }
    else if (note.frequency <= 587)
    {
        writeLED(2);
    }
    else if (note.frequency <= 698)
    {
        writeLED(4);
    }
    else
    {
        writeLED(8);
    }
}

void makeSong()
{

    song[0].duration = 500;
    song[0].frequency = 440;

    song[1].duration = 500;
    song[1].frequency = 1000;

    song[3].duration = 500;
    song[3].frequency = 440;

    song[4].duration = 500;
    song[4].frequency = 1000;

    song[5].duration = 500;
       song[5].frequency = 440;

       song[6].duration = 500;
       song[6].frequency = 1000;
       song[7].duration = 500;
          song[7].frequency = 440;

      song[8].duration = 500;
      song[8].frequency = 1000;

     song[9].duration = 500;
     song[9].frequency = 440;

}

// Example syntax for TimerA2 ISR
#pragma vector=TIMER2_A0_VECTOR
__interrupt void TIMERA2_ISR(void)
{
    nextBeat = 1;
}

void showLEDs(unsigned int val)
{

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
    P7OUT |= (BIT0 | BIT4);
    P2OUT |= (BIT2);
    P3OUT |= (BIT6);
}

unsigned int readButtons()
{
//buttons on P7.0(S1), P7.4 (S2), P2.4 (S3), P3.7 (S4)
    return (~P7IN & (BIT0)) | ((~P3IN & (BIT6)) >> 5) | (~P2IN & (BIT2))
            | ((~P7IN & (BIT4)) >> 1);
}
void configUserLED()
{
    P6SEL &= ~(BIT2 | BIT1 | BIT3 | BIT4);
    P6DIR |= (BIT2 | BIT1 | BIT3 | BIT4);
}
void writeLED(unsigned int val)
{
    P6OUT &= ~(BIT2 | BIT1 | BIT3 | BIT4);

    if ((val & BIT0) != 0)
    {
        P6OUT |= BIT2;
    }
    if ((val & BIT1) != 0)
    {
        P6OUT |= BIT1;
    }
    if ((val & BIT2) != 0)
    {
        P6OUT |= BIT3;
    }
    if ((val & BIT3) != 0)
    {
        P6OUT |= BIT4;
    }
}
