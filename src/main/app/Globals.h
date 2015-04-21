/* 
 * File:   Globals.h
 * Author: williampoynter
 *
 * Created on October 18, 2014, 3:37 PM
 */

#ifndef GLOBALS_H
#define	GLOBALS_H

namespace GBL {
	static const int WIDTH = 480;
	static const int HEIGHT = 640;
	static const int SCREEN_SPRITE_WIDTH = 32;

	static const int WIN_HEIGHT = 200;

	static const int TILE_WIDTH = 32;						// tile width & height
	static const int COLS = 13;								// tilemap dimensions
	static const int ROWS = 20;
	static const int NUMBER_LEVELS = 3;
	static const int MIN_NUMBER_WAVES = 4;					// player can move back, and can hence play more than this no. of waves
	static const int NUMBER_ENEMIES = COLS;
	static const float MIN_LEVEL_START_SPEED = 150.0f;		// units/sec (pixels in this simplistic mapping)
	static const float MAX_BULLET_SPEED = 450.0f;			// max speed is the same for each level
	static const float LEVEL_START_SPEED_INCREMENT = ((MAX_BULLET_SPEED - MIN_LEVEL_START_SPEED) / (NUMBER_LEVELS - 1));
};

#endif	/* GLOBALS_H */
