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
extern const unsigned short cutie[];
extern const unsigned short pixel[];
extern const unsigned short emoji[];

	
extern const unsigned short guns_n_roses[48];
extern const unsigned short wave[64];
extern const unsigned short end_song[22];
extern const unsigned short scream[3];
extern const unsigned short banana[4];
extern const unsigned short jump[2];
extern const unsigned short menu[2];


struct banana{
	int x;
	int y;
	int capt; // 0 if not capted by gorilla, 1 if captured
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
	int x;
	int y; 
	int oldx;
	int oldy;
	side pos;
	Status status;
	int score;
};
extern struct gorilla Gorilla;  

//platform struct
	struct platform{
		int x;
		int y;
		int length; 
	};
	
extern struct platform Platform[4]; 


