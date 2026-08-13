#pragma once
#include <SFML/System.hpp>
#include <string>

//Window settings
const int width = 1280;
const int height = 720;
inline std::string title = "Shape Game";
const int camwidth = 960;
const int camheight = 540;
const int stars = 1000;
inline bool running = true;
inline bool restart = false;
inline bool newlevel = false;
inline bool swapped = false;

//Debug stuff
inline bool enterkeyheld = false;
inline bool draw = false;

//Player and physics settings
const float playerdim = 20.f; //Also the dimensions of every tile in the game 
inline float gravity = 1800.f;
inline float jumpforce = 600.f;
inline float movespeed = 230.f;
inline float nearestedge = 90.f;
inline bool blockonhead = false;
inline bool tipping_right = false; 
inline bool tipping_left = false;
inline sf::Vector2f edge = sf::Vector2f(0, 0);

inline bool swimming = false;
inline bool zerogactive = false;

inline float circleaccel = 8.f;
inline float circlemax = 500.f;
inline float pushspeed = 115.f;
inline int jumpcount = 2;
inline sf::Clock tp_timer;
inline sf::Clock jump_timer;
inline bool wallhuggingleft = false;
inline bool wallhuggingright = false;
inline bool walljumped = false;
inline bool walljumpcancel = false;
inline bool jumpkeyheld = false;
inline bool landed = false;

//Game settings
inline int levelnum = 3;
inline int setnum = 2;
inline bool circlelocked = true;
inline bool trianglelocked = true;
inline bool octagonlocked = true;
inline bool hexagonlocked = true;
inline bool squareactive = true;
inline bool circleactive = false;
inline bool triangleactive = false;
inline bool octagonactive = false;
inline bool hexagonactive = false;