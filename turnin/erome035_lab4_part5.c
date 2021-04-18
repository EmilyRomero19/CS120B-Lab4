/*	Author: erome035
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
#endif

enum SM1_STATES { START, INIT, VALID, INVALID, UNLOCK , LOCK } SM1_STATE;
unsigned char index = 0x00;
unsigned char array[4] = {0x04, 0x01, 0x02, 0x01};

void Tick_Door() {
	switch(SM1_STATE) {
		case START:
		SM1_STATE = INIT;
		break;
			
		case INIT:
		if ((PINA & 0x87) == array[index]) {
			SM1_STATE = VALID;
		}
		else if ((PINA & 0x87) == 0x80) {
			SM1_STATE = LOCK;
		}
		else if (PINA == 0x00) {
			SM1_STATE = INIT;
		}
		else{
			SM1_STATE = INVALID;
		}
		break; 
			
		
		case VALID:
		if ((index == 0x03) && ((PORTB & 0x01) == 0x01)) {
			SM1_STATE = LOCK;
		}
		else if (index == 0x03) {
			SM1_STATE = UNLOCK;
		}
		else if ((PINA & 0x07) == 0x00) {
                         ++index;
			SM1_STATE = INIT;
                }
		else {
			SM1_STATE = VALID;
		}
                break;	
			
		
		case INVALID:
		if ((PINA & 0x07) == 0x00) {
			index = 0x00;
			SM1_STATE = INIT;
		}
		break;
			
			
			
		case UNLOCK:
                if ((PINA & 0x07) == 0x00) {
			SM1_STATE = INIT;
			index = 0x00;
		}
		else {
			SM1_STATE = UNLOCK;
		}
		break;	
			
		
		case Locked:
		if ((PINA & 0x87) == 0x80) {
                        SM1_STATE = LOCK;
                }
                else {
                          SM1_STATE = INIT;
			  index = 0x00;
                }
                break;		
			
	}
	
	switch(SM1_STATE) {
	case START:
	PORTB = 0x00;
	break;
			
	case INIT:
	break;
			
	case VALID:
	break;
			
	case INVALID:
	break;
			
	case UNLOCK:
	PORTB = 0x01;
	break;
			
	case LOCK:
	PORTB = 0x00;
	break;

	}
}

int main(void) {
    /* Insert DDR and PORT initializations */

	DDRA = 0x00; PORTA = 0xFF; //inputs
	DDRB = 0xFF; PORTB = 0x00; //outputs
	
    /* Insert your solution below */
    while (1) {
	Tick_Door();
    }
    return 1;
}
