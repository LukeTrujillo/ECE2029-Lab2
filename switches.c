/*
 * switches.c
 *
 *  Created on: Jan 24, 2019
 *      Author: Luke Trujillo
 */
#include <msp430.h>

void switchConfig();
char switchIO();

/*int main() {
    switchConfig();

    char result = switchIO();

    return 0;
}*/
/*
 * P2.6-3 for digital IO
 * Disable pull resistors
 * Don't affect other pins
 */
void switchConfig() {
  P2SEL = P2SEL & ~(BIT6 | BIT5 | BIT4 | BIT3);  // 1000 0111 & P2SEL
  P2REN = P2SEL & ~(BIT6 | BIT5 | BIT4 | BIT3);  // 1000 0111 & P2DIR

  P2DIR = P2DIR & ~(BIT6 | BIT5 | BIT4 | BIT3);
  // 1000 0111 & P2DIR (sets 6 - 3 to 0 for input,
  // while not modifying the others)
}
char switchIO() {
  char inBits;
  inBits = inBits;

  inBits = inBits >> 3;
  inBits = inBits & (BIT3 | BIT2 | BIT1 | BIT0);

  if (inBits < 9) {
    inBits += 0x30;
  } else {
    inBits += (0x41 - 0xA);
  }

  return inBits;
}
