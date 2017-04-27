typedef enum {RIGHT,LEFT} side;
typedef enum {CAPTURED,NOTCAPTURED}capt;
typedef enum {ALIVE,DEAD}Status;

#define num_bullets 5

//gorilla struct
struct gorilla{
	int x,oldx;
	int y,oldy;
	side pos;
	Status status;
};
//declare initial Gorrilla Position here
//128 x, 160 y
struct gorilla Gorilla= {0, 160, RIGHT,ALIVE};  

struct banana{
	int x;
	int y;
	int capt; // 0 if not captured by gorilla, 1 if captured
};
// w = 15 h = 13 BANANA
struct banana Bananas[6 /*number of bananas on screen*/]= {
	//declare bananas here, all capt are declared as 0
	{27,28,NOTCAPTURED},{50,58,NOTCAPTURED},
	{70,58,NOTCAPTURED},{17,108,NOTCAPTURED},
	{75,98,NOTCAPTURED},{95,98,NOTCAPTURED}
};

struct bullet{
	int x;
	int oldx;
	int y;
	int oldy;
	int speed;
};


struct bullet Bullets[num_bullets]= {
	//declare bullets here
	{120},{120},{120},{120},{120}
};

void Display_Engine()
{		
		uint8_t i;
		for(i=0;i<6;i++)
	{
		if(Bananas[i].capt==NOTCAPTURED)			// Checking if banana has been captured
			ST7735_DrawBitmap(Bananas[i].x,Bananas[i].y ,sprite_banana , 15,13);
		else 
			ST7735_DrawBitmap(Bananas[i].x,Bananas[i].y ,robot_clear , 15,13);
	}
		if(Gorilla.status==ALIVE)				// prints gorilla only if its alive
		{
			if(Gorilla.pos==RIGHT)				// depends on the side the gorilla is facing/ADC moves
			ST7735_DrawBitmap(Gorilla.x,Gorilla.y, right, 15,15);
			else
			ST7735_DrawBitmap(Gorilla.x,Gorilla.y, left, 15,15);	
			
			ST7735_DrawBitmap(Gorilla.oldx,Gorilla.oldy, robot_clear, 15,15);
		}
		else
			ST7735_DrawBitmap(Gorilla.x,Gorilla.y, robot_clear, 15,15);	//BLINKING wiht delay
		for(i=0;i<num_bullets;i++)								// Prints bullets
		{
			ST7735_FillRect(Bullet[i].x,Bullet[i].y ,5,3 , 0xFFFF);
			ST7735_FillRect(Bullet[i].oldx,Bullet[i].oldy ,5,3 , 0x0000);
		}


}

void check_Bullet(){
	uint8_t i;	
	for(i=0;i<num_bullets;i++)
	{
		if((Bullets[i].x==Gorilla.x+15)&&((Bullets[i].y<Gorilla.y+15)&&(Bullets[i].y>=Gorilla.y))) // SEE GAMEPLAY AND CHANGE
		{
				Gorilla.status=DEAD;
		}
	}	
}