#pragma once
#include <SFML/System.hpp>
#include <map>
#include <string>
#include <iomanip>
#include <sstream>

//Window settings
const int width = 1280;
const int height = 720;
inline std::string title = "Worlds of Blockman";
const int camwidth = 960;
const int camheight = 540;
const int stars = 700;
const int planets = 25;
inline int volumelevel = 10; //0-20 
inline int deathcount = 0;
inline bool esckeyheld = false;
inline bool mouseheld = false;
inline bool running = true;
inline bool restart = false;
inline bool newlevel = false;
inline bool swapped = false;
inline bool gamestart = false;
inline bool menuenter = false;
inline bool handbookenter = false;
inline bool autohover = false;
inline bool restarted = false;
inline int pbs[30] = {0};
inline sf::Clock leveltimer;

//States stuff
enum class State {
    mainmenu,
    playing,
    pause,
    levelselect,
    credits,
    handbook,
    settings
};

inline State state = State::mainmenu;
inline State targetstate = State::mainmenu;

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

enum class Action {
    right,
    left,
    jump,
    down,
    restart,
    goback,
    special1,
    special2,
    switch1,
    switch2,
    switch3,
    switch4,
    switch5
};

inline std::map<Action, sf::Keyboard::Key> keybinds = {
    {Action::right, sf::Keyboard::Key::Right},
    {Action::left, sf::Keyboard::Key::Left},
    {Action::jump, sf::Keyboard::Key::Up},
    {Action::down, sf::Keyboard::Key::Down},
    {Action::restart, sf::Keyboard::Key::R},
    {Action::goback, sf::Keyboard::Key::Escape},
    {Action::special1, sf::Keyboard::Key::LShift},
    {Action::special2, sf::Keyboard::Key::RShift},
    {Action::switch1, sf::Keyboard::Key::Num1},
    {Action::switch2, sf::Keyboard::Key::Num2},
    {Action::switch3, sf::Keyboard::Key::Num3},
    {Action::switch4, sf::Keyboard::Key::Num4},
    {Action::switch5, sf::Keyboard::Key::Num5},
};

inline bool keypressed (Action action) {
    if (sf::Keyboard::isKeyPressed(keybinds[action])) return true;
    else return false;
}

inline std::string maketime (int ms) {
    if (ms == 0) return "--:--.---";
    int mins = (ms/1000) / 60;
    int secs = (ms/1000) % 60;
    int millisecs = ms % 1000;

    std::ostringstream timestring;
    timestring << std::setfill('0') << std::setw(2) << mins << ':' << std::setw(2) << secs << '.' << std::setw(2) << millisecs;
    return timestring.str();
}

inline bool swimming = false;
inline bool zerogactive = false;
inline bool inblackhole = false; 
inline float circleaccel = 8.f;
inline float circlemax = 500.f;
inline float pushspeed = 115.f;
inline int jumpcount = 2;
inline bool tped = false;
inline sf::Clock tp_timer;
inline sf::Clock jump_timer;
inline int triangleshade = 255;
inline bool wallhuggingleft = false;
inline bool wallhuggingright = false;
inline bool walljumped = false;
inline bool walljumpcancel = false;
inline bool jumpkeyheld = false;
inline bool landed = false;
inline bool obstacleright = false;
inline bool obstacleleft = false;
inline bool obstacletop = false;
inline bool obstaclebelow = false;

//Game settings
inline bool switched = false;
inline int levelnum = 0;
inline int setnum = 0;
inline bool circlelocked = true;
inline bool trianglelocked = true;
inline bool octagonlocked = true;
inline bool hexagonlocked = true;
inline int coins[30] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
inline int completed[30] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
inline int unlocked[31] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};