typedef enum {RIGHT,LEFT} side;
typedef enum {CAPTURED,NOTCAPTURED}capt;
typedef enum {ALIVE,DEAD}Status;
#define num_bullets 5

extern const unsigned short left2[];
extern const unsigned short right2[];
extern const unsigned short left[];
extern const unsigned short right[] ;
extern const unsigned short robot_clear[];
extern const unsigned short sprite_banana[];


struct banana{
	int x;
	int y;
	int capt; // 0 if not captured by gorilla, 1 if captured
};
extern struct banana Bananas[6];

struct bullet{
	int x;
	int oldx;
	int y;
	int oldy;
	int speed;	//flag that specifies if bullet should move
};
extern struct bullet Bullet[num_bullets];

//gorilla struct
struct gorilla{
	int x,oldx;
	int y,oldy;
	side pos;
	Status status;
};
extern struct gorilla Gorilla;  

//platform struct
	struct platform{
		int x;
		int y;
		int length; 
	};
	
extern struct platform Platform[4]; 


