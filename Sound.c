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
			Timer2_Init(FINT);	// Timer2 for song
			//Timer1_Init(&UserTask1A, guns_n_roses[cnt] ); 	// Timer1 for sound(for each note) 
			
}


void Sound_Play(uint32_t period){
   Timer1_Init(&UserTask1A, guns_n_roses[cnt] );
	//flag=0;
}

void Sound_Shoot(void){
// write this
};
void Sound_Killed(void){
// write this
};
void Sound_Explosion(void){
// write this
};

void Sound_Fastinvader1(void){
// write this
};
void Sound_Fastinvader2(void){
// write this
};
void Sound_Fastinvader3(void){
// write this
};
void Sound_Fastinvader4(void){
// write this
};
void Sound_Highpitch(void){
// write this
};
