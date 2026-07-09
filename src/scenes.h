#pragma once

#include <SFML/Graphics.hpp>
#include <cstdlib> 
#include "tilemap.h"

class sky {
public:
    std::vector<sf::CircleShape> starlist;
    sf::CircleShape star;
    sf::RectangleShape skyblock;
    sky() {
        skyblock = sf::RectangleShape(sf::Vector2f(width, height));
        skyblock.setFillColor(sf::Color(0, 0, 30));
        skyblock.setPosition(sf::Vector2f(0, 0));
    }
    void makestars (int stars) {
        for (int i = 0; i < stars; i++) {
            float star_radius = std::rand() % 3;
            star = sf::CircleShape(star_radius);

            float starx = std::rand() % width;
            float stary = (std::rand() % height) - 80;
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
    void drawsky (sf::RenderWindow& window) {
        window.draw(skyblock);
    }
};