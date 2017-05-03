#include <stdint.h>
#include "struct_definition.h"
#include "ST7735.h"
#include "tm4c123gh6pm.h"
#include "random.h"
#include "ADC.h"

void DisableInterrupts(void);
void EnableInterrupts(void);
void Delay_100ms(uint32_t count);
uint8_t randomy(uint8_t);



void Display_Engine()
{		
	uint8_t i;
		//PLATFORMS
	ST7735_FillRect(25,30,30,3,0xFFFF);
	ST7735_FillRect(55,60,40,3,0xFFFF);
	ST7735_FillRect(15,110,20,3,0xFFFF);
	ST7735_FillRect(70,100,50,3,0xFFFF);

	
		for(i=0;i<6;i++)					// PRINTING BANANAS
	{
		if(Bananas[i].capt==NOTCAPTURED)			// Checking if banana has been captured
			ST7735_DrawBitmap(Bananas[i].x,Bananas[i].y ,sprite_banana , 15,13);
		else 
			ST7735_DrawBitmap(Bananas[i].x,Bananas[i].y ,robot_clear , 15,13);
	}
	
		i=0;
	
	
		if(Gorilla.status==ALIVE)				// PRINTING GORILLA
		{
			ST7735_DrawBitmap(Gorilla.oldx,Gorilla.oldy, robot_clear, 15,15);
			
			if(Gorilla.pos==RIGHT)				// depends on the side the gorilla is facing/ADC moves
			ST7735_DrawBitmap(Gorilla.x,Gorilla.y, right, 15,15);
			else
			ST7735_DrawBitmap(Gorilla.x,Gorilla.y,right2, 15,15);	
			
		}
		else													// WHEN GORILLA IS DEAD - blinks 3 times and disappears -- 
																	//set this as condn for while loop 
		{
			//DisableInterrupts();
			ST7735_DrawBitmap(Gorilla.oldx,Gorilla.oldy, robot_clear, 15,15);
			while(i++<3)
			{
			if(Gorilla.pos == RIGHT)
				ST7735_DrawBitmap(Gorilla.x,Gorilla.y,right , 15,15);	//BLINKING with delay

			else
				ST7735_DrawBitmap(Gorilla.x,Gorilla.y,right2 , 15,15);
				
			Delay_100ms(3);
			
			ST7735_DrawBitmap(Gorilla.x,Gorilla.y, robot_clear, 15,15);
			Delay_100ms(3);
			}
			//EnableInterrupts();
		}
		
		
		
		for(i=0;i<num_bullets;i++)								// PRINTING BULLETS MOVING
		{
			if(Bullet[i].x==0)		// go back to right side of the screen
				Bullet[i].x=120;
			if(Bullet[i].x==120)
			{
				Random_Init(ADC_In()*i);	// changes seed for the y coord generator
				Bullet[i].y=randomy(i);		// change y coordinate of bullet
				ST7735_FillRect(0,Bullet[i].oldy ,5,3 , 0x0000);	//clean up old bullet
			}
			if(Bullet[i].speed==1)
			{
				Bullet[i].x-=2;
				ST7735_FillRect(Bullet[i].x,Bullet[i].y ,5,3 , 0xFFFF);
				ST7735_FillRect(Bullet[i].oldx+2,Bullet[i].oldy ,5,3 , 0x0000);
				Bullet[i].speed=0;
			}
			Bullet[i].oldx=Bullet[i].x;
			Bullet[i].oldy=Bullet[i].y;
						
		}
		
}
void Delay_100ms(uint32_t count){uint32_t volatile time;
  while(count>0){
    time = 727240;  // 0.1sec at 80 MHz
    while(time){
	  	time--;
    }
    count--;
  }
}


uint8_t randomy(uint8_t i){
	uint8_t temp,max,min;
	switch(i){
		case 0:	{max=160;min=120;break;}
		case 1:	{max=120;min=80;break;}
		case 2: {max=80;min=40;break;}
		case 3: {max=40;min=10;break;}
		case 4: {max=10;min=0;break;}
	}
	do{
		
		temp=min+Random32()%(max-min+1);
		// checks if bullet crashes into platforms && bananas
	}while((temp>=140)||((temp>=27)&&(temp<=46))||((temp>=57)&&(temp<=76))||((temp>=97)&&(temp<=116))||((temp>=107)&&(temp<=126)));
	return temp;
}

