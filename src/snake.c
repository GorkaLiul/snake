#include "snake.h"

int game_over;

struct snake *Snake;
struct apple *Apple;


int T = 0; // Time counter
int current_speed = SPEED;

void main(){

	game_over = 0;
	int dir[2] = {0, -1}; // {x,y} Snake direction (up)

	clear_screen();
	draw_scenery();
	draw_snake(Snake);

	draw_apple();
	while (!game_over) {
	//todo

		input_control(Snake, dir); // Input control
		draw_snake(Snake); // Draw the snake
		draw_apple();

		move_snake(Snake->X + dir[0], Snake->Y + dir[1], Snake);
		T = 0;//reset time
	}
}
