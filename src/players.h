#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>
#include "vars.h"
#include "scenes.h"

//In the future, will make separate classes for each playable powerup

//I had to make a master class for every object affected by physics so I didn't completely lose my mind
class entity {
public: 
    sf::Vector2f velocity;
    bool grounded;
    virtual sf::Shape& shape() = 0;

    void moveobject (float deltatime, float gravity) {
        
        if (!grounded) velocity.y += gravity * deltatime;
        if (velocity.y == 0) grounded = true;

        shape().move(velocity * deltatime);
    }

    virtual ~entity() = default;
};

class player : public entity{
public:
    sf::RectangleShape playershape;

    player() {
        playershape = sf::RectangleShape(sf::Vector2f(playerdim, playerdim));
	    playershape.setFillColor(sf::Color::Red);

        sf::Vector2f velocity = (sf::Vector2f(0.f, gravity));
        grounded = false;
    }

    void jump (float deltatime) {
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
    void updatepos (float deltatime) {
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

        velocity.y += gravity * deltatime;

        if (velocity.y == 0) grounded = true;

		playershape.move(velocity * deltatime);

        sf::Vector2f bound = playershape.getPosition();
        bound.x = std::clamp(bound.x, 0.f, (float)width-playerdim);
        playershape.setPosition(bound);
        swimming = false;
        zerogactive = false;
    }

    void drawscreen (sf::RenderWindow& window) {
        window.draw(playershape);
    }
};

class circle : public player {

};

class triangle : public player {

};

class hexagon : public player {

};

class octagon : public player {
    
};