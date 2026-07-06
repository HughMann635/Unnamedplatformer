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
        playershape = sf::RectangleShape( sf::Vector2f(playerdim, playerdim));
	    playershape.setFillColor(sf::Color::Red);
	    playershape.setPosition(sf::Vector2f(100.f, 300.f));

        sf::Vector2f velocity = (sf::Vector2f(0.f, gravity));
        grounded = false;
    }

    void jump (const std::optional<sf::Event>&event) {
        if ( event->is<sf::Event::KeyPressed>() ) {
            auto& key = event->getIf<sf::Event::KeyPressed>()->code;
            if (key == sf::Keyboard::Key::Up || key == sf::Keyboard::Key::W) {
                if (grounded) {
                    velocity.y -= jumpforce;
                    grounded = false;
                }
            } 
        }
    }
    void updatepos (float deltatime) {
        if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed (sf::Keyboard::Key::D)) {
            velocity.x = movespeed;
		} else if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed (sf::Keyboard::Key::A)) {
            velocity.x = -movespeed;
		} else {
            velocity.x = 0.f; 
        }
        
        sf::Vector2f bound = playershape.getPosition();
        bound.x = std::clamp(bound.x, 0.f, (float)width-playerdim);
        playershape.setPosition(bound);

		if (!grounded) {
			velocity.y += gravity * deltatime;
		}

		playershape.move(velocity * deltatime);
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
