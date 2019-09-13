/*
COMP 369 Assignment 2 - Space Game
spacegame.h
@author: Chris Kidney
		 Student ID: 3251456
@date: Oct 16th, 2018
*/
#pragma once
#ifndef _SPACEGAME_H
#define _SPACEGAME_H

#include <iostream>
#include <fstream>
#include <string>
#include <allegro.h>

extern int gameState;

extern int score;
extern int life;

extern int enemyMaxSpd;
extern int enemySpdMulti;


// Constants
#define MODE GFX_AUTODETECT_WINDOWED
#define WIDTH 640
#define HEIGHT 480
#define COLORDEPTH 32
#define MAINMENU "mainmenu.bmp"
#define HELPMENU "helpmenu.bmp"
#define GAMEPLAY "gameplay.bmp"
#define GAMEOVER "gameover.bmp"
#define PLAYERSPRITE "player01.bmp"
#define PLAYERSPRITE2 "player02.bmp"
#define ENEMYSPRITE "enemy01.bmp"
#define ENEMYSPRITE2 "enemy02.bmp"
#define EXPLOSIONSPRITE "explosion.bmp"
#define LASERSPRITE "laser.bmp"
#define BACKGROUND "background.mid"
#define LASERSOUND "laser.wav"
#define THRUSTERSOUND "thrusters_loop.wav"
#define EXPLOSIONSOUND "explosion.wav"
#define HOVER "hover.wav"
#define CLICK "click.wav"
#define MAXSPEED 4
#define LASERSPEED 10
#define BLACK makecol(0,0,0)
#define WHITE makecol(255,255,255)
#define YELLOW makecol(255,255,100)


// Sprite struct
typedef struct SPRITE {
	int dir, alive;
	int x, y;
	int width, height;
	int xspeed, yspeed;
	int xdelay, ydelay;
	int xcount, ycount;
	int curframe, maxframe, animdir;
	int framecount, framedelay;
}SPRITE;


// Function Prototypes
void mainMenu();
void helpMenu();
void gameplayScreen();
void musicControl();
void setup();
void spawnEnemy();
void getInput();
void scoreDisplay();
void lifeDisplay();
void explode(int num);
void fireLaser(int num);
void updateLaser(int num);
void moveShip(int num);
void moveEnemy(int num);
void gameoverScreen();
void drawShip(int num);
void drawEnemy(int num);
void eraseEnemy(int num);
void eraseShip(int num);
int mousePos(int x1, int y1, int x2, int y2);

#endif