#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>
#include "vars.h"
#include "scenes.h"

//In the future, will make separate classes for each playable powerup

class player {
public:
    sf::RectangleShape playershape;
	sf::Vector2f velocity;
    bool grounded;

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
            }
            if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed (sf::Keyboard::Key::W)) {
                velocity.y = -125.f;
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
                velocity.y *= 0.983;
            }
        } 

        if (swimming) {
            gravity = 250.f; 
        } else if (zerogactive) {
            gravity = 0.f;
        } else if (!swimming && !zerogactive) { 
            gravity = 1800.f; 
        }

        if (!grounded) {
			velocity.y += gravity * deltatime;
		}

		playershape.move(velocity * deltatime);

        sf::Vector2f bound = playershape.getPosition();
        bound.x = std::clamp(bound.x, 0.f, (float)width-playerdim);
        playershape.setPosition(bound);
    }

    void checkground (float groundlevel) {
        float playerlevel = playershape.getPosition().y+playerdim;

        if (playerlevel >= groundlevel) {
            playershape.setPosition(sf::Vector2f(playershape.getPosition().x, groundlevel-playerdim));
            grounded = true;
            velocity.y = 0.f;
        } else {
            grounded = false;
        }
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