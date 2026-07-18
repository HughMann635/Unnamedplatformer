#pragma once
#include <SFML/System.hpp>
#include <string>

//window settings
const int width = 1280;
const int height = 720;
inline std::string title = "Shape Game";
const int camwidth = 960;
const int camheight = 540;
const int stars = 700;
inline bool running = true;
inline bool restart = false;
inline bool newlevel = false;
inline bool enterkeyheld = false;

//Player and physics settings
//This is also the dimension of all tiles in the game
const float playerdim = 20.f; 

inline float gravity = 1800.f;
inline float jumpforce = 600.f;
inline float movespeed = 230.f;

inline bool swimming = false;
inline bool zerogactive = false;

inline float circleaccel = 8.f;
inline float circlemax = 400.f;
//Triangle was initially gonna be the only character that could push blocks; this is now the push speed for any block
//Keeping the name for old times sake :')
inline float trianglepushspeed = 115.f;
inline int jumpcount = 2;
inline sf::Clock tp_timer;
inline sf::Clock jump_timer;
inline bool wallhuggingleft = false;
inline bool wallhuggingright = false;
inline bool walljumpcancel = false;
inline bool jumpkeyheld = false;

//Game settings
inline int levelnum = 0;
inline int setnum = 0;
inline bool circlelocked = true;
inline bool trianglelocked = true;
inline bool octagonlocked = true;
inline bool hexagonlocked = true;
inline bool squareactive = true;
inline bool circleactive = false;
inline bool triangleactive = false;
inline bool octagonactive = false;
inline bool hexagonactive = false;
