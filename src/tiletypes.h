#pragma once

#include <SFML/Graphics.hpp>
#include "vars.h"

class tileTypes {
public:
    virtual void draw (sf::RenderWindow& window) {}
    virtual sf::Shape& collide() = 0;
    virtual void movetile (float deltatime) {} 
    virtual ~tileTypes() {}
};

class ground_ : public tileTypes {
public:
    sf::ConvexShape ground_block;
    ground_(sf::Vector2f position) {
        ground_block.setPointCount(4);
        ground_block.setPoint(0, sf::Vector2f(0, 0));
        ground_block.setPoint(1, sf::Vector2f(20, 0));
        ground_block.setPoint(2, sf::Vector2f(20, 20));
        ground_block.setPoint(3, sf::Vector2f(0, 20));
        ground_block.setFillColor(sf::Color(255, 200, 200));
        ground_block.setOutlineColor(sf::Color(215, 160, 160));
        ground_block.setOutlineThickness(-1.f);
        ground_block.setPosition(sf::Vector2f(position));
    }    

    void draw (sf::RenderWindow& window) override {
        window.draw(ground_block);
    }

    sf::Shape& collide() override {
        return ground_block;
    }
};

class spike : public tileTypes {
public:
    sf::ConvexShape spikeblock;
    spike(sf::Vector2f position) {
        spikeblock.setPointCount(3);
        spikeblock.setPoint(0, sf::Vector2f(0, 0));
        spikeblock.setPoint(1, sf::Vector2f(10, 20));
        spikeblock.setPoint(2, sf::Vector2f(20, 0));
        spikeblock.setFillColor(sf::Color::Red);
        spikeblock.setOutlineColor(sf::Color(150, 0, 0));
        spikeblock.setOutlineThickness(-2.f);
        spikeblock.setPosition(position);
    }

    void draw (sf::RenderWindow& window) override {
        window.draw(spikeblock);
    }

    sf::Shape& collide() override {
        return spikeblock;
    }

};

class doublespike : public tileTypes {
public:
    sf::ConvexShape twospikes[2];
    doublespike(sf::Vector2f position) {
        twospikes[0].setPointCount(3);
        twospikes[0].setPoint(0, sf::Vector2f(0, 0));
        twospikes[0].setPoint(1, sf::Vector2f(5, 10));
        twospikes[0].setPoint(2, sf::Vector2f(10, 0));
        
        twospikes[1].setPointCount(3);
        twospikes[1].setPoint(0, sf::Vector2f(10, 0));
        twospikes[1].setPoint(1, sf::Vector2f(15, 10));
        twospikes[1].setPoint(2, sf::Vector2f(20, 0));
        
        for (int i = 0; i < 2; i++) {
            twospikes[i].setFillColor(sf::Color::Red);
            twospikes[i].setOutlineColor(sf::Color(150, 0, 0));
            twospikes[i].setOutlineThickness(-1.f);
            twospikes[i].setPosition(position);
        }
    }

    void draw (sf::RenderWindow& window) override {
        window.draw(twospikes[0]);
        window.draw(twospikes[1]);
    }

    sf::Shape& collide() override {
        return twospikes[0], twospikes[1];
    }
};

//Black circle with particles orbiting it 
//NOTE TO SELF when inputting the position, make sure to add 2.5 to each coordinate
class blackhole : public tileTypes {
public:
    sf::CircleShape blackholeblock;
    blackhole(sf::Vector2f position) {
        blackholeblock.setRadius(15);
        blackholeblock.setFillColor(sf::Color::Black);
        blackholeblock.setPosition(position);
    }
    
    void draw (sf::RenderWindow& window) override {
        window.draw(blackholeblock);
    }

    sf::Shape& collide() override {
        return blackholeblock;
    } 

};
//Lava - kills upon entering
class lava : public tileTypes {
public:
    sf::ConvexShape lavablock;
    lava(sf::Vector2f position) {
        lavablock.setPointCount(4);
        lavablock.setPoint(0, sf::Vector2f(0, 0));
        lavablock.setPoint(1, sf::Vector2f(20, 0));
        lavablock.setPoint(2, sf::Vector2f(20, 20));
        lavablock.setPoint(3, sf::Vector2f(0, 20));
        lavablock.setFillColor(sf::Color(255, 150, 20, 200));
        lavablock.setPosition(position);
    }

    void draw (sf::RenderWindow& window) override {
        window.draw(lavablock);
    }

    sf::Shape& collide() override {
        return lavablock;
    }
};

class water : public tileTypes {
public:
    sf::ConvexShape waterblock;
    water(sf::Vector2f position) {
        waterblock.setPointCount(4);
        waterblock.setPoint(0, sf::Vector2f(0, 0));
        waterblock.setPoint(1, sf::Vector2f(20, 0));
        waterblock.setPoint(2, sf::Vector2f(20, 20));
        waterblock.setPoint(3, sf::Vector2f(0, 20));
        waterblock.setFillColor(sf::Color(20, 150, 255, 170));
        waterblock.setPosition(position);    
    }

    void draw (sf::RenderWindow& window) override {
        window.draw(waterblock);
    }

    sf::Shape& collide() override {
        return waterblock;
    }
};

class zero_g : public tileTypes {
    public:
    sf::ConvexShape zero_gblock;
    zero_g(sf::Vector2f position) {
        zero_gblock.setPointCount(4);
        zero_gblock.setPoint(0, sf::Vector2f(0, 0));
        zero_gblock.setPoint(1, sf::Vector2f(20, 0));
        zero_gblock.setPoint(2, sf::Vector2f(20, 20));
        zero_gblock.setPoint(3, sf::Vector2f(0, 20));
        zero_gblock.setFillColor(sf::Color(230, 230, 230, 170));
        zero_gblock.setPosition(position);
    }

    void draw (sf::RenderWindow& window) override {
        window.draw(zero_gblock);
    }

    sf::Shape& collide() override {
        return zero_gblock;
    }
};

class block : public tileTypes, public entity {
public:
    sf::ConvexShape blockblock;
    float blockgravity = 1800.f;
    block(sf::Vector2f position) {
        blockblock.setPointCount(4);
        blockblock.setPoint(0, sf::Vector2f(0, 0));
        blockblock.setPoint(1, sf::Vector2f(20, 0));
        blockblock.setPoint(2, sf::Vector2f(20, 20));
        blockblock.setPoint(3, sf::Vector2f(0, 20));
        blockblock.setFillColor(sf::Color(100, 100, 100));
        blockblock.setOutlineColor(sf::Color(75, 75, 75));
        blockblock.setOutlineThickness(-2);
        blockblock.setPosition(position);

        velocity = sf::Vector2f(0.f, 0.f);
        grounded = false;
    }

    sf::Shape& shape() override {
        return blockblock;
    }

    sf::Shape& collide() override {
        return blockblock;
    }

    void movetile (float deltatime) override {
        moveobject(deltatime, blockgravity);
        velocity.x *= 0.87;
    }

    void draw (sf::RenderWindow& window) override {
        window.draw(blockblock);
    }
};

class spring : public tileTypes {
public:
    sf::ConvexShape springblock;
    spring(sf::Vector2f position) {
        springblock.setPointCount(11);
        springblock.setPoint(0, sf::Vector2f(0, 20));
        springblock.setPoint(1, sf::Vector2f(0, 17));
        springblock.setPoint(2, sf::Vector2f(8, 17));
        springblock.setPoint(3, sf::Vector2f(8, 14));
        springblock.setPoint(4, sf::Vector2f(0, 14));
        springblock.setPoint(5, sf::Vector2f(10, 10));
        springblock.setPoint(6, sf::Vector2f(20, 14));
        springblock.setPoint(7, sf::Vector2f(12, 14));
        springblock.setPoint(8, sf::Vector2f(12, 17));
        springblock.setPoint(9, sf::Vector2f(20, 17));
        springblock.setPoint(10, sf::Vector2f(20, 20));
        springblock.setFillColor(sf::Color(200, 255, 255));
        springblock.setPosition(position);
    }

    void draw (sf::RenderWindow& window) override {
        window.draw(springblock);
    }

    sf::Shape& collide() override {
        return springblock;
    }
};

//the only way to justify the amount of time I spent on block-pushing physics
//if a block or the player is on the button, a door will open
class button : public tileTypes {
public:
    sf::ConvexShape buttonblock[3];
    int id;
    bool pressed = false;
    bool presscheck = false;
    button (sf::Vector2f position, int id_button = 0) : id(id_button) {
        buttonblock[0].setPointCount(4);
        buttonblock[0].setPoint(0, sf::Vector2f(10, 4));
        buttonblock[0].setPoint(1, sf::Vector2f(16, 10));
        buttonblock[0].setPoint(2, sf::Vector2f(10, 16));
        buttonblock[0].setPoint(3, sf::Vector2f(4, 10));
        buttonblock[0].setPosition(position);

        buttonblock[1].setPointCount(8);
        buttonblock[1].setPoint(0, sf::Vector2f(7, 4));
        buttonblock[1].setPoint(1, sf::Vector2f(13, 4));
        buttonblock[1].setPoint(2, sf::Vector2f(16, 7));
        buttonblock[1].setPoint(3, sf::Vector2f(16, 13));
        buttonblock[1].setPoint(4, sf::Vector2f(13, 16));
        buttonblock[1].setPoint(5, sf::Vector2f(7, 16));
        buttonblock[1].setPoint(6, sf::Vector2f(4, 13));
        buttonblock[1].setPoint(7, sf::Vector2f(4, 7));
        buttonblock[1].setPosition(position);
    }

    void draw (sf::RenderWindow& window) {
        if (pressed) {
            buttonblock[0].setFillColor(sf::Color(0, 210, 0));
            buttonblock[1].setFillColor(sf::Color(0, 150, 0));
        } else {
            buttonblock[0].setFillColor(sf::Color(200, 0, 0));
            buttonblock[1].setFillColor(sf::Color(95, 0, 0));
        }
        window.draw(buttonblock[1]);
        window.draw(buttonblock[0]);
    }

    sf::Shape& collide() override {
        return buttonblock[1];
    }
};

class door : public tileTypes {
public:
    sf::ConvexShape doorblock[4];
    int id;
    bool opened = false;
    door (sf::Vector2f position, int id_door = 0) : id(id_door) {
        doorblock[0].setPointCount(4);
        doorblock[0].setPoint(0, sf::Vector2f(0, 0));
        doorblock[0].setPoint(1, sf::Vector2f(20, 0));
        doorblock[0].setPoint(2, sf::Vector2f(20, 20));
        doorblock[0].setPoint(3, sf::Vector2f(0, 20));
        doorblock[0].setFillColor(sf::Color(60, 60, 70));
        
        doorblock[1].setPointCount(4);
        doorblock[1].setPoint(0, sf::Vector2f(0, 0));
        doorblock[1].setPoint(1, sf::Vector2f(10, 6));
        doorblock[1].setPoint(2, sf::Vector2f(10, 14));
        doorblock[1].setPoint(3, sf::Vector2f(0, 20));
        doorblock[1].setFillColor(sf::Color(70, 60, 80));
        
        doorblock[2].setPointCount(4);
        doorblock[2].setPoint(0, sf::Vector2f(20, 0));
        doorblock[2].setPoint(1, sf::Vector2f(10, 6));
        doorblock[2].setPoint(2, sf::Vector2f(10, 14));
        doorblock[2].setPoint(3, sf::Vector2f(20, 20));
        doorblock[2].setFillColor(sf::Color(70, 60, 80));

        doorblock[3].setPointCount(4);
        doorblock[3].setPoint(0, sf::Vector2f(0, 0));
        doorblock[3].setPoint(1, sf::Vector2f(0, 0));
        doorblock[3].setPoint(2, sf::Vector2f(0, 0));
        doorblock[3].setPoint(3, sf::Vector2f(0, 0));
        doorblock[3].setFillColor(sf::Color(70, 60, 80));

        for (int i = 0; i < 3; i++) {
            doorblock[i].setOutlineColor(sf::Color(25, 21, 30));
            doorblock[i].setOutlineThickness(-1);
            doorblock[i].setPosition(position);
        }
    }

    void draw (sf::RenderWindow& window) override {
        if (!opened) for (int i = 0; i < 3; i++) window.draw(doorblock[i]);
    }

    sf::Shape& collide() override {
        if (opened) {
            return doorblock[3];
        } else {
            return doorblock[0];
        }
    }
};

class finish : public tileTypes {
public:
    sf::ConvexShape finishblock;
    finish (sf::Vector2f position) {
        finishblock.setPointCount(4);
        finishblock.setPoint(0, sf::Vector2f(0, 0));
        finishblock.setPoint(1, sf::Vector2f(20, 0));
        finishblock.setPoint(2, sf::Vector2f(20, 20));
        finishblock.setPoint(3, sf::Vector2f(0, 20));
        finishblock.setFillColor(sf::Color(235, 240, 70, 200));
        finishblock.setPosition(position);
    }

    void draw (sf::RenderWindow& window) override {
        window.draw(finishblock);
    }

    sf::Shape& collide() override {
        return finishblock;
    }
};