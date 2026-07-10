#pragma once

#include <SFML/Graphics.hpp>
#include "vars.h"

class tileTypes {
public:
    virtual void draw (sf::RenderWindow& window) {}
    virtual sf::FloatRect collide() = 0;
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
        ground_block.setPosition(sf::Vector2f(position));
    }    

    void draw (sf::RenderWindow& window) override {
        window.draw(ground_block);
    }

    sf::FloatRect collide() override {
        return ground_block.getGlobalBounds();
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

    sf::FloatRect collide() override {
        return spikeblock.getGlobalBounds();
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

    sf::FloatRect collide() override {
        return sf::FloatRect(twospikes[0].getPosition(), sf::Vector2f(20.f, 10.f));
    }
};

//Black circle with particles orbiting it 
//NOTE TO SELF when inputting the position, make sure to add 2.5 to each coordinate
class blackhole : public tileTypes {
public:
    sf::CircleShape blackholeblock;
    blackhole(sf::Vector2f position) {
        blackholeblock.setRadius(7.5);
        blackholeblock.setFillColor(sf::Color::Black);
        blackholeblock.setPosition(position);
    }
    
    void draw (sf::RenderWindow& window) override {
        window.draw(blackholeblock);
    }

    sf::FloatRect collide() override {
        return blackholeblock.getGlobalBounds();
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

    sf::FloatRect collide() override {
        return lavablock.getGlobalBounds();
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

    sf::FloatRect collide() override {
        return waterblock.getGlobalBounds();
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

    sf::FloatRect collide() override {
        return zero_gblock.getGlobalBounds();
    }
};

class block : public tileTypes, public entity {
public:
    sf::ConvexShape blockblock;
    block(sf::Vector2f position) {
        blockblock.setPointCount(4);
        blockblock.setPoint(0, sf::Vector2f(0, 0));
        blockblock.setPoint(1, sf::Vector2f(20, 0));
        blockblock.setPoint(2, sf::Vector2f(20, 20));
        blockblock.setPoint(3, sf::Vector2f(0, 20));
        blockblock.setFillColor(sf::Color(100, 100, 100));
        blockblock.setPosition(position);

        velocity = sf::Vector2f(0.f, 0.f);
        grounded = false;
    }

    sf::Shape& shape() override {
        return blockblock;
    }

    sf::FloatRect collide() override {
        return blockblock.getGlobalBounds();
    }

    void movetile (float deltatime) override {
        velocity.y += 1800.f * deltatime;
        velocity.x += 0;
        blockblock.move(velocity * deltatime);
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

    sf::FloatRect collide() override {
        return springblock.getGlobalBounds();
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

    sf::FloatRect collide() override {
        return finishblock.getGlobalBounds();
    }
};