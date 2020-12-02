/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "timer.h"
#endif

unsigned char patternArray[2] = { 0x3C, 0x24 };
unsigned char rowArray[3] = { 0x02, 0x04, 0x08 };
unsigned char input;
unsigned char i;

enum CenterRect_States { CR_Init, CR_DisplayR2, CR_DisplayR3, CR_DisplayR4 } CR_currState;

void CenterRectDisplay() {
    switch (CR_currState) {
        case CR_Init:
            CR_currState = CR_DisplayR2;
            break;
        case CR_DisplayR2:
            CR_currState = CR_DisplayR3;
            break;
        case CR_DisplayR3:
            CR_currState = CR_DisplayR4;
            break;
        case CR_DisplayR4:
            CR_currState = CR_DisplayR2;
            break;
        default:
            break;
    }
    
    switch (CR_currState) {
        case CR_DisplayR2:
            PORTC = patternArray[0];
            PORTD = ~rowArray[0];
            break;
        case CR_DisplayR3:
            PORTC = patternArray[1];
            PORTD = ~rowArray[1];
            break;
        case CR_DisplayR4:
            PORTC = patternArray[0];
            PORTD = ~rowArray[2];
            break;
        default:
            break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    DDRD = 0xFF; PORTD = 0x00;

    TimerSet(1);
    CR_currState = CR_Init;
    TimerOn();
    /* Insert your solution below */
    while (1) {
        CenterRectDisplay();
        while(!TimerFlag);
        TimerFlag = 0;
    }
    return 1;
}
