#pragma once

#include <SFML/Graphics.hpp>
#include "vars.h"

class ground {
public:
    sf::RectangleShape groundblock;
    ground() {
        groundblock = sf::RectangleShape( sf::Vector2f(width, 100.f));
        groundblock.setFillColor(sf::Color(255,200,200));
        groundblock.setPosition(sf::Vector2f(0.f, height-100.f));
    }

    float getgroundlevel() {
        return groundblock.getPosition().y;
    }

    void drawscreen (sf::RenderWindow& window) {
        window.draw(groundblock);
    }
};