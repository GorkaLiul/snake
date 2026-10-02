#define ESC 27
#define WALL '#'

#define  HEIGHT 60
#define  WIDTH 60 
#define  X_BOUND 3
#define  Y_BOUND 3

#define FRAMERATE 16 //ms-tan adierazita dago. 16ms -> 60fps
#define SPEED 150
#define SPEED_INC 2
// Define keys

#define UP 119 // Define UP constant (w: 119)
#define DOWN 115 // Define DOWN constant (s: 115)
#define RIGHT 100 // Define RIGHT constant (d: 100)
#define LEFT 97 // Define LEFT constant (a: 97)

						   //
// sugearen elementuen ascii balioa 
#define HEAD_UP 118 // 'v'
#define HEAD_DOWN 94 // '^'
#define HEAD_LEFT 62 // '>'
#define HEAD_RIGHT 60 // '<'
#define SNAKE_BODY 64 // '@

//sagarrak
#define GOLD_APPLE 5 // 5 puntu
#define RED_APPLE 1 // 1 puntu
#define PROB_GOLD 25 // Probabilities of the gold apples
#define APPLE_BODY 111 // 'o' karakterea


//Egiturak: 
struct snake {
	int X; // X position of the snake
	int Y; // Y position of the snake
	struct snake *next; // Pointer to the next snake element
	int APPEARANCE; 
	int COLOR; 
	int LENGTH; // sugearen luzeera
};

//sagarrak: 
struct apple {
	int X; // X position of the apple
	int Y; // Y position of the apple
	int APPEARANCE; // Appearance of the apple
	int COLOR; // Color of the apple
	int POINTS; // Score of the apple
};



//funtzioak (orokorrak)
void clear_screen();
void goto_xy(int x, int y );
void draw_scenery();

void change_mode(int);
int speed_control(); //abiadura aldatu
		     //
//funtzioak (teklatuko sarrera, mugimendua...)
int kbhit(void); // Check if a key was pressed
int input_control(struct snake *body, int dir[2]); // Check the input


//funtzioak sugearako: 
void create_snake(); // Create the snake
void draw_snake(struct snake *body);
void move_snake(int x, int y , struct snake *body);


//funtzioak sagarrentzako: 
void draw_apple(); 
void create_apple (); 
void reposition_apple(); 
void revalue_apple();

void collision_apple(struct snake *body);
void grow_snake(struct  snake *body);

// Check the collision of the snake with the wall
int collision_snake_wall(struct snake *body);
