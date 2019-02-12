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

struct Note {
  int frequency, duration;
};

void makeNote(int position, int freq, int dur);
void playNote(struct Note not);

struct Note song[10];

volatile int nextBeat = 0;

// Main
void main() {
  WDTCTL = WDTPW | WDTHOLD;  // Stop watchdog timer. Always need to stop this!!
  _BIS_SR(GIE);

  configUserLED();
  configureButtons();
  makeSong();

  //---------------TIMER SETUP----------------------
  TA2CTL = TASSEL_1 | MC_1 | ID_0;  // clock: ACLK:32768 Hz, upmode, divider=1
  TA2CCR0 = 327;  // interrupt every 327 clicks (~0.01 seconds)

  TA2CCTL0 = CCIE;  // enable interrupt
  //-----------------------------------------------

  int index = 0;        // current note
  int songLength = 10;  // total note length in song
  while (index < songLength) {
    if (nextBeat) {  // this should run about once every 0.01 seconds
      nextBeat = 0;  // reset timer flag

      if (song[index].duration >
          0) {  // if this note still has playing time left
        song[index]
            .duration--;  // decrease the amount of time left in this note
      } else {
        index++;  // next note
      }
    }
    playNote(song[index]);  // actually play the needed sound
  }
  BuzzerOff();
}
void playNote(struct Note note) {
  BuzzerOn(note.frequency, 100);

  if (note.frequency <= 495) {
    writeLED(1);
  } else if (note.frequency <= 587) {
    writeLED(2);
  } else if (note.frequency <= 698) {
    writeLED(4);
  } else {
    writeLED(8);
  }
}

void makeSong() {
  makeNote(0, 440, 100);  // A
  makeNote(1, 494, 100);  // B
  makeNote(2, 523, 100);  // C
  makeNote(3, 440, 100);  // A
  makeNote(4, 523, 100);  // C
  makeNote(5, 440, 100);  // A
  makeNote(6, 523, 100);  // C
  makeNote(7, 440, 100);  // A
  makeNote(8, 523, 100);  // C
  makeNote(9, 300, 100);  // END
}

void makeNote(int position, int freq, int dur) {  // shorthand for note creation
  song[position].duration = dur;
  song[position].frequency = freq;
};

// Example syntax for TimerA2 ISR
#pragma vector = TIMER2_A0_VECTOR
__interrupt void TIMERA2_ISR(void) { nextBeat = 1; }

void showLEDs(unsigned int val) {}
void configureButtons() {
  // buttons on P7.0, P7.4, P2.4, P3.6

  // configure switches for IO
  P7SEL &= ~(BIT0 | BIT4);
  P2SEL &= ~(BIT2);
  P3SEL &= ~(BIT6);

  // set them up for input
  P7DIR &= ~(BIT0 | BIT4);
  P2DIR &= ~(BIT2);
  P3DIR &= ~(BIT6);

  // enable the pull resistors
  P7REN |= (BIT0 | BIT4);
  P2REN |= (BIT2);
  P3REN |= (BIT6);

  // specify that they should be pull resistors
  P7OUT |= (BIT0 | BIT4);
  P2OUT |= (BIT2);
  P3OUT |= (BIT6);
}

unsigned int readButtons() {
  // buttons on P7.0(S1), P7.4 (S2), P2.4 (S3), P3.7 (S4)
  return (~P7IN & (BIT0)) | ((~P3IN & (BIT6)) >> 5) | (~P2IN & (BIT2)) |
         ((~P7IN & (BIT4)) >> 1);
}
void configUserLED() {
  P6SEL &= ~(BIT2 | BIT1 | BIT3 | BIT4);
  P6DIR |= (BIT2 | BIT1 | BIT3 | BIT4);
}
void writeLED(unsigned int val) {
  P6OUT &= ~(BIT2 | BIT1 | BIT3 | BIT4);

  if ((val & BIT0) != 0) {
    P6OUT |= BIT2;
  }
  if ((val & BIT1) != 0) {
    P6OUT |= BIT1;
  }
  if ((val & BIT2) != 0) {
    P6OUT |= BIT3;
  }
  if ((val & BIT3) != 0) {
    P6OUT |= BIT4;
  }
}
