//  June kodea bukatu mese >;v
//  June kodea bukatu mese >;v
//  June kodea bukatu mese >;v

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <termios.h> //terminaleko interfaze orokorra. IO, asinkronoa...

#include "snake.h"



// Hemen honetan snake.h fitxategian agertzen diren funtzio eta egituren inplementazioa dago
// Snake.h-n deklaratzen dira fitxategi ezberdinetan funtzio berdinak erabili ahal izateko.
// Snake.h inportatzen den fitxategietan funtzioen inplementazioa inplizituki txertatuko da(func.c-ko inplementazioa)

extern struct snake *Snake;
extern struct apple *Apple;
extern int T; // Time counter
extern int current_speed;

void clear_screen()
{
	system("clear");
}

void goto_xy(int x, int y)
{
	printf("%c[%d;%dH", ESC, y, x);
}

void draw_scenery()
{
	int i, j;
	char c;
	goto_xy(X_BOUND, Y_BOUND); // Move the cursor to the scenery x, y start position
	for (j = 0; j < HEIGHT + 2; j++)
	{ // Columns: +2 because of the borders
		for (i = 0; i < WIDTH + 2; i++)
		{ // Rows: +2 because of the borders
			if (i == 0 || i == WIDTH + 1 || j == 0 || j == HEIGHT + 1)
				c = WALL;
			else
				c = ' ';
			printf("%c", c); // Print the character
			if (i == WIDTH + 1)
				goto_xy(X_BOUND, Y_BOUND + j + 1); // Jump to the next row
		}
	}
	printf("\n");
}

void create_snake()
{
	// HEAD
	Snake = (struct snake *)malloc(sizeof(struct snake));		// Allocate memory for the snake
	Snake->X = X_BOUND + WIDTH / 2;								// Set the x position of the snake
	Snake->Y = Y_BOUND + HEIGHT / 2;							// Set the y position of the snake
	Snake->APPEARANCE = HEAD_UP;								// Set the head direction of the snake
	Snake->COLOR = 31;											// Set the color of the snake (red)
																// First BODY
	Snake->next = (struct snake *)malloc(sizeof(struct snake)); // Allocate memory for the snake
	Snake->next->X = Snake->X;									// Set the x position of the snake
	Snake->next->Y = Snake->Y + 1;								// Set the y position of the snake
	Snake->next->APPEARANCE = SNAKE_BODY;						// Set the appearance of the snake
	Snake->next->COLOR = 32;									// Set the color of the snake (green)
	Snake->next->next = NULL;									// Set the next element to NULL
}

void draw_snake(struct snake *body)
{
	printf("%c[1;%dm", ESC, body->COLOR); // Set the color of the snake
	goto_xy(body->X, body->Y);			  // Move the cursor to the snake x, y position
	printf("%c\n", body->APPEARANCE);	  // Print the snake part
	printf("%c[0m", ESC);				  // Unset the color of the snake
	if (body->next != NULL)
	{
		draw_snake(body->next); // Draw the next snake element
	}
};

void move_snake(int x, int y, struct snake *body)
{
	if (body->next != NULL)
	{
		// Move the next element
		move_snake(body->X, body->Y, body->next);
	}
	else
	{
		// Move the cursor to the snake x, y position
		goto_xy(body->X, body->Y);
		printf(" "); // Clear the snake tail
	}
	body->X = x; // Set the x position of the snake
	body->Y = y; // Set the y position of the snake
}

void create_apple()
{
	// Allocate memory for the apple
	Apple = (struct apple *)malloc(sizeof(struct apple));
	Apple->APPEARANCE = APPLE_BODY; // Set the body of the apple
	reposition_apple();				// Reposition the apple
	revalue_apple();				// Set the color and points of the apple
}

void reposition_apple()
{
	Apple->X = X_BOUND + 1 + rand() % WIDTH;  // Set the x position of the apple
	Apple->Y = Y_BOUND + 1 + rand() % HEIGHT; // Set the y position of the apple
}

void revalue_apple()
{
	if (rand() % 100 < PROB_GOLD)
	{								// If the probability of the current apple is up to 25 (gold)
		Apple->COLOR = 33;			// Set the color of the apple to yellow
		Apple->POINTS = GOLD_APPLE; // Set the score of the apple to 5
	}
	else
	{
		Apple->COLOR = 31;		   // Set the color of the apple to red
		Apple->POINTS = RED_APPLE; // Set the score of the apple to 1
	}
}

void draw_apple()
{
	printf("%c[1;%dm", ESC, Apple->COLOR); // Set the color of the apple
	goto_xy(Apple->X, Apple->Y);		   // Move the cursor to the apple x, y position
	printf("%c\n", Apple->APPEARANCE);	   // Print the apple
	printf("%c[0m", ESC);				   // Unset the color of the apple body
}

// teklatuko sarrerako funtzioak:
int kbhit()
{
	struct timeval tv;
	fd_set rdfs;
	tv.tv_sec = 0;
	tv.tv_usec = 0;
	FD_ZERO(&rdfs);
	FD_SET(STDIN_FILENO, &rdfs);
	select(STDIN_FILENO + 1, &rdfs, NULL, NULL, &tv);
	return FD_ISSET(STDIN_FILENO, &rdfs);
}

int input_control(struct snake *body, int dir[2])
{				 // Check the input control
	int key = 0; // Key pressed
				 // Check if a key was pressed
	if (kbhit())
	{					 // If a key was pressed
		key = getchar(); // Get the key pressed
		switch (key)
		{
		case UP: // If the key pressed is UP
				 // if previous direction is not down
			if ((dir[1] == 0) && (body->APPEARANCE != HEAD_DOWN))
			{
				dir[0] = 0;					// Set the x direction to 0
				dir[1] = -1;				// Set the y direction to -1
				body->APPEARANCE = HEAD_UP; // Set the snake head direction
			}
			break;
		case DOWN: // If the key pressed is DOWN
				   // if previous direction is not up
			if ((dir[1] == 0) && (body->APPEARANCE != HEAD_UP))
			{
				dir[0] = 0;				 // Set the x direction to 0
				dir[1] = 1;				 // Set the y direction to 1
				body->APPEARANCE = DOWN; // Set the snake head direction
			}
			break;
		case RIGHT: // If the key pressed is RIGHT
					// if previous direction is not left
			if ((dir[0] == 0) && (body->APPEARANCE != HEAD_LEFT))
			{
				dir[0] = 1;					   // Set the x direction to 1
				dir[1] = 0;					   // Set the y direction to 0
				body->APPEARANCE = HEAD_RIGHT; // Set the snake head direction
			}
			break;
		case LEFT: // If the key pressed is LEFT
				   // if previous direction is not right
			if ((dir[0] == 0) && (body->APPEARANCE != HEAD_RIGHT))
			{
				dir[0] = -1;				  // Set the x direction to -1
				dir[1] = 0;					  // Set the y direction to 0
				body->APPEARANCE = HEAD_LEFT; // Set the snake head direction
			}
			break;
		}
	}
}

void changemode(int dir)
{
	static struct termios oldt, newt;
	if (dir == 1)
	{											 // Set the terminal mode to non-canonical mode (no echo)
		printf("%c[?25l", ESC);					 // Hide the cursor
		tcgetattr(STDIN_FILENO, &oldt);			 // Get the terminal mode
		newt = oldt;							 // Save the old terminal mode
		newt.c_lflag &= ~(ICANON | ECHO);		 // Change the terminal mode to non-canonical mode (no echo)
		tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Set the new terminal mode
	}
	else
	{											 // Set the terminal mode to canonical mode (echo)
		tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Set the old terminal mode (Restore)
		printf("%c[?25h", ESC);					 // Show the cursor
	}
}

int speed_control()
{
	usleep(FRAMERATE * 1000); // Sleep (microseconds) for the fram rate
	T += FRAMERATE;			  // Update the time counter
							  // If the time counter is greater than the snake speed
	return (T >= current_speed);
}

void collision_apple(struct snake *body)
{
	// Check the collision with the apple
	if (body->X == Apple->X && body->Y == Apple->Y)
	{
		for (int i = 0; i < Apple->POINTS; i++)
		{					   // For each point of the apple
			grow_snake(Snake); // Grow the snake
			// Increase the speed of the snake
			if (current_speed >= SPEED_INC)
			{								// If the speed is greater than SPEED_INC
				current_speed -= SPEED_INC; // Decrease the speed by SPEED_INC
			}
		}
		reposition_apple(); // Reposition the apple
		revalue_apple();	// Set the color and points of the apple
	}
}

void grow_snake(struct snake *body)
{
	if (body->next != NULL)
	{
		grow_snake(body->next); // Move to the next snake element
	}
	else
	{															   // If the snake has no more elements(last element), add a new element
		body->next = (struct snake *)malloc(sizeof(struct snake)); // Allocate memory for the snake
		body->next->X = body->X;								   // Set the x position of the snake
		body->next->Y = body->Y;								   // Set the y position of the snake
		body->next->APPEARANCE = SNAKE_BODY;					   // Set the appearance of the snake
		body->next->COLOR = 32;									   // Set the color of the snake (green)
		body->next->next = NULL;								   // Set the next element to NULL
	}
}
