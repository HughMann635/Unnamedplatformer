#pragma once

#include <SFML/Graphics.hpp>
#include <cstdlib> 
#include "tilemap.h"

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
class sky {
public:
    std::vector<sf::CircleShape> starlist;
    sf::CircleShape star;
    sky() {

    }
    void makestars (int stars) {
        for (int i = 0; i < stars; i++) {
            float star_radius = 5;
            star = sf::CircleShape(star_radius);

            float starx = std::rand() % width;
            float stary = std::rand() % height;
            star.setPosition(sf::Vector2f(starx, stary));
            
            int starbrightness = 134 + std::rand() % 122;
            star.setFillColor(sf::Color(starbrightness, starbrightness, starbrightness));

            starlist.push_back(star);
        };
    }
    void drawstars (sf::RenderWindow& window) {
        for (int i = 0; i < std::size(starlist); i++) {
            window.draw(starlist[i]);
        }
    }
};