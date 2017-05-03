// Timer1.c
// Runs on LM4F120/TM4C123
// Use TIMER1 in 32-bit periodic mode to request interrupts at a periodic rate
// Daniel Valvano
// Last Modified: 3/6/2015 
// You can use this timer only if you learn how it works

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2013
  Program 7.5, example 7.6

 Copyright 2013 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */
#include <stdint.h>

#include "tm4c123gh6pm.h"
#include "DAC.h"
#include "global_variables.h"
#include "struct_definition.h"
#include "Sound.h"
#include "Timer1.h"

unsigned long TimerCount;
void Timer2_Init(unsigned long period){
  unsigned long volatile delay;
  SYSCTL_RCGCTIMER_R |= 0x04;   // 0) activate timer2
  delay = SYSCTL_RCGCTIMER_R;
  TimerCount = 0;
  TIMER2_CTL_R = 0x00000000;   // 1) disable timer2A
  TIMER2_CFG_R = 0x00000000;   // 2) 32-bit mode
  TIMER2_TAMR_R = 0x00000002;  // 3) periodic mode
  TIMER2_TAILR_R = period-1;   // 4) reload value
  TIMER2_TAPR_R = 0;           // 5) clock resolution
  TIMER2_ICR_R = 0x00000001;   // 6) clear timeout flag
  TIMER2_IMR_R = 0x00000001;   // 7) arm timeout
  NVIC_PRI5_R = (NVIC_PRI5_R&0x00FFFFFF)|0x80000000;
// 8) priority 4
  NVIC_EN0_R = 1<<23;          // 9) enable IRQ 23 in
  TIMER2_CTL_R = 0x00000001;   // 10) enable timer2A
}
// trigger is Timer2A Time-Out Interrupt
// set periodically TATORIS set on rollover
void Timer2A_Handler(void){
  TIMER2_ICR_R = 0x00000001;  // acknowledge
  TimerCount++;
	
	if(sound_flag==ALIVE0)
	{
		//Sound_Play(1);
		if(cnt==48)
		{cnt=0;}
	
		Timer1_Init(&UserTask1A, guns_n_roses[cnt] );		//for next note
		
		cnt++;
	}
	if(sound_flag==SCREAM)	
	{Sound_Play(1);
		sindex++;
	if(sindex==3)
	sindex=0;
	}
	if(sound_flag==BANANA)
	{
	Sound_Play(2);
		bindex++;		
	if(bindex==4)
	{bindex=0;
		sound_flag=ALIVE0;}
	}
	if(sound_flag==DEAD0)
	{	
			Sound_Play(1);
			eindex++;
		if(eindex==22)
			eindex=0;
	}	
	if(sound_flag==JUMP)
	{
		Sound_Play(2);
			jindex++;
		if(jindex==2)
		{jindex=0;sound_flag=ALIVE0;}
	}
	if(sound_flag==MENU)
	{
		Sound_Play(2);
			mindex++;
		if(mindex==2)
		{mindex=0;}	
	}
		
// run some background stuff here
}
