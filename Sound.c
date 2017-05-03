// Sound.c
// Runs on any computer
// Sound assets based off the original Space Invaders 
// Import these constants into your SpaceInvaders.c for sounds!
// Jonathan Valvano
// November 17, 2014
#include <stdint.h>
#include "Sound.h"
#include "DAC.h"
#include "global_variables.h"
#include "Timer2.h"
#include "Timer1.h"
#include "struct_definition.h"


void Sound_Init(void){
// write this
};
void Song_Play(){
			Timer2_Init(FINT);	// Timer2 for guns_n_roses song			
}

void Sound_Play(uint8_t n){
	Timer2_Init(FINT/n);
	switch(sound_flag)
	{
		
		case DEAD0:		
			{
				Timer1_Init(&UserTask1A, end_song[eindex] );
				break;
			}
	  case SCREAM:  
		{
			
			Timer1_Init(&UserTask1A, scream[sindex] );
			break;
		}
		case BANANA: 
		{
			Timer1_Init(&UserTask1A, banana[bindex] );
			break;
		}
		case MENU:
		{
			Timer1_Init(&UserTask1A, menu[mindex] );
			break;
		}
		default: //case JUMP:
		{
			Timer1_Init(&UserTask1A, jump[jindex] );
			break;
		}
	}

}
