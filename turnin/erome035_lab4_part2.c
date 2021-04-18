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

enum SM1_STATES { SM1_SMStart, SM1_INIT, SM1_ADD1, SM1_MINUS1, SM1_ADD, SM1_MINUS, SM1_RESET } SM1_STATE;
void Tick_LED() {
	switch(SM1_STATE){
			
	case SM1_SMStart:
	SM1_STATE = SM1_INIT;
	break;
	
	case SM1_INIT:
	if( (PINA & 0x01) == 0x01){
		SM1_STATE = SM1_ADD;
	}
	else if ((PINA & 0x02) == 0x02){
		SM1_STATE = SM1_MINUS;
	}
	else if ((PINA & 0x03) == 0x03){
		SM1_STATE = SM1_RESET;
	}
	break;
	
	case SM1_ADD1:
	if( (PINA & 0x01) == 0x01){
		SM1_STATE = SM1_ADD;
	}
	else{
		SM1_STATE = SM1_INIT;
	}
	break;	
			
	case SM1_ADD:
	SM1_STATE = SM1_ADD1;	
	break;	
	
	case SM1_MINUS1:
	if ((PINA & 0x02) == 0x02){
		SM1_STATE = SM1_MINUS;
	}
	else{
		SM1_STATE = SM1_INIT;
	}
	break;
		
	case SM1_MINUS:	
	SM1_STATE = SM1_MINUS;
	break;
	
	case SM1_RESET:
	if ((PINA & 0x03) == 0x03){
		SM1_STATE = SM1_RESET;
	}
	else{
		SM1_STATE = SM1_INIT;
	}
	break;		
			
	default:
	SM1_STATE = SM1_INIT;
	break;		
	
	}
	
	switch(SM1_STATE){
			
	case SM1_SMStart:
	PORTC = 0x07;
	break;
	
	case SM1_INIT:
	PORTC = 0x07;
	break;
			
	case SM1_ADD:
	break;
			
	case SM1_MINUS:	
	break;	
			
	case SM1_ADD1:
	if(PORTC < 0x09){
		
	PORTC = PORTC + 1;
	break;
	}
			
	case SM1_MINUS1:		
	if(PORTC > 0x00){
		
	PORTC = PORTC - 1;
	break;	
	}
	
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
	Tick_LED();
    }
    return 1;
}
