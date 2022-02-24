#ifndef CONFIG_H
#define CONFIG_H

#include <QtGlobal>

// Play area bounds
const int screenWidth = 900;
const int screenHeight = 900;

const int playerheight = 80;        // Player dimensions
const int playerwidth = 80;

const int crumbsheight = 30;        // Obstacle dimensions
const int crumbswidth = 30;

const int flyframes = 24;
const int frogframes = 30;          // Time interval between frames in milliseconds

const int player_dx_frog = 2;
const int player_dy_frog = 2;

const int player_dx_fly = 5;
const int player_dy_fly = 5;

#endif // CONFIG_H
