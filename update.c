#include <stdint.h>
#include "struct_definition.h"
#include "Update.h"
#include "global_variables.h"
#include "Timer2.h"


void check_Bullet(){
	uint8_t i;	
	for(i=0;i<num_bullets;i++)
	{
		if(((Bullet[i].x<=Gorilla.x+17)&&((Bullet[i].x>=Gorilla.x))&&((Bullet[i].y<=Gorilla.y)&&(Bullet[i].y>=Gorilla.y-17))) )// SEE GAMEPLAY AND CHANGE
		{
				Gorilla.status=DEAD;
				dead_flag=1;
				sound_flag=SCREAM;
				break;
		}
	}	
}

void moveGorilla(int x, int y)
{
	//check if in LCD range
	if(y>=160)
	{y=160;}
	
	if(y<=15)
	{y=15;}
	
	//shift the current Gorilla coord to the old coord
	Gorilla.oldx=Gorilla.x;
	Gorilla.oldy=Gorilla.y;
	
	//save new coord in Gorilla struct
	Gorilla.x=x;
	Gorilla.y=y;
	
	//determine if gorilla is moving left or right
	if((Gorilla.x)>(Gorilla.oldx+3))
		Gorilla.pos= RIGHT;
	else
		Gorilla.pos= LEFT;
}

void captBanana(void)
{
	
	int n;
	for(n=0; n<6; n++)
	{
		if(Bananas[n].capt==NOTCAPTURED)
			{
		//check if gorilla captured banana while moving horizontally
		if((Gorilla.y>=(Bananas[n].y))&&(((Gorilla.y)<=((Bananas[n].y)+13))))
		{
			//checks if gorilla captured banana while moving from the right	
			if(Gorilla.pos==RIGHT)
				{
					if(((Gorilla.x)+15)==(Bananas[n].x))
					{
						Bananas[n].capt=CAPTURED;
						Gorilla.score+=10;
						sound_flag=BANANA;
						
					}
				}
				
			//check if gorilla captured banana while moving from left
			if(Gorilla.pos==LEFT)
				{
					if((Gorilla.x)==((Bananas[n].x)+15))
					{
						Bananas[n].capt=CAPTURED;
						Gorilla.score+=10;
						sound_flag=BANANA;
					}
				}
		}
		//check if gorilla captured banana while moving up
		if((Gorilla.x>=(Bananas[n].x))&&(((Gorilla.x)<=((Bananas[n].x)+15))))
			{
			if(((Gorilla.y<=(Bananas[n].y+13))&&(Gorilla.y>=Bananas[n].y)))
				{
						Bananas[n].capt=CAPTURED;
						Gorilla.score+=10;
						sound_flag=BANANA;
				}
			}
		}
	}
}

void gorillaLand(void)
{
	uint8_t m;
	for(m=0;m<4;m++)
	{
		if((Platform[m].x<=(Gorilla.x+15))&&(Gorilla.x<=(Platform[m].x+Platform[m].length))&&((Platform[m].y<=Gorilla.y)&&(Platform[m].y+3>=Gorilla.y)))//need to add buffer of how much the gorrilla will move in the y direction
		{
			Gorilla.y=Platform[m].y+3;
			Gdown=0;//clear flag for downward direction
		}
		
		//add for floor
		else if(Gorilla.y>=153&&Gorilla.y<=163)
		{
			Gorilla.y=160;
			Gdown=0;//clear flag for downward direction
		}

	}
}

void gorilla_fall(){
	int m;
	for(m=0;m<4;m++)
	{
	
	if(((Platform[m].x<=(Gorilla.oldx+15))&&(Gorilla.oldx<=(Platform[m].x+Platform[m].length)))&&((Platform[m].y<=Gorilla.y)&&(Platform[m].y+3>=Gorilla.y))&&!((Platform[m].x<=(Gorilla.x+15))&&(Gorilla.x<=(Platform[m].x+Platform[m].length))))
		{
			Gdown=1;
		}

	}
}

