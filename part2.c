#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum SM1_STATES {SM1_SMStart, SM_Begin, SM_Init, SM_Reset, SM_Add, SM_Subtract, SM_AddOn, SM_SubtractOn} SM1_STATE;
void Tick_AddSubtract() {
	unsigned char tmpA = PINA & 0x01;
	unsigned char tmpB = PINA & 0x02; 
	switch(SM1_STATE) {
		case SM1_SMStart:
			SM1_STATE = SM_Begin;
			break;
		case SM_Begin:
			SM1_STATE = SM_Init;
			break;
		case SM_Init:
			
			if (tmpA && tmpB) 
			{
               	 		SM1_STATE = SM_Reset;
            		}
			else if (tmpA && !tmpB) 
			{
				SM1_STATE = SM_AddOn;
			}
			else if (!tmpA && tmpB) 
			{
                		SM1_STATE = SM_SubtractOn;
            		}
			else if (!tmpA && !tmpB)
			{
				SM1_STATE = SM_Init;
			}
			
			break;
		case SM_Reset:
			if (tmpA && tmpB) 
			{
				SM1_STATE = SM_Reset;
			}
			else 
			{
				SM1_STATE = SM_Init;
			}
			break;
		case SM_Add:
			if (tmpA && !tmpB) 
			{
                		SM1_STATE = SM_Add;
            		}
            		else 
			{
                		SM1_STATE = SM_Init;
            		}
            		break;
		case SM_AddOn:
			SM1_STATE = SM_Add;
			break;
			
		case SM_Subtract:
			if (!tmpA && tmpB) 
			{
				SM1_STATE = SM_Subtract;
            		}
            		else 
			{
                		SM1_STATE = SM_Init;
            		}
            		break;
		case SM_SubtractOn:
			SM1_STATE = SM_SubtractOn;
			break;
			
		default:
			SM1_STATE = SM1_SMStart;
			break;
	}
	switch(SM1_STATE) {
		case SM1_SMStart:
			PORTC = 0x07;
			break;
		case SM_Begin:
			PORTC = 0x07;
			break;
		case SM_Init:
			break;
		case SM_Add:
			break;
		case SM_Subtract:
			break;
		case SM_AddOn:
			if (PORTC < 0x09) 
			{
                		PORTC = PORTC + 1;
			}
            		break;
		case SM_SubtractOn:
			if (PORTC > 0x00) 
			{ 
                		PORTC = PORTC - 1;
			}
            		break;
		case SM_Reset:
			PORTC = 0x00;
			break;
		default:
			PORTC = 0x07;
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
    /* Insert your solution below */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    while (1) 
	{
		Tick_AddSubtract();
    }
    return 1;
}
