#pragma once
#include <string>

//window settings
const int width = 1280;
const int height = 720;
std::string title = "Shape Game";
const int camwidth = 1280;
const int camheight = 720;

//Player and physics settings - for now just contains stuff for a square
const float playerdim = 50.f; 

float gravity = 300.f;
float jumpforce = 200.f;
float speed = 150.f;