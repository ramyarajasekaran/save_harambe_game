#include <stdint.h>
#include "struct_definition.h"
#include "ST7735.h"
#include "random.h"

void DisableInterrupts(void);
void EnableInterrupts(void);
void randomy(struct bullet element);


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
			if(Gorilla.pos==RIGHT)				// depends on the side the gorilla is facing/ADC moves
			ST7735_DrawBitmap(Gorilla.x,Gorilla.y, right, 15,15);
			else
			ST7735_DrawBitmap(Gorilla.x,Gorilla.y, left, 15,15);	
			
			ST7735_DrawBitmap(Gorilla.oldx,Gorilla.oldy, robot_clear, 15,15);
		}
		else													// WHEN GORILLA IS DEAD - blinks 3 times and disappears -- 
																	//set this as condn for while loop 
		{
			DisableInterrupts();
			ST7735_DrawBitmap(Gorilla.oldx,Gorilla.oldy, robot_clear, 15,15);
			while(i++<3)
			{
			if(Gorilla.pos == RIGHT)
				ST7735_DrawBitmap(Gorilla.x,Gorilla.y,right , 15,15);	//BLINKING with delay
			else
				ST7735_DrawBitmap(Gorilla.x,Gorilla.y,left , 15,15);
				
			//Delay100ms(2);
			
			ST7735_DrawBitmap(Gorilla.x,Gorilla.y, robot_clear, 15,15);
			}
			EnableInterrupts();
		}
		
		
		
		for(i=0;i<num_bullets;i++)								// PRINTING BULLETS MOVING
		{
			if(Bullet[i].x==0)		// go back to right side of the screen
				Bullet[i].x=120;
			if(Bullet[i].x==120)
			{
				randomy(Bullet[i]);		// change y coordinate of bullet
				ST7735_FillRect(0,Bullet[i].oldy ,5,3 , 0x0000);	//clean up old bullet
			}
			if(Bullet[i].speed==1)
			{
				Bullet[i].x-=2;
				Bullet[i].y-=2;
				ST7735_FillRect(Bullet[i].x,Bullet[i].y ,5,3 , 0xFFFF);
				ST7735_FillRect(Bullet[i].oldx,Bullet[i].oldy ,5,3 , 0x0000);
				Bullet[i].speed=0;
			}
			Bullet[i].oldx=Bullet[i].x;
			Bullet[i].oldy=Bullet[i].y;
						
		}

}

void randomy(struct bullet element){
	uint8_t temp;
	do{
		
		temp=Random32()%161;
		// checks if bullet crashes into platforms
	}while((temp>=145)||(((temp>=30)&&(temp<=33))||((temp>=60)&&(temp<=63))||((temp>=100)&&(temp<=103))||((temp>=110)&&(temp<=113))));
	element.y=temp;
}

