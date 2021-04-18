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

enum SM1_STATES { SM1_SMStart, SM_INIT1, SM1_INIT2, SM1_ADD1, SM1_MINUS1, SM1_ADD, SM1_MINUS, SM1_RESET } SM1_STATE;

void Tick_Reset() {	
	
	unsigned char ButtonAdd = PINA & 0x01; 
	unsigned char ButtonMinus = PINA & 0x02; 
	
	
	switch(SM1_STATE) {
		case SM1_SMStart:
		SM1_STATE = SM_INIT1;
		break;
			
		case SM_INIT1:
		SM1_STATE = SM1_INIT2;
		break;
			
		case SM1_INIT2:
		if (ButtonAdd && ButtonMinus) { // reset
               	 	SM1_STATE = SM1_RESET;
            	}
		else if (ButtonAdd && !ButtonMinus) { // go add
			SM1_STATE = SM1_ADD;
		}
		else if (!ButtonAdd && ButtonMinus){ // go subtract 
                	SM1_STATE = SM1_MINUS;
            	}
		else if (!ButtonAdd && !ButtonMinus){ // stay in same state
			SM1_STATE = SM1_INIT2; 
		}
		break;
			
			
		case SM1_RESET:
		if (ButtonAdd && ButtonMinus){ // repeat reset
			SM1_STATE = SM1_RESET;
		}
		else {
			SM1_STATE = SM1_INIT2; // go back to initial
		}
		break;
			
			
		case SM1_ADD1:
		if (ButtonAdd && !ButtonMinus) { 
                	SM1_STATE = SM1_ADD1;
            	}
            	else {
                	SM1_STATE = SM1_INIT2; // go back to initial
            	}
            	break;
			
		case SM1_ADD:
			SM1_STATE = SM1_ADD1;
		break;
		
			
		case SM1_MINUS1:
		if (!tempVal && !tempVal2) {
			SM1_STATE = SM1_MINUS1;
            	}
            	else {
                	SM1_STATE = SM1_INIT2;
            	}
            	break;
			
		case SM1_MINUS:
			SM1_STATE = SM1_MINUS;
		break;
			
		default:
			SM1_STATE = SM1_SMStart;
		break;
	}
	switch(SM1_STATE) {
			
	case SM1_SMStart:
	PORTC = 0x07;
	break;
			
	case SM_INIT1:
	PORTC = 0x07;
	break;
			
	case SM1_INIT2:
	break;
			
	case SM1_ADD1:
	break;
			
	case SM1_MINUS1:
	break;
			
	case SM1_ADD:
	if (PORTC < 0x09) {
                PORTC = PORTC + 1;
	}
        break;
			
	case SM1_MINUS:
	if (PORTC > 0x00){ 
                PORTC = PORTC - 1;
	}
        break;
			
	case SM1_RESET:
	PORTC = 0x00;
	break;
			
	default:
	PORTC = 0x07;
	break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */

	DDRA = 0x00; PORTA = 0xFF; //inputs
	DDRB = 0xFF; PORTB = 0x00; //outputs
	
    /* Insert your solution below */
    while (1) {
	Tick_Reset();
    }
    return 1;
}
