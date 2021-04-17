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

enum SM1_STATES { SM1_SMStart, SM1_LED1, SM1_LED2, SM1_RELEASED2 } SM1_STATE;
void Tick_LED() {
	switch(SM1_STATE){

	case SM1_SMStart:
	SM1_STATE = SM1_LED1;
	break;

	case SM1_LED1:
	if( (PINA & 0x01) == 0x01){ //if button is pressed, turn on LED2
	SM1_STATE = SM1_LED2;
	}
	else{
	SM1_STATE = SM1_LED1;
	}
	break;
					
	case SM1_LED2:
	if( (PINA & 0x01) == 0x01){ // if the buttons is being pressed stay here 
	SM1_STATE = SM1_LED2;
	}
	else{
	SM1_STATE = SM1_RELEASED2; // the button is released
	}
	break;
			
	case SM1_RELEASED2:
	if( (PINA & 0x01) == 0x01){ // the button is pressed
	SM1_STATE = SM1_LED1;
	}
	else{
	SM1_STATE = SM1_RELEASED2; 
	}
	break;		
	
	default:
	SM1_STATE = SM1_SMStart;
	break;
}
	
	switch(SM1_STATE){
	case SM1_SMStart:
	break;

	case SM1_LED1:
	PORTB = 0x01;
	break;
			
	case SM1_LED2:
	PORTB = 0x02;
	break;
			
	case SM1_RELEASED2:
	break;
	
	default:
	PORTB = 0x01;
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
