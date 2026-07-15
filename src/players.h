#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>
#include "vars.h"
#include "scenes.h"

class tilemap;

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
    virtual void updatepos (float deltatime, tilemap& map) = 0;
    virtual void drawscreen (sf::RenderWindow& window) = 0;
    virtual ~player() = default;
};

class square: public player {
public:
    sf::RectangleShape playershape;

    square();
    sf::Shape& shape() override;
    void jump (float deltatime) override;
    void updatepos (float deltatime, tilemap& map) override;
    void drawscreen (sf::RenderWindow& window) override;
};

class circle : public player {
public:
    sf::CircleShape playershape;

    circle();
    sf::Shape& shape() override;
    void jump (float deltatime) override;
    void updatepos (float deltatime, tilemap& map) override;
    void drawscreen (sf::RenderWindow& window) override;
};

class triangle : public player {
public:
    sf::ConvexShape playershape;

    triangle();
    sf::Shape& shape() override;
    void jump (float deltatime) override;
    void updatepos (float deltatime, tilemap& map) override;
    void drawscreen (sf::RenderWindow& window) override;

};

class hexagon : public player {
    sf::ConvexShape playershape;

    hexagon();
    sf::Shape& shape() override;
    void jump (float deltatime) override;
    void updatepos (float deltatime, tilemap& map) override;
    void drawscreen (sf::RenderWindow& window) override;
};

class octagon : public player {
    sf::ConvexShape playershape;

    octagon();
    sf::Shape& shape() override;
    void jump (float deltatime) override;
    void updatepos (float deltatime, tilemap& map) override;
    void drawscreen (sf::RenderWindow& window) override;
};