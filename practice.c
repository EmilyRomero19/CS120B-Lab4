#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum SM1_STATES {SM1_SMStart, SM1_SMOn, SM1_SMOnRelease, SM1_SMOff, SM1_SMOffRelease} SM1_STATE;
void Tick_OnOff() {
	switch(SM1_STATE) {
		case SM1_SMStart:
			SM1_STATE = SM1_SMOn;
			break;
		case SM1_SMOn:
			if ((PINA & 0x01) == 0x01) {
				SM1_STATE = SM1_SMOn;
			}
			else {
				SM1_STATE = SM1_SMOnRelease;
			}
			break;
		case SM1_SMOnRelease:
			if ((PINA & 0x01) == 0x01) {
                                SM1_STATE = SM1_SMOff;
                        }
                        else {
                                SM1_STATE = SM1_SMOnRelease;
                        }
                        break;
		case SM1_SMOff:
			if ((PINA & 0x01) == 0x01) {
				SM1_STATE = SM1_SMOff;
			}
			else {
				SM1_STATE = SM1_SMOffRelease;
			}
			break;
		case SM1_SMOffRelease:
			if ((PINA & 0x01) == 0x01) {
				SM1_STATE = SM1_SMOn;
			}
			else {
				SM1_STATE = SM1_SMOffRelease;
			}
			break;
		default:
			SM1_STATE = SM1_SMStart;
			break;
	}
	switch(SM1_STATE) {
		case SM1_SMStart:
			PORTB = 0x01;
			break;
		case SM1_SMOn:
                        PORTB = 0x01;
                        break;
		case SM1_SMOnRelease:
			break;
		case SM1_SMOff:
                        PORTB = 0x02;
                        break;
		case SM1_SMOffRelease:
			break;
		default:
			PORTB = 0x01;
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
    /* Insert your solution below */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    while (1) {
	Tick_OnOff();
    }
    return 1;
}
