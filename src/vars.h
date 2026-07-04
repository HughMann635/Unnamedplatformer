#pragma once
#include <string>

//window settings
const int width = 1280;
const int height = 720;
std::string title = "Shape Game";
const int camwidth = 1280;
const int camheight = 720;

//Player and physics settings
const float playerdim = 50.f; 

float gravity = 1000.f;
float jumpforce = 450.f;
float movespeed = 230.f;

//Circle can accelerate up to a speed of 240 or so
float circleaccel = 30.f;
