#include "SFML/Graphics.hpp"
#include <algorithm>
#include "vars.h"
#include "scenes.h"
#include "players.h"

#include "tilesettings.h"


square::square() {
    playershape = sf::RectangleShape(sf::Vector2f(playerdim, playerdim));
    playershape.setFillColor(sf::Color::Red);
    
    velocity = (sf::Vector2f(0.f, gravity));
    grounded = false;
}

sf::Shape& square::shape() {
    return playershape;
}

void square::jump (float deltatime) {
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

void square::updatepos (float deltatime, tilemap& map) {
    if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed (sf::Keyboard::Key::D)) {
        if (velocity.x > movespeed) velocity.x -= circleaccel*0.7;
        else velocity.x = movespeed;
    } else if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed (sf::Keyboard::Key::A)) {
        if (velocity.x < -movespeed) velocity.x += circleaccel*0.7;
        else velocity.x = -movespeed;
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

void square::drawscreen (sf::RenderWindow& window)  {
    window.draw(playershape);
}

circle::circle() {
    playershape = sf::CircleShape(playerdim/2);
    playershape.setFillColor(sf::Color(0, 255, 255));

    velocity = (sf::Vector2f(0.f, gravity));
    grounded = false;
}

sf::Shape& circle::shape()  {
    return playershape;
}

void circle::jump (float deltatime)  {
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

void circle::updatepos (float deltatime, tilemap& map)  {
    if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed (sf::Keyboard::Key::D)) {
        if (velocity.x <= circlemax && !zerogactive) velocity.x += circleaccel;
        else if (zerogactive) velocity.x = movespeed;
    } else if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed (sf::Keyboard::Key::A)) {
        if (velocity.x >= -circlemax && !zerogactive) velocity.x += -circleaccel;
        else if (zerogactive) velocity.x = -movespeed;
    } else if (swimming || zerogactive) {
        velocity.x *= 0.8; 
    } else {
        if (velocity.x > 0) velocity.x -= circleaccel*0.7;
        else if (velocity.x < 0) velocity.x += circleaccel*0.7;
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

void circle::drawscreen (sf::RenderWindow& window)  {
    window.draw(playershape);
}

triangle::triangle() {
    playershape.setPointCount(3);
    playershape.setPoint(0, sf::Vector2f(0, 17.3));
    playershape.setPoint(1, sf::Vector2f(10, 0));
    playershape.setPoint(2, sf::Vector2f(20, 17.3));
    playershape.setFillColor(sf::Color(0, 255, 0));

    velocity = (sf::Vector2f(0.f, gravity));
    grounded = false;
}

sf::Shape& triangle::shape()  {
    return playershape;
}

void triangle::jump (float deltatime)  {
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

void triangle::updatepos (float deltatime, tilemap& map)  {
    if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed (sf::Keyboard::Key::D)) {
        if (velocity.x > movespeed) velocity.x -= circleaccel*0.7;
        else velocity.x = movespeed;
    } else if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed (sf::Keyboard::Key::A)) {
        if (velocity.x < -movespeed) velocity.x += circleaccel*0.7;
        else velocity.x = -movespeed;
    } else {
        zerogactive || swimming ? velocity.x *= 0.8 : velocity.x *= 0.f; 
    }

    if (tp_timer.getElapsedTime().asSeconds() >= 3.f) {
        if ((sf::Keyboard::isKeyPressed (sf::Keyboard::Key::LShift) || sf::Keyboard::isKeyPressed (sf::Keyboard::Key::RShift))) {
            if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed (sf::Keyboard::Key::D)) {
                if (!map.predictCollision(sf::FloatRect(sf::Vector2f(shape().getPosition().x+40, shape().getPosition().y), sf::Vector2f(20, 17.3)))) {
                    playershape.setPosition(sf::Vector2f(playershape.getPosition().x + 40, playershape.getPosition().y));
                    velocity = sf::Vector2f(0, 0);
                    tp_timer.restart();
                }
            } else if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed (sf::Keyboard::Key::A)) {
                if (!map.predictCollision(sf::FloatRect(sf::Vector2f(shape().getPosition().x-40, shape().getPosition().y), sf::Vector2f(20, 17.3)))) {
                    playershape.setPosition(sf::Vector2f(playershape.getPosition().x - 40, playershape.getPosition().y));
                    velocity = sf::Vector2f(0, 0);
                    tp_timer.restart();
                }
            } else if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed (sf::Keyboard::Key::W)) {
                if (!map.predictCollision(sf::FloatRect(sf::Vector2f(shape().getPosition().x, shape().getPosition().y-40), sf::Vector2f(20, 17.3)))) {                        
                    playershape.setPosition(sf::Vector2f(playershape.getPosition().x, playershape.getPosition().y - 40));
                    velocity = sf::Vector2f(0, 0);
                    tp_timer.restart();
                }
            } else if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed (sf::Keyboard::Key::S)) {
                if (!map.predictCollision(sf::FloatRect(sf::Vector2f(shape().getPosition().x, shape().getPosition().y-40), sf::Vector2f(20, 17.3)))) {
                    playershape.setPosition(sf::Vector2f(playershape.getPosition().x, playershape.getPosition().y + 40));
                    velocity = sf::Vector2f(0, 0);
                    tp_timer.restart();
                }
            }
        }
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

void triangle::drawscreen (sf::RenderWindow& window)  {
    window.draw(playershape);
}