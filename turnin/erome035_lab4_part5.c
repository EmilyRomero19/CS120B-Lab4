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

enum SM1_STATES {START, INIT, POUND_UNLOCK, Y_UNLOCK, Y_RELEASE, LOCK} SM1_STATE;
void Tick_Door() {
	switch(SM1_STATE) {
		case START:
		SM1_STATE = INIT;
		break;
			
		case INIT:
		if ((PINA & 0x07) == 0x04) {
			SM1_STATE = POUND_UNLOCK;
		}
		else if ((PINA & 0x87) == 0x80) {
			SM1_STATE = Y_UNLOCK;
		}
		else {
			SM1_STATE = INIT;
		}
		break;
			
		case POUND_UNLOCK:
		if ((PINA & 0x07) == 0x04) {
                        SM1_STATE = POUND_UNLOCK;
                }
                else {
                        SM1_STATE = Y_UNLOCK;
                }
                break;
			
		case Y_UNLOCK:
		if (((PINA & 0x07) == 0x02) && ((PORTB & 0x01) == 0x01)) {	
			 SM1_STATE = LOCK;
		}
		else if ((PINA & 0x07) == 0x02) {
                      SM1_STATE = Y_RELEASE;
                }
	 	else if (PINA == 0x00) {
		      SM1_STATE = Y_UNLOCK;
		}
                else {
                      SM1_STATE = INIT;
                }
                break;
			
		case Y_RELEASE:
		if ((PINA & 0x07) == 0x02) {
                        SM1_STATE = Y_RELEASE;
                }
                else {
                        SM1_STATE = INIT;
                }
                break;
			
			
		case LOCK:
		if ((PINA & 0x87) == 0x80) {
                         SM1_STATE = LOCK;
                }
                else if((PINA & 0x07) == 0x02) {
                         SM1_STATE = LOCK;
                }
		else{
		 	SM1_STATE = INIT;
		}
               break;
	}
	
	switch(SM1_STATE) {
	case START:
	PORTB = 0x00;
	break;
			
	case INIT:
	break;
			
	case POUND_UNLOCK:
	break;
			
	case Y_UNLOCK:
	break;
			
	case Y_RELEASE:
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
