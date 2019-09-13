/*
COMP 369 Assignment 2 - Space Game
gameplay.cpp
@author: Chris Kidney
Student ID: 3251456
@date: Oct 16th, 2018
Class Description: Contains routines for displaying gameplay screen, and contains main gameplay loop
*/
#include "spacegame.h"

///////////////////
//Gameplay Screen//
///////////////////
void gameplayScreen(){
	// Set up Bitmap
	char *filename = GAMEPLAY;
	BITMAP *image;
	int ret;
	set_color_depth(COLORDEPTH);
	ret = set_gfx_mode(MODE, WIDTH, HEIGHT, 0, 0);
	if (ret != 0) {
		allegro_message(allegro_error);
	}

	// Load image
	image = load_bitmap(filename, NULL);
	if (!image) {
		set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
		allegro_message("Error loading %s", filename);
	}

	// Draw background image
	blit(image, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	destroy_bitmap(image);

	// Main Gameplay loop
	while (!key[KEY_ESC]) {

		eraseShip(0);
		eraseEnemy(0);

		moveShip(0);
		moveEnemy(0);

		drawShip(0);
		drawEnemy(0);
		
		updateLaser(0);

		scoreDisplay();
		lifeDisplay();


		if (keypressed()) {
			getInput();
		}

		rest(30);

		if (life < 0) {
			gameState = 4;
		}

		if (key[KEY_BACKSPACE] ) {
			gameState = 1;
			break;
		}
		else if (gameState != 2) {
			break;
		}

	}
}