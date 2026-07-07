#pragma once

#include <SFML/Graphics.hpp>
#include "vars.h"

//Spike - same size as player
class tileTypes {
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual ~tileTypes() {}
};

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
//NOTE TO SELF when inputting the position, make sure to add 2.5 to each coordinate
class blackhole {
public:
    sf::CircleShape blackholeblock;
    blackhole(sf::Vector2f position) {
        blackholeblock.setRadius(7.5);
        blackholeblock.setFillColor(sf::Color::Black);
        blackholeblock.setPosition(position);
    }
    
    void drawblackhole (sf::RenderWindow& window){
        window.draw(blackholeblock);
    }
};
//Lava - kills upon entering
class lava {
public:
    sf::ConvexShape lavablock;
    lava(sf::Vector2f position) {
        lavablock.setPointCount(4);
        lavablock.setPoint(0, sf::Vector2f(0, 0));
        lavablock.setPoint(1, sf::Vector2f(20, 0));
        lavablock.setPoint(2, sf::Vector2f(20, 20));
        lavablock.setPoint(3, sf::Vector2f(0, 20));
        lavablock.setFillColor(sf::Color(255, 150, 20, 0.5));
        lavablock.setPosition(position);
    }

    void drawlava (sf::RenderWindow& window) {
        window.draw(lavablock);
    }
};
//Water - alters physics as if you're swimming
class water {
public:
    sf::ConvexShape waterblock;
    water(sf::Vector2f position) {
        waterblock.setPointCount(4);
        waterblock.setPoint(0, sf::Vector2f(0, 0));
        waterblock.setPoint(1, sf::Vector2f(20, 0));
        waterblock.setPoint(2, sf::Vector2f(20, 20));
        waterblock.setPoint(3, sf::Vector2f(0, 20));
        waterblock.setFillColor(sf::Color(20, 150, 255, 0.5));
        waterblock.setPosition(position);    
    }

    void drawwater (sf::RenderWindow& window) {
        window.draw(waterblock);
    }
};
//Zero gravity - you can no longer jump, you just drift through the air and up and down let you move in those directions
class zero_g {
    public:
    sf::ConvexShape zero_gblock;
    zero_g(sf::Vector2f position) {
        zero_gblock.setPointCount(4);
        zero_gblock.setPoint(0, sf::Vector2f(0, 0));
        zero_gblock.setPoint(1, sf::Vector2f(20, 0));
        zero_gblock.setPoint(2, sf::Vector2f(20, 20));
        zero_gblock.setPoint(3, sf::Vector2f(0, 20));
        zero_gblock.setFillColor(sf::Color(200, 200, 200, 0.5));
        zero_gblock.setPosition(position);
    }

    void drawzerog (sf::RenderWindow& window) {
        window.draw(zero_gblock);
    }
};
//Block - an immovable block, except for if you use the triangle powerup then you can push it 
class block {
public:
    sf::ConvexShape blockblock;
    //sf::Vector2<float> blockx; 
    //sf::Vector2<float> blocky;
    //might implement these later for push code
    block(sf::Vector2f position) {
        blockblock.setPointCount(4);
        blockblock.setPoint(0, sf::Vector2f(0, 0));
        blockblock.setPoint(1, sf::Vector2f(20, 0));
        blockblock.setPoint(2, sf::Vector2f(20, 20));
        blockblock.setPoint(3, sf::Vector2f(0, 20));
        blockblock.setFillColor(sf::Color(100, 100, 100));
        blockblock.setPosition(position);
    }
};
//Spring - catapults you into the air
class spring {
public:
    sf::ConvexShape springblock;
    spring(sf::Vector2f position) {
        springblock.setPointCount(9);
        springblock.setPoint(0, sf::Vector2f(0, 0));
        springblock.setPoint(1, sf::Vector2f(0, 3));
        springblock.setPoint(2, sf::Vector2f(8, 3));
        springblock.setPoint(3, sf::Vector2f(8, 6));
        springblock.setPoint(4, sf::Vector2f(0, 6));
        springblock.setPoint(5, sf::Vector2f(10, 10));
        springblock.setPoint(6, sf::Vector2f(20, 6));
        springblock.setPoint(7, sf::Vector2f(12, 6));
        springblock.setPoint(8, sf::Vector2f(12, 3));
        springblock.setPoint(9, sf::Vector2f(20, 3));
        springblock.setPoint(10, sf::Vector2f(20, 0));
    }
};