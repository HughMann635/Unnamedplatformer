#pragma once

#include <SFML/Graphics.hpp>
#include <cstdlib> 
#include "tilemap.h"

class sky {
public:
    std::vector<sf::CircleShape> starlist;
    sf::CircleShape star;
    sf::RectangleShape skyblock;
    std::vector<std::unique_ptr<sf::Shape>> bkgdelements;
    sky() {
        skyblock = sf::RectangleShape(sf::Vector2f(width, height));
        skyblock.setFillColor(sf::Color(0, 0, 35));
        skyblock.setPosition(sf::Vector2f(0, 0));

        auto horizonland = std::make_unique<sf::RectangleShape>(sf::Vector2f(width, height*0.3));
        horizonland -> setPosition(sf::Vector2f(0, height*0.6));
        horizonland -> setFillColor(sf::Color(35, 15, 15));
        bkgdelements.push_back(std::move(horizonland));

        auto horizonline = std::make_unique<sf::RectangleShape>(sf::Vector2f(width, 60));
        horizonline -> setPosition(sf::Vector2f(0, height*0.9));
        horizonline -> setFillColor(sf::Color(0, 0, 0));
        bkgdelements.push_back(std::move(horizonline));

        auto mountain = std::make_unique<sf::ConvexShape>();
        mountain -> setPointCount(3);
        mountain -> setPoint(0, sf::Vector2f(20, height*0.7));
        mountain -> setPoint(1, sf::Vector2f(236, height*0.4));
        mountain -> setPoint(2, sf::Vector2f(452, height*0.7));
        mountain -> setFillColor(sf::Color(150, 150, 20));
        bkgdelements.push_back(std::move(mountain));

        auto moon = std::make_unique<sf::CircleShape>();
        moon -> setRadius(40);
        moon -> setFillColor(sf::Color(180, 180, 180));
        moon -> setPosition(sf::Vector2f(120, 120));
        bkgdelements.push_back(std::move(moon));
    }
    void makestars (int stars) {
        for (int i = 0; i < stars; i++) {
            float star_radius = std::rand() % 3;
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
    void drawsky (sf::RenderWindow& window) {
        window.draw(skyblock);
    }
    void drawbkgd (sf::RenderWindow& window) {
        for (auto& pos: bkgdelements) {
            window.draw(*pos);
        }    
    }
};