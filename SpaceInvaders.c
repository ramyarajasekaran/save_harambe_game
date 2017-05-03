// SpaceInvaders.c
// Runs on LM4F120/TM4C123
// Jonathan Valvano and Daniel Valvano
// This is a starter project for the EE319K Lab 10

// Last Modified: 3/6/2015 
// http://www.spaceinvaders.de/
// sounds at http://www.classicgaming.cc/classics/spaceinvaders/sounds.php
// http://www.classicgaming.cc/classics/spaceinvaders/playguide.php
/* This example accompanies the books
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2014

   "Embedded Systems: Introduction to Arm Cortex M Microcontrollers",
   ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2014

 Copyright 2015 by Jonathan W. Valvano, valvano@mail.utexas.edu
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
// ******* Possible Hardware I/O connections*******************
// Slide pot pin 1 connected to ground
// Slide pot pin 2 connected to PE2/AIN1
// Slide pot pin 3 connected to +3.3V 
// fire button connected to PE0
// special weapon fire button connected to PE1
// 8*R resistor DAC bit 0 on PB0 (least significant bit)
// 4*R resistor DAC bit 1 on PB1
// 2*R resistor DAC bit 2 on PB2
// 1*R resistor DAC bit 3 on PB3 (most significant bit)
// LED on PB4
// LED on PB5

// Backlight (pin 10) connected to +3.3 V
// MISO (pin 9) unconnected
// SCK (pin 8) connected to PA2 (SSI0Clk)
// MOSI (pin 7) connected to PA5 (SSI0Tx)
// TFT_CS (pin 6) connected to PA3 (SSI0Fss)
// CARD_CS (pin 5) unconnected
// Data/Command (pin 4) connected to PA6 (GPIO), high for data, low for command
// RESET (pin 3) connected to PA7 (GPIO)
// VCC (pin 2) connected to +3.3 V
// Gnd (pin 1) connected to ground

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "ST7735.h"
#include "Random.h"
#include "Timer2.h"
#include "TExaS.h"
#include "ADC.h"
#include "Button.h"
#include "Timer0.h"
#include "Update.h"
#include "DAC.h"
#include "global_variables.h"
#include "struct_definition.h"
#include "Sound.h"



 #define PF1       (*((volatile uint32_t *)0x40025008))

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void Delay100ms(uint32_t count); // time delay in 0.1 
void Delay10ms(uint32_t count);
void display_bullets(void);
void display_gorilla(uint8_t x,uint8_t y);	
void check_Bullet(void);
void Display_Engine(void);
void Timer0_Init(void(*task)(void), uint32_t period);
void UserTask0A(void);
void PortAinit(void);
void Timer1_Init(void(*task)(void), uint32_t period);

uint32_t ADCMail,ADCStatus=0,check=0,check1=0;

uint32_t Convert(uint32_t mailbox){
	mailbox=113*mailbox/4096;
	
	return mailbox;
}

// ************* Capture image dimensions out of BMP**********
uint32_t newX, newY=160, value2;
uint8_t y,i=0;

volatile int seed;
int main(void){
	
  TExaS_Init();  // set system clock to 80 MHz
  Random_Init(seed);		// to generate new random number everytime
	ADC_Init();
	SysTick_Init(2000000);
	DAC_Init();
	Output_Init();
	
	ST7735_FillScreen(0x0000);            // set screen to black		
	Timer0_Init(&UserTask0A,150000);				// Timer for bullets' speed
	Button_Init();
	
	
	volatile uint32_t delay;

	SYSCTL_RCGCSSI_R |= 0x01;  // activate SSI0
  SYSCTL_RCGCGPIO_R |= 0x01; // activate port A
  while((SYSCTL_PRGPIO_R&0x01)==0){}; // allow time for clock to start
	delay=5;
  // toggle RST low to reset; CS low so it'll listen to us
  // SSI0Fss is temporarily used as GPIO
  GPIO_PORTA_DIR_R |= 0xC8;             // make PA3,6,7 out
  GPIO_PORTA_AFSEL_R &= ~0xC8;          // disable alt funct on PA3,6,7
  GPIO_PORTA_DEN_R |= 0xC8;             // enable digital I/O on PA3,6,7
                                        // configure PA3,6,7 as GPIO
  GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0x00FF0FFF)+0x00000000;
  GPIO_PORTA_AMSEL_R &= ~0xC8;          // disable analog functionality on PA3,6,7
		
	//display main menu
		
		sound_flag=ALIVE0;
		Song_Play();
		
		char* ptr = "SAVE HARAMBE!";
		ST7735_FillScreen(0xFFFF);
		ST7735_DrawString(5, 2, ptr, 0x0000);
		ST7735_DrawBitmap(15,100 ,emoji,100,70);
while(GPIO_PORTF_DATA_R&0X01){	
		
		char* ptr2 = "PLAY LEVEL 1";
		ST7735_DrawString(6, 10, ptr2, 0x0000);
		char* ptr3 = "PLAY LEVEL 2";
		ST7735_DrawString(6, 13, ptr3, 0x0000);
		if(ADCMail<2048)
		{
			ST7735_DrawString(6, 10, ptr2, 0xF0CF);
			level1=1;
		}
		else
		{
			ST7735_DrawString(6, 13, ptr3, 0xF0CF);
			level1=0;
		}
		Delay100ms(2);
		
	}		
			sound_flag=MENU;
			Sound_Play(2);
		
		
		
			ST7735_FillScreen(0x0000); 
			
			sound_flag=ALIVE0;
			
	while(dead_flag==0) //check if end game button is pressed OR if gorilla is dead
	{
		
		
		//1. read ADC
		while(ADCStatus!=1){}
			ADCStatus=0;
		newX = Convert(ADCMail);
		//2. read button
		if(Gdown)
			{newY+=2;}
		else if(!(GPIO_PORTF_DATA_R&0x10))
			{
				Gdown=0;
				newY-=2;
				sound_flag=JUMP;
			}
		//3. change coordinate of gorilla in struct
		if(Gdown)	
			gorillaLand();
			
		moveGorilla(newX, newY);
		gorilla_fall();	
		//4.Check if Gorilla is hit by Bullet
		check_Bullet();
		//5. Check if Gorilla captured the Banana
		captBanana();	
		//6.display board
		
		Display_Engine();
			
	}
	
	sound_flag=DEAD0;
	//end screen, do display of end screen here

		if(Gorilla.score==60)
	{
		ST7735_FillScreen(0xFFFF);
		ptr = "HARAMBE IS ";
		ST7735_DrawString(1, 5, ptr, 0xF0CF);
		ptr="HAPPY AGAIN!";
		
	  ST7735_DrawString(7, 7, ptr, 0x00FF);
		ptr = "YOU ARE THE ";
		ST7735_DrawString(1, 10, ptr, 0xF0CF);
		ptr=	"	MEME QUEEN/KING ";
		ST7735_DrawString(3,12, ptr, 0x001F);
		ptr= "OF 2K17!";
		ST7735_DrawString(8, 14, ptr, 0xF0CF);
		Delay100ms(20);
	}
	
	ST7735_FillScreen(0x0000);
	char*	ptr2 ="RIP HARAMBE";
	ST7735_DrawString(7, 9, ptr2, 0xFFFF);
	ST7735_DrawBitmap(35,70 ,pixel,75,63);	
	
			
		
  ptr2="GAME OVER!";
	ptr = "SCORE";
	
	ST7735_DrawString(8, 14, ptr, 0xFFFF);
	ST7735_SetCursor(17,14);
	LCD_OutDec(Gorilla.score);
while(1){		 
	ST7735_DrawString(2, 11, ptr2, 0xFFFF);
	Delay100ms(5);	 
	ST7735_DrawString(2, 11, ptr2, 0x0000);
	Delay100ms(5);
	}

}


void Delay100ms(uint32_t count){uint32_t volatile time;
  while(count>0){
    time = 727240;  // 0.1sec at 80 MHz
    while(time){
	  	time--;
    }
    count--;
  }
}

void SysTick_Init(uint32_t period){
  NVIC_ST_CTRL_R &= 0xFE;         // disable SysTick during setup
  NVIC_ST_RELOAD_R = period-1;// reload value
  NVIC_ST_CURRENT_R = 0;      // any write to current clears it
  NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x20000000; // priority 1
  NVIC_ST_CTRL_R = 0x0006; // enable SysTick with core clock and interrupts
	NVIC_ST_CTRL_R|=0x01; //enables clock
}

void SysTick_Handler(void){

	ADCMail= ADC_In();		// grab sample and put in the mailbox
	ADCStatus=1;			// set flag
	
}




