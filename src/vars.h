#pragma once
#include <string>

//window settings
const int width = 1280;
const int height = 720;
std::string title = "Shape Game";
const int camwidth = 960;
const int camheight = 540;
const int stars = 700;
bool running = true;
bool restart = false;

//Player and physics settings
//This is also the dimension of all tiles in the game
const float playerdim = 20.f; 

float gravity = 1800.f;
float jumpforce = 600.f;
float movespeed = 230.f;

bool swimming = false;
bool zerogactive = false;

float circleaccel = 8.f;
float circlemax = 400.f;
//Triangle was initially gonna be the only character that could push blocks; this is now the push speed for any block
//Keeping the name for old times sake :')
float trianglepushspeed = 115.f;

//Game settings
bool circlelocked = true;
bool trianglelocked = true;
bool octagonlocked = true;
bool hexagonlocked = true;
bool squareactive = true;
bool circleactive = false;
bool triangleactive = false;
bool octagonactive = false;
bool hexagonactive = false;
