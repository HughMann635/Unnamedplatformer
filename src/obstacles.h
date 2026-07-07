#pragma once

#include <SFML/Graphics.hpp>
#include "vars.h"

//Spike - same size as player
class spike {
public:
    sf::ConvexShape spikeblock;
    spike(sf::Vector2f position) {
        spikeblock.setPointCount(3);
        spikeblock.setPoint(0, sf::Vector2f(0, 0));
        spikeblock.setPoint(1, sf::Vector2f(10, 20));
        spikeblock.setPoint(2, sf::Vector2f(20, 0));
        spikeblock.setFillColor(sf::Color::Red);
        spikeblock.setPosition(position);
    }

    void drawspike (sf::RenderWindow& window) {
        window.draw(spikeblock);
    }
};

//Double spike - two small spikes placed beside each other
class doublespike {
public:
    sf::ConvexShape twospikeblock;
    doublespike(sf::Vector2f position) {
        twospikeblock.setPointCount(5);
        twospikeblock.setPoint(0, sf::Vector2f(0, 0));
        twospikeblock.setPoint(1, sf::Vector2f(5, 10));
        twospikeblock.setPoint(2, sf::Vector2f(10, 0));
        twospikeblock.setPoint(3, sf::Vector2f(15, 10));
        twospikeblock.setPoint(4, sf::Vector2f(20, 0));
        twospikeblock.setFillColor(sf::Color::Red);
        twospikeblock.setPosition(position);
    }

    void drawdoublespike (sf::RenderWindow& window) {
        window.draw(twospikeblock);
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