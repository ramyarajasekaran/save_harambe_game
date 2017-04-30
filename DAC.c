// dac.c
// This software configures DAC output
// Runs on LM4F120 or TM4C123
// Program written by: put your names here
// Date Created: 3/6/17 
// Last Modified: 3/6/17 
// Lab number: 6
// Hardware connections
// DAC INPUTS: PB 5-0
// PIANO KEYS: PE 2-0

#include <stdint.h>
#include "tm4c123gh6pm.h"
// Code files contain the actual implemenation for public functions
// this file also contains an private functions and private data

// **************DAC_Init*********************
// Initialize 4-bit DAC, called once 
// Input: none
// Output: none
void DAC_Init(void){
	int volatile delay;
	SYSCTL_RCGCGPIO_R |= 0x02; // enabling clock for Port B
	while((SYSCTL_RCGCGPIO_R&0x02)!=0x02){}
	delay=100;
	delay=100;		
	delay= 100; // giving clock time to stabilize
	GPIO_PORTB_AMSEL_R &= ~0x3F;      // no analog
  GPIO_PORTB_PCTL_R &= ~0x00000FFF; // regular GPIO function
  GPIO_PORTB_DIR_R |= 0x03F;      // make PB5-0 out
  GPIO_PORTB_AFSEL_R &= ~0x3F;   // disable alt funct on PB5-0
  GPIO_PORTB_DEN_R |= 0x03F;      // enable digital I/O on PB5-0
}

// **************DAC_Out*********************
// output to DAC
// Input: 6-bit data, 0 to 63
// Output: none
void DAC_Out(uint32_t data){
	GPIO_PORTB_DATA_R= data;
}
