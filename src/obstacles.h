#pragma once

#include <SFML/Graphics.hpp>
#include "vars.h"

//Spike - same size as player
class spike {
public:
    sf::ConvexShape spikeblock;
    spike() {

    }
};

//Double spike - two small spikes placed beside each other
class doublespike {
public:
    sf::ConvexShape spikeblock;
    doublespike() {

    }
};

//Black hole - sucks you in when you get within 1 tile of the center
//Black circle with particles orbiting it 
class blackhole {
public:
    sf::CircleShape blackholeblock;
    blackhole() {

    }
};
//Lava - kills upon entering; reacts with water to become a walkable platform
class lava {
public:
    sf::RectangleShape lavablock;
    lava() {

    }
};
//Water - alters physics as if you're swimming; reacts with lava to become a walkable platform
class water {
public:
    sf::RectangleShape waterblock;
    water() {

    }
};
//Block - an immovable block, except for if you use the triangle powerup the  you can push it 
class block {
public:
    sf::RectangleShape blockblock;
    block() {

    }
};
//Spring - catapults you into the air
class spring {
public:
    sf::ConvexShape springblock; //I might not use a convexshape
    spring() {
        
    }
};