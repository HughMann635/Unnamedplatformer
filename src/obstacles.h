#pragma once

#include <SFML/Graphics.hpp>
#include "vars.h"

//Spike - same size as player
class spike {
public:
    sf::ConvexShape spikeblock;
    spike() {
        spikeblock.setPointCount(3);
    }

    void drawspike (sf::RenderWindow& window) {
        window.draw(spikeblock);
    }
};

//Double spike - two small spikes placed beside each other
class doublespike {
public:
    sf::ConvexShape twospikeblock;
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
//Lava - kills upon entering
class lava {
public:
    sf::RectangleShape lavablock;
    lava() {

    }
};
//Water - alters physics as if you're swimming
class water {
public:
    sf::RectangleShape waterblock;
    water() {

    }
};
//Zero gravity - you can no longer jump, you just drift through the air and up and down let you move in those directions
class zero_g {
    public:
    sf::RectangleShape zero_gblock;
    zero_g() {

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