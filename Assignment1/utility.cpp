/*
COMP 369 Assignment 2 - Space Game
utility.cpp
@author: Chris Kidney
		 Student ID: 3251456
@date: Oct 16th, 2018
Class Description: Contains routines and functions for various actions used throughout the program, including gameplay functions, input control and sound control. 

					A handful of functions in this class are modified versions of functions from the tank war project in the textbook 'Game Programming All In One by Jonathan S. Harbour'
					Modified functions are:
						inside()
						draw, move and erase ship and enemy functions
						movement control functions
						getinput()
						setup()
						firelaser()
						updatelaser()
						explode()
					
					**NOTE** See commented note in drawEnemy() **
*/
#include "spacegame.h"

bool anim = true;

int score = 0;
int life = 3;
int enemyMaxSpd = 2;
int enemySpdMulti = 1;

SPRITE theplayer[2];
SPRITE *player[2];
SPRITE theenemy[2];
SPRITE *enemy[2];
SPRITE thelaser[2];
SPRITE *laser[2];

BITMAP *ship_bmp[2][8];
BITMAP *enemy_bmp[2][8];
BITMAP *laser_bmp;
BITMAP *explosion_bmp;


/////////////////////////////
// Mouse Position Function //
/////////////////////////////
int mousePos(int x1, int y1, int x2, int y2)
{
	if (mouse_x > x1 && mouse_x < x2 && mouse_y > y1 && mouse_y < y2)
		return 1;
	else
		return 0;
}

///////////////////
//Inside Function//
///////////////////
int inside(int x, int y, int left, int top, int right, int bottom)
{
	if (x > left && x < right && y > top && y < bottom)
		return 1;
	else
		return 0;
}

///////////////////////////
//Draw & Move Player Ship//
///////////////////////////
void drawShip(int num) {
	// Load sound effect for ship engine
	SAMPLE *thruster;
	if (install_sound(DIGI_AUTODETECT, MIDI_NONE, "") != 0) {
		allegro_message("Error initializing sound system.");
	}
	thruster = load_sample(THRUSTERSOUND);
	if (!thruster) {
		allegro_message("Error reading .wav file");
	}


	int dir = player[num]->dir;
	int x = player[num]->x - 15;
	int y = player[num]->y - 15;
	if (player[num]->xspeed > 0) {
		draw_sprite(screen, ship_bmp[1][dir], x, y);
		play_sample(thruster, 100, 128, 1000, FALSE);
	}
	else {
		draw_sprite(screen, ship_bmp[num][dir], x, y);
	}

}
void eraseShip(int num) {
	int x = player[num]->x - 17;
	int y = player[num]->y - 17;
	rectfill(screen, x, y, x + 33, y + 33, BLACK);
}
void moveShip(int num) {
	int dir = player[num]->dir;
	int speed = player[num]->xspeed;

	//Update player ship based on direction
	switch (dir)
	{
	case 0:
		player[num]->y -= speed;
		break;
	case 1:
		player[num]->x += speed;
		player[num]->y -= speed;
		break;
	case 2:
		player[num]->x += speed;
		break;
	case 3:
		player[num]->x += speed;
		player[num]->y += speed;
		break;
	case 4:
		player[num]->y += speed;
		break;
	case 5:
		player[num]->x -= speed;
		player[num]->y += speed;
		break;
	case 6:
		player[num]->x -= speed;
		break;
	case 7:
		player[num]->x -= speed;
		player[num]->y -= speed;
		break;
	}

	//Cause player ship to screen wrap 
	if (player[num]->x > SCREEN_W) {
		player[num]->x = -32;
		player[num]->xspeed = 2;
	}
	if (player[num]->y > SCREEN_H) {
		player[num]->y = -32;
		player[num]->xspeed = 2;
	}

	if (player[num]->x < -32) {
		player[num]->x = SCREEN_W - 10;
		player[num]->xspeed = 2;
	}
	if (player[num]->y < -32) {
		player[num]->y = SCREEN_H - 10;
		player[num]->xspeed = 2;
	}


	int x = player[0]->x;
	int y = player[0]->y;
	int ex = enemy[0]->x;
	int ey = enemy[0]->y;

	if (inside(x , y , ex-16, ey-16, ex + 32, ey + 32))
	{
		// If hit occurs, remove 1 life from player, play explosion animation, spawn new enemy ship
		life--;
		explode(0);
	}

}

//////////////////////////
//Draw & Move Enemy Ship//
//////////////////////////
void drawEnemy(int num) {
	int dir = enemy[num]->dir;
	int x = enemy[num]->x - 15;
	int y = enemy[num]->y - 15;	

	//////////////////////////////////////////////////////////////////
	//    NOTE: Commented out code below was used to animate the	//
	//		enemy ship's sprite. It does work when added back in	//
	//		but causes a random crash during gameplay. I decided	//
	//		to cut it out in favor of not crashing but left the		//
	//		code in incase I can resolve the error.					//
	//////////////////////////////////////////////////////////////////

	//if (anim) {
		draw_sprite(screen, enemy_bmp[num][dir], x, y);
	//}
	//else {
	//	draw_sprite(screen, enemy_bmp[1][dir], x, y);
	//}
	//anim = !anim;
}
void eraseEnemy(int num) {
	int x = enemy[num]->x - 17;
	int y = enemy[num]->y - 17;
	rectfill(screen, x, y, x + 33, y + 33, BLACK);
}
void moveEnemy(int num) {
	enemy[num]->xspeed++;
	if (enemy[num]->xspeed > enemyMaxSpd)
		enemy[num]->xspeed = enemyMaxSpd;

	int dir = enemy[num]->dir;
	int speed = enemy[num]->xspeed;

	//Update enemy ship based on direction
	switch (dir)
	{
	case 0:
		enemy[num]->y -= speed;
		break;
	case 1:
		enemy[num]->x += speed;
		enemy[num]->y -= speed;
		break;
	case 2:
		enemy[num]->x += speed;
		break;
	case 3:
		enemy[num]->x += speed;
		enemy[num]->y += speed;
		break;
	case 4:
		enemy[num]->y += speed;
		break;
	case 5:
		enemy[num]->x -= speed;
		enemy[num]->y += speed;
		break;
	case 6:
		enemy[num]->x -= speed;
		break;
	case 7:
		enemy[num]->x -= speed;
		enemy[num]->y -= speed;
		break;
	}

	// Cause enemy ships to screen wrap
	if (enemy[num]->x > SCREEN_W) {
		enemy[num]->x = -32;
		enemy[num]->xspeed = 2;
	}
	if (enemy[num]->y > SCREEN_H) {
		enemy[num]->y = -32;
		enemy[num]->xspeed = 2;
	}

	if (enemy[num]->x < -32) {
		enemy[num]->x = SCREEN_W - 10;
		enemy[num]->xspeed = 2;
	}
	if (enemy[num]->y < -32) {
		enemy[num]->y = SCREEN_H - 10;
		enemy[num]->xspeed = 2;
	}


}

////////////////////
//Movement Control//
////////////////////
void forward(int num)
{
	player[num]->xspeed++;
	if (player[num]->xspeed > MAXSPEED)
		player[num]->xspeed = MAXSPEED;
}
void backward(int num)
{
	player[num]->xspeed--;
	if (player[num]->xspeed <= 0)
		player[num]->xspeed = 0;
}
void turnleft(int num)
{
	player[num]->dir--;
	if (player[num]->dir < 0)
		player[num]->dir = 7;
}
void turnright(int num)
{
	player[num]->dir++;
	if (player[num]->dir > 7)
		player[num]->dir = 0;
}

////////////////////////////
//Background Music Control//
////////////////////////////
void musicControl() {
	MIDI *music;
	if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) != 0) {
		allegro_message("Error initializing sound system\n%s\n", allegro_error);
	}
	//load the midi file
	music = load_midi(BACKGROUND);
	set_volume(235,145);

	if (!music) {
		allegro_message("Error loading Midi file");
	}

	if (play_midi(music, 0) != 0) {
		allegro_message("Error playing Midi\n%s", allegro_error);

	}
}

/////////////
//Get Input//
/////////////
void getInput()
{
	static bool chk = true;

	//WASD + SPACE keys control player ship
	if (key[KEY_W])     forward(0);
	if (key[KEY_D])     turnright(0);
	if (key[KEY_A])     turnleft(0);
	if (key[KEY_S])     backward(0);
	if (key[KEY_SPACE]) fireLaser(0);

	// ESC to quit game
	if (key[KEY_ESC]) allegro_exit();

	// Mute / Play music control
	if (key[KEY_M]){
		if (key_shifts & KB_CTRL_FLAG) {
			chk = !chk;
			if (chk == false) {
				midi_pause();
			}
			else {
				midi_resume();
			}
			rest(50);
		}
	}


	// Go to Help Menu if CTRL+H is pressed
	if (key[KEY_H]) {
		if (key_shifts & KB_CTRL_FLAG) {
			gameState = 3;
		}
	}

	//short delay after keypress        
	rest(20);
}

/////////////////
//Score Display//
/////////////////
void scoreDisplay() {
	std::string conv = std::to_string(score);
	const char * con = conv.c_str();

	rectfill(screen, SCREEN_W - 80, 0, SCREEN_W - 20, 10, BLACK);
	textprintf_centre_ex(screen, font, SCREEN_W - 55, 5, WHITE, -1, "Score:");	
	textprintf_centre_ex(screen, font, SCREEN_W - 25, 5, WHITE, -1, con);
}

/////////////////
//Life Display//
/////////////////
void lifeDisplay() {
	std::string conv = std::to_string(life);
	const char * con = conv.c_str();


	rectfill(screen, 0, 0, 80, 10, BLACK);
	textprintf_centre_ex(screen, font, SCREEN_W - 600, 5, WHITE, -1, "Lives:");
	textprintf_centre_ex(screen, font, SCREEN_W - 565, 5, WHITE, -1, con);
}

//////////////
//Setup Game//
//////////////
void setup()
{
	scoreDisplay();
	lifeDisplay();

	int n;
//Player Ship
	//Configure player's ship
	player[0] = &theplayer[0];
	player[0]->x = 30;
	player[0]->y = 50;
	player[0]->xspeed = 0;
	score = 0;
	life = 3;
	player[0]->dir = 3;

	//Load first ship bitmap
	ship_bmp[0][0] = load_bitmap(PLAYERSPRITE, NULL);

	//Rotate image to generate all 8 directions
	for (n = 1; n<8; n++)
	{
		ship_bmp[0][n] = create_bitmap(32, 32);
		clear_bitmap(ship_bmp[0][n]);
		rotate_sprite(ship_bmp[0][n], ship_bmp[0][0],
			0, 0, itofix(n * 32));
	}

	//Load second ship bitmap
	ship_bmp[1][0] = load_bitmap(PLAYERSPRITE2, NULL);

	//Rotate image to generate all 8 directions
	for (n = 1; n<8; n++)
	{
		ship_bmp[1][n] = create_bitmap(32, 32);
		clear_bitmap(ship_bmp[1][n]);
		rotate_sprite(ship_bmp[1][n], ship_bmp[1][0],
			0, 0, itofix(n * 32));
	}

	// Spawn initial enemy ship
	spawnEnemy();

// Laser
	//Load laser image
	if (laser_bmp == NULL)
		laser_bmp = load_bitmap(LASERSPRITE, NULL);

	//Initialize laser
	for (n = 0; n<2; n++)
	{
		laser[n] = &thelaser[n];
		laser[n]->x = 0;
		laser[n]->y = 0;
		laser[n]->width = laser_bmp->w;
		laser[n]->height = laser_bmp->h;
	}
	if (explosion_bmp == NULL)
	{
		explosion_bmp = load_bitmap(EXPLOSIONSPRITE, NULL);
	}
}

///////////////
//Spawn Enemy//
///////////////
void spawnEnemy() {
	int n;
	enemyMaxSpd = 3 * enemySpdMulti; // Set enemy speed, enemySpdMulti used to increase enemy speed after each enemy is destroyed
	//Generate random values for enemy ship direction and starting position
	srand(time(NULL));
	int randx = rand() % (620 - 30 + 1) + 1;
	int randy = rand() % (430 - 30 + 1) + 1;
	int randdir = rand() % (8 - 1 + 1) + 1;

	//Configure enemy ship
	enemy[0] = &theenemy[0];
	enemy[0]->x = randx;
	enemy[0]->y = randy;
	enemy[0]->xspeed = 0;
	enemy[0]->dir = randdir;

	//Load first enemy bitmap
	enemy_bmp[0][0] = load_bitmap(ENEMYSPRITE, NULL);

	//Rotate image to generate all 8 directions
	for (n = 1; n<8; n++)
	{
		enemy_bmp[0][n] = create_bitmap(32, 32);
		clear_bitmap(enemy_bmp[0][n]);
		rotate_sprite(enemy_bmp[0][n], enemy_bmp[0][0],
			0, 0, itofix(n * 32));
	}

	//Load second enemy bitmap
	enemy_bmp[1][0] = load_bitmap(ENEMYSPRITE2, NULL);

	//Rotate image to generate all 8 directions
	for (n = 1; n<8; n++)
	{
		enemy_bmp[1][n] = create_bitmap(32, 32);
		clear_bitmap(enemy_bmp[1][n]);
		rotate_sprite(enemy_bmp[1][n], enemy_bmp[1][0],
			0, 0, itofix(n * 32));
	}
}

//////////////
//Fire Laser//
//////////////
void fireLaser(int num)
{
	// Load sound effects
	SAMPLE *lasersound;

	if (install_sound(DIGI_AUTODETECT, MIDI_NONE, "") != 0) {
		allegro_message("Error initializing sound system.");
	}
	lasersound = load_sample(LASERSOUND);
	if (!lasersound) {
		allegro_message("Error reading .wav file");
	}

	int x = player[num]->x;
	int y = player[num]->y;

	// Check if laser is ready to fire
	if (!laser[num]->alive)
	{
		laser[num]->alive = 1;
		play_sample(lasersound, 255, 128, 1000, FALSE); // Play laser sound effect

		// Fire laser in direction player ship is facing
		switch (player[num]->dir)
		{
		//N
		case 0:
			laser[num]->x = x - 2;
			laser[num]->y = y - 22;
			laser[num]->xspeed = 0;
			laser[num]->yspeed = -LASERSPEED;
			break;
		//NE
		case 1:
			laser[num]->x = x + 18;
			laser[num]->y = y - 18;
			laser[num]->xspeed = LASERSPEED;
			laser[num]->yspeed = -LASERSPEED;
			break;
		//E
		case 2:
			laser[num]->x = x + 22;
			laser[num]->y = y - 2;
			laser[num]->xspeed = LASERSPEED;
			laser[num]->yspeed = 0;
			break;
		//SE
		case 3:
			laser[num]->x = x + 18;
			laser[num]->y = y + 18;
			laser[num]->xspeed = LASERSPEED;
			laser[num]->yspeed = LASERSPEED;
			break;
		//S
		case 4:
			laser[num]->x = x - 2;
			laser[num]->y = y + 22;
			laser[num]->xspeed = 0;
			laser[num]->yspeed = LASERSPEED;
			break;
		//SW
		case 5:
			laser[num]->x = x - 18;
			laser[num]->y = y + 18;
			laser[num]->xspeed = -LASERSPEED;
			laser[num]->yspeed = LASERSPEED;
			break;
		//W
		case 6:
			laser[num]->x = x - 22;
			laser[num]->y = y - 2;
			laser[num]->xspeed = -LASERSPEED;
			laser[num]->yspeed = 0;
			break;
		//NW
		case 7:
			laser[num]->x = x - 18;
			laser[num]->y = y - 18;
			laser[num]->xspeed = -LASERSPEED;
			laser[num]->yspeed = -LASERSPEED;
			break;
		}
	}
}

////////////////
//Update Laser//
////////////////
void updateLaser(int num)
{
	int x, y, ex, ey;

	x = laser[0]->x;
	y = laser[0]->y;

	if (!laser[0]->alive) return;

	rectfill(screen, x, y, x + 10, y + 10, BLACK);

	// Move laser
	laser[0]->x += laser[0]->xspeed;
	laser[0]->y += laser[0]->yspeed;
	x = laser[0]->x;
	y = laser[0]->y;

	// Keep laser on screen
	if (x < 6 || x > SCREEN_W - 6 || y < 20 || y > SCREEN_H - 6)
	{
		laser[0]->alive = 0;
		return;
	}

// Hit detection	
	ex = enemy[0]->x;
	ey = enemy[0]->y;

	if (inside(x, y, ex-16, ey-16, ex + 16, ey + 16))
	{
		// If hit occurs, 'kill' the laser, explode enemy ship
		laser[0]->alive = 0;

		score++; // Increase score
		explode(1); // Blow up enemy ship and spawn a new one

	}
	else
	// If no hit then draw laser
	{
		draw_sprite(screen, laser_bmp, x, y);
	}
}

////////////////////////
//Explosion Controller//
////////////////////////
void explode(int num)
{
	// Load sound effects
	SAMPLE *explosion;

	if (install_sound(DIGI_AUTODETECT, MIDI_NONE, "") != 0) {
		allegro_message("Error initializing sound system.");
	}
	explosion = load_sample(EXPLOSIONSOUND);
	if (!explosion) {
		allegro_message("Error reading .wav file");
	}

	play_sample(explosion, 255, 128, 1000, FALSE);
	
	int n;

	int x = enemy[0]->x;
	int y = enemy[0]->y;
	enemyMaxSpd = 0;

	// If explode() is called because of an enemy kill, increase next enemy's speed
	if (num == 1) {
		enemySpdMulti++;
	}

	// Draw explosion animation
	for (n = 0; n < 5; n++)
	{
		rotate_sprite(screen, explosion_bmp,
			x + rand() % 10 - 20, y + rand() % 10 - 20,
			itofix(rand() % 255));
		rest(300);
	}
	circlefill(screen, x, y, 50, BLACK);

	spawnEnemy(); // Spawn new enemy
}