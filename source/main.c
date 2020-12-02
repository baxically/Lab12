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

unsigned char pattern;
unsigned char row;
unsigned char input;
enum Row_States { Row_Init, Row_Shift } Row_currState;

void RowShift() {
    switch (Row_currState) {
        case Row_Init:
            input = ~PINA;
            pattern = 0xFF;
            row = 0x01;
            Row_currState = Row_Shift;
            break;
        case Row_Shift:
            input = ~PINA;
            if (input == 0x02 && row < 0x10) {
                row <<= 1;
                Row_currState = Row_Shift;
            } else if (input == 0x01 && row > 0x01) {
                row >>= 1;
                Row_currState = Row_Shift;
            } else { Row_currState = Row_Shift; }
            break;
    }
    PORTC = pattern; PORTD = ~row;
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    DDRD = 0xFF; PORTD = 0x00;

    TimerSet(100);
    Row_currState = Row_Init;
    TimerOn();
    /* Insert your solution below */
    while (1) {
        RowShift();
        while(!TimerFlag);
        TimerFlag = 0;
    }
    return 1;
}
