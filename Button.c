//create Button.h for header file
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "ST7735.h"
#include "Random.h"
#include "TExaS.h"
#include "ADC.h"
#include "Button.h"
#include "struct_definition.h"
#include "global_variables.h"

void EnableInterrupts(void);
void DisableInterrupts(void);


//initializes PB0 to be edge triggered interupt button
void Button_Init(void){       
  SYSCTL_RCGC2_R |= 0x00000008; // (a) activate clock for port D
  GPIO_PORTD_DIR_R &= ~0x01;    // (c) make PB0 in (built-in button)
  GPIO_PORTD_AFSEL_R &= ~0x01;  //     disable alt funct on PB0
  GPIO_PORTD_DEN_R |= 0x01;     //     enable digital I/O on PB0
  GPIO_PORTD_PCTL_R &= ~0x000F0000; //  configure PF4 as GPIO *****HOW DO I CHANGE THIS?*******
  GPIO_PORTD_AMSEL_R &= ~0x01;  //    disable analog functionality on PB0
  GPIO_PORTD_PUR_R |= 0x01;     //     enable weak pull-up on PBO
  GPIO_PORTD_IS_R &= ~0x01;     // (d) PBO is edge-sensitive
  GPIO_PORTD_IBE_R &= ~0x01;    //     PBO is not both edges
  GPIO_PORTD_IEV_R &= ~0x01;    //     PBO falling edge event
  GPIO_PORTD_ICR_R = 0x10;      // (e) clear flag4 ****DO I NEED TO CHANGE THIS?*****
  GPIO_PORTD_IM_R |= 0x01;      // (f) arm interrupt on PBO
  NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00A00000; // (g) priority 5
  NVIC_EN0_R = 0x40000000;      // (h) enable interrupt 30 in NVIC
  EnableInterrupts();	// (i) Enable global Interrupt flag (I)
	
	//Gdown=0;
	
}


void GPIOPortD_Handler(void){
  GPIO_PORTF_ICR_R = 0x10;      // acknowledge flag4
	Gdown=1;
	
}
