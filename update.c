#include <stdint.h>
#include "struct_definition.h"
#include "Update.h"
#include "global_variables.h"

//uint8_t Gdown;
void check_Bullet(){
	uint8_t i;	
	for(i=0;i<num_bullets;i++)
	{
		if((Bullet[i].x==Gorilla.x+15)&&((Bullet[i].y<Gorilla.y+15)&&(Bullet[i].y>=Gorilla.y))) // SEE GAMEPLAY AND CHANGE
		{
				Gorilla.status=DEAD;
		}
	}	
}

void moveGorilla(int x, int y)
{
	//shift the current Gorilla coord to the old coord
	Gorilla.oldx=Gorilla.x;
	Gorilla.oldy=Gorilla.y;
	
	//save new coord in Gorilla struct
	Gorilla.x=x;
	Gorilla.y=y;
	
	//determine if gorilla is moving left or right
	if((Gorilla.x)>(Gorilla.oldx))
		Gorilla.pos= RIGHT;
	else if((Gorilla.x)<(Gorilla.oldx))
		Gorilla.pos= LEFT;
}

void captBanana(void)
{
	int n;
	for(n=0; n<6; n++)
	{
		//check if gorilla captured banana while moving horizontally
		if((Gorilla.y>=(Bananas[n].y))&&(((Gorilla.y)<=((Bananas[n].y)+13))))
		{
			//checks if gorilla captured banana while moving from the right	
			if(Gorilla.pos==RIGHT)
				{
					if((((Gorilla.x)+15)==(Bananas[n].x)))
						Bananas[n].capt=CAPTURED;
				}
				
			//check if gorilla captured banana while moving from left
			if(Gorilla.pos==LEFT)
				{
					if((Gorilla.x)==((Bananas[n].x)+15))
						Bananas[n].capt=CAPTURED;
				}
		}
		//check if gorilla captured banana while moving up
		if((Gorilla.x>=(Bananas[n].x))&&(((Gorilla.x)<=((Bananas[n].x)+15))))
		{
			if((Gorilla.y<=(Bananas[n].y+13))&&(Gorilla.y>=Bananas[n].y))
				Bananas[n].capt=CAPTURED;
		}
	}
}

void gorillaLand(void)
{
	uint8_t m;
	for(m=0;m<4;m++)
	{
		if((Platform[m].x<=(Gorilla.x+15))&(Gorilla.x<=(Platform[m].x+Platform[m].length))&&((Platform[m].y<=Gorilla.y)&&(Platform[m].y+3>=Gorilla.y)))//need to add buffer of how much the gorrilla will move in the y direction
		{
			Gorilla.y=Platform[m].y+3;
			Gdown=0;//clear flag for downward direction
		}
		//add for floor
		else if(Gorilla.y==0)
		{
			Gdown=0;//clear flag for downward direction
		}
	}
}
