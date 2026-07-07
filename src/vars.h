#pragma once
#include <string>

//window settings
const int width = 1280;
const int height = 720;
std::string title = "Shape Game";
const int camwidth = 960;
const int camheight = 540;
const int stars = 700; //700 stars in the background, of varying sizes

//Player and physics settings
//This is also the dimension of all tiles in the game
const float playerdim = 20.f; 

float gravity = 1800.f;
float jumpforce = 600.f;
float movespeed = 260.f;

//Circle can accelerate up to a speed of 300 or so
float circleaccel = 30.f;
float circlemax = 300.f;
//Triangle moves at a normal speed but when pushing an object, it slows down and pushes the object at the same speed
float trianglepushspeed = 115.f;

//Game settings
bool circlelocked = true;
bool trianglelocked = true;
bool octagonlocked = true;
bool hexagonlocked = true;
