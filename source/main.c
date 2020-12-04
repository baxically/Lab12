/*	Author: Ally Thach, athac007
 *  Partner(s) Name: 
 *	Lab Section: 24
 *	Assignment: Lab 12  Exercise 4
 *	Exercise Description: Expand upon exercise 3 of the lab by introducing four buttons that control the position of the hollow rectangle.
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

unsigned char patternArray[3] = { 0x3C, 0x24, 0x3C };
unsigned char rowArray[3] = { 0x02, 0x04, 0x08 };
unsigned char tmpA;
unsigned char i;

enum Demo_tates {init, displayR2, displayR3, displayR4 } currState;

void Demo_Tick()
{
    switch (currState)
    {
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
            PORTC = patternArray[2];
            PORTD = ~rowArray[2];
            break;
        default:
            break;
    }
}

enum Button_States {button_init, button_press } button_currState;

void Button_Tick()
{
    switch (button_currState)
    {
        case button_init:
            button_currState = button_press;
            break;
        case button_press:
            if (tmpA == 0x04 && patternArray[0] < 0x80)
            {
                for (i = 0; i < 3; i++)
                {
                    patternArray[i] <<= 1;
                    
                }
                button_currState = button_press;
            }
            else if (tmpA == 0x08 && patternArray[2] > 0x0F)
            {
                for (i = 0; i < 3; i++)
                {
                    patternArray[i] >>= 1;
                    
                }
                button_currState = button_press;
            }
            else if (tmpA == 0x01 && rowArray[2] > 0x01)
            {
                for (i = 0; i < 3; i++)
                {
                    rowArray[i] >>= 1;
                    
                }
                button_currState = button_press;
            }
            else if (input == 0x02 && rowArray[0] < 0x10)
            {
                for (i = 0; i < 3; i++)
                {
                    rowArray[i] <<= 1;
                }
                button_currState = button_press;
            }
            else
            {
                button_currState = button_press;
                
            }
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

    unsigned char time = 0;
    TimerSet(1);
    currState = init;
    button_currState = button_init;
    TimerOn();
    /* Insert your solution below */
    while (1) {
        tmpA = ~PINA;
        
        if (time < 100)
        {
            time++;
        }
        else
        {
            time = 0;
            Button_Tick();
        }

        Demo_Tick();
        while(!TimerFlag)
        {
            
        }
        TimerFlag = 0;
    }
    return 1;
}
