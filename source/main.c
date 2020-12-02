/*	Author: Ally Thach, athac007
 *  Partner(s) Name: 
 *	Lab Section: 24
 *	Assignment: Lab 12  Exercise 3
 *	Exercise Description: Design a system where a 3x4 hollow rectangle is displayed in the center of the LED matrix like the photo below: Note: The varying brightness of the LEDs is only present in the photo. The completed exercise will not have varying brightness.
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

unsigned char patternArray[2] = {0x3C, 0x24};
unsigned char rowArray[3] = {0x02, 0x04, 0x08};
unsigned char tmpA;
unsigned char i;

enum Demo_States {init, displayR2, displayR3, displayR4 } currState;

void Demo_Tick()
{
    switch (currState) {
        case init:
            currState = displayR2;
            break;
        case displayR2:
            currState = displayR3;
            break;
        case displayR3:
            currState = displayR4;
            break;
        case displayR4:
            currState = displayR2;
            break;
        default:
            break;
    }
    
    switch (currState)
    {
        case displayR2:
            PORTC = patternArray[0];
            PORTD = ~rowArray[0];
            break;
        case displayR3:
            PORTC = patternArray[1];
            PORTD = ~rowArray[1];
            break;
        case displayR4:
            PORTC = patternArray[0];
            PORTD = ~rowArray[2];
            break;
        default:
            break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00;
    PORTA = 0xFF;
    DDRC = 0xFF;
    PORTC = 0x00;
    DDRD = 0xFF;
    PORTD = 0x00;

    TimerSet(1);
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
