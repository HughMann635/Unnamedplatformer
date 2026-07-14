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
float movespeed = 260.f;

bool swimming = false;
bool zerogactive = false;

float circleaccel = 8.f;
float circlemax = 320.f;
//Triangle moves at a normal speed but when pushing an object, it slows down and pushes the object at the same speed
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
