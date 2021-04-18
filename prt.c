enum SM1_STATES {SM1_SMStart, SM_Init, SM_UnlockHashtag, SM_UnlockY, SM_UnlockYRelease, SM_UnlockHashtagRelease} SM1_STATE;
void Tick_Lock() {
	
	unsigned char tmpA = PINA & 0x01;
	unsigned char tmpB = PINA & 0x02;
	unsigned char tmpC = PINA & 0x04;
	unsigned char tmpD = PINA & 0x80;
	switch(SM1_STATE) 
	{
		case SM1_SMStart:
			SM1_STATE = SM_Init;
			break;
		case SM_Init:
			if (tmpD) 
			{
				SM1_STATE = SM_Init;
			}
			else if (tmpC && !tmpB && !tmpA) 
			{
				SM1_STATE = SM_UnlockHashtag;
			}
			else 
			{
				SM1_STATE = SM_Init;
			}
			break;
		case SM_UnlockHashtag:
			if (tmpD)
			{
				SM1_STATE = SM_Init;
			}
			else 
			{
					if (!tmpC && tmpB && !tmpA)
					{
                                SM1_STATE = SM_UnlockY;
                        }
                        else 
			{
                                SM1_STATE = SM_Init;
                        }
                        break;
		case SM_UnlockHashtagRelease:
			if (tmpC)
			{
				SM1_STATE = SM_UnlockHashtagRelease;
			}
			else
			{
				SM1_STATE = SM_Init;
			}
			break;
		case SM_UnlockY:
			if (tmpD)
			{
				SM1_STATE = SM_Init;
			}
			else if (PINA == 0x00)
			{
				SM1_STATE = SM_UnlockY;
			}
			else
			{
				SM1_STATE = SM_UnlockYRelease;
			}
			break;
		case SM_UnlockYRelease:
			if (tmpB)
			{
				SM1_STATE = SM_UnlockYRelease;
			}
			else
			{
				SM1_STATE = SM_Init;
			}
			break;
			
	}
	switch(SM1_STATE) 
	{
		case SM1_SMStart:
			break;
		case SM_Init:
			PORTB = 0x00;
			break;
		case SM_UnlockHashtag:
			break;
		case SM_UnlockY:
			break;
		case SM_UnlockYRelease:
			PORTB = 0x01;
			break;
		case SM_UnlockHashtagRelease:
			PORTB = 0x01;
			break;
	}
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
    /* Insert your solution below */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    while (1) {
	Tick_Lock();
    }
    return 1;
}
