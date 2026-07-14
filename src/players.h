#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>
#include "vars.h"
#include "scenes.h"

//I had to make a master class for every object affected by physics so I didn't completely lose my mind
class entity {
public: 
    sf::Vector2f velocity;
    bool grounded;
    virtual sf::Shape& shape() = 0;

    void moveobject (float deltatime, float gravity) {
        velocity.y += gravity * deltatime;
        shape().move(velocity * deltatime);
    }

    virtual ~entity() = default;
};

class player : public entity{
public:
    virtual void jump (float deltatime) = 0;
    virtual void updatepos (float deltatime) = 0;
    virtual void drawscreen (sf::RenderWindow& window) = 0;
    virtual ~player() = default;
};

class square: public player {
public:
    sf::RectangleShape playershape;

    square() {
        playershape = sf::RectangleShape(sf::Vector2f(playerdim, playerdim));
	    playershape.setFillColor(sf::Color::Red);

        sf::Vector2f velocity = (sf::Vector2f(0.f, gravity));
        grounded = false;
    }

    sf::Shape& shape() override {
        return playershape;
    }

    void jump (float deltatime) override {
        if (sf::Keyboard::isKeyPressed ( sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed (sf::Keyboard::Key::W)) {
            if (grounded && !swimming && !zerogactive) {
                velocity.y -= jumpforce;
                grounded = false;
            }
        }
        if (swimming) {
            if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed (sf::Keyboard::Key::S)) {
                velocity.y += 50.f;
                grounded = false;
            }
            if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed (sf::Keyboard::Key::W)) {
                velocity.y = -125.f;
                grounded = false;
            }
        } 
    }

    void updatepos (float deltatime) override {
        if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed (sf::Keyboard::Key::D)) {
            velocity.x = movespeed;
		} else if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed (sf::Keyboard::Key::A)) {
            velocity.x = -movespeed;
		} else {
            zerogactive || swimming ? velocity.x *= 0.8 : velocity.x *= 0.f; 
        }
        if (zerogactive) {
            if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed (sf::Keyboard::Key::S)) {
                velocity.y = 125.f;
            }
            else if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed (sf::Keyboard::Key::W)) {
                velocity.y = -125.f;
            }
            else {
                velocity.y *= 0.96;
            }
        } 

        if (swimming) {
            gravity = 250.f; 
        } else if (zerogactive) {
            gravity = 0.f;
        } else if (!swimming && !zerogactive) { 
            gravity = 1800.f;
        }

        moveobject(deltatime, gravity);

        sf::Vector2f bound = playershape.getPosition();
        bound.x = std::clamp(bound.x, 0.f, (float)width-playerdim);
        playershape.setPosition(bound);
        swimming = false;
        zerogactive = false;
    }

    void drawscreen (sf::RenderWindow& window) override {
        window.draw(playershape);
    }
};

class circle : public player {
public:
    sf::CircleShape playershape;

    circle() {
        playershape = sf::CircleShape(playerdim/2);
	    playershape.setFillColor(sf::Color(0, 255, 255));

        sf::Vector2f velocity = (sf::Vector2f(0.f, gravity));
        grounded = false;
    }

    sf::Shape& shape() override {
        return playershape;
    }

    void jump (float deltatime) override {
        if (sf::Keyboard::isKeyPressed ( sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed (sf::Keyboard::Key::W)) {
            if (grounded && !swimming && !zerogactive) {
                velocity.y -= jumpforce;
                grounded = false;
            }
        }
        if (swimming) {
            if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed (sf::Keyboard::Key::S)) {
                velocity.y += 50.f;
                grounded = false;
            }
            if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed (sf::Keyboard::Key::W)) {
                velocity.y = -125.f;
                grounded = false;
            }
        } 
    }

    void updatepos (float deltatime) override {
        if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed (sf::Keyboard::Key::D)) {
            if (velocity.x <= circlemax && !zerogactive) velocity.x += circleaccel;
            else if (zerogactive) velocity.x = movespeed;
		} else if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed (sf::Keyboard::Key::A)) {
            if (velocity.x >= -circlemax && !zerogactive) velocity.x += -circleaccel;
            else if (zerogactive) velocity.x = -movespeed;
		} else if (swimming || zerogactive) {
            velocity.x *= 0.94; 
        } else {
            if (velocity.x > 0) velocity.x -= circleaccel;
            else if (velocity.x < 0) velocity.x += circleaccel;
            else velocity.x = 0;
        }
        if (zerogactive) {
            if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed (sf::Keyboard::Key::S)) {
                velocity.y = 125.f;
            }
            else if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed (sf::Keyboard::Key::W)) {
                velocity.y = -125.f;
            }
            else {
                velocity.y *= 0.96;
            }
        } 

        if (swimming) {
            gravity = 250.f; 
        } else if (zerogactive) {
            gravity = 0.f;
        } else if (!swimming && !zerogactive) { 
            gravity = 1800.f;
        }

        moveobject(deltatime, gravity);

        sf::Vector2f bound = playershape.getPosition();
        bound.x = std::clamp(bound.x, 0.f, (float)width-playerdim);
        playershape.setPosition(bound);
        swimming = false;
        zerogactive = false;
    }

    void drawscreen (sf::RenderWindow& window) override {
        window.draw(playershape);
    }
};

class triangle : public player {

};

class hexagon : public player {

};

class octagon : public player {
    
};