/*	Author: Ally Thach, athac007
 *  Partner(s) Name: 
 *	Lab Section: 24
 *	Assignment: Lab 12  Exercise 2
 *	Exercise Description: Design a system where an illuminated column of the LED matrix can be shifted left or right based on a button press.
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *  DEMO LINK:
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "timer.h"
#endif

unsigned char pattern;
unsigned char row;
unsigned char tmpA;

enum Demo_States {init, shift } currState;

void Demo_Tick() {
    switch (currState) {
        case init:
            tmpA = ~PINA;
            pattern = 0xFF;
            row = 0x01;
            currState = shift;
            break;
        case shift:
            tmpA = ~PINA;
            if(tmpA == 0x01 && pattern < 0x10)
            {
                pattern <<= 1;
                currState = shift;
            }
            else if(tmpA == 0x02 && pattern > 0x01)
            {
                pattern >>= 1;
                currState = shift;
            }
            else
            {
                currState = shift;
                
            }
            break;
    }
    PORTC = pattern;
    PORTD = ~row;
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00;
    PORTA = 0xFF;
    DDRC = 0xFF;
    PORTC = 0x00;
    DDRD = 0xFF;
    PORTD = 0x00;

    TimerSet(100);
    currState = init;
    TimerOn();
    /* Insert your solution below */
    while (1)
    {
        Demo_Tick();
        while(!TimerFlag)
        {
            
        }
        TimerFlag = 0;
    }
    return 1;
}
