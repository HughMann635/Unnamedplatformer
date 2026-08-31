#pragma once

#include <SFML/Graphics.hpp>
#include <cstdlib> 
#include "tilemap.h"

struct parallaxlayer {
    float scrollx;
    float scrolly;
    std::unique_ptr<sf::Shape> element;
    sf::Vector2f pos;
};

class sky {
public:
    std::vector<sf::CircleShape> starlist;
    sf::CircleShape star;
    sf::RectangleShape skyblock;
    std::vector<parallaxlayer> bkgdelements;
    sky() {
        skyblock = sf::RectangleShape(sf::Vector2f(width, height));
        skyblock.setFillColor(sf::Color(0, 0, 35));
        skyblock.setPosition(sf::Vector2f(0, 0));

        auto horizonland = std::make_unique<sf::RectangleShape>(sf::Vector2f(width, height*0.3));
        horizonland -> setOrigin(sf::Vector2f(horizonland->getGlobalBounds().size.x/2, horizonland->getGlobalBounds().size.y/2));
        horizonland -> setPosition(sf::Vector2f(width/2, height*0.95));
        horizonland -> setFillColor(sf::Color(185, 145, 145));
        //bkgdelements.push_back({0, std::move(horizonland), sf::Vector2f(width/2, height*0.95)});

        auto moon = std::make_unique<sf::CircleShape>();
        moon -> setRadius(40);
        moon -> setFillColor(sf::Color(180, 180, 180));
        moon -> setPosition(sf::Vector2f(120, 120));
        bkgdelements.push_back({0.06, 0.01, std::move(moon), sf::Vector2f(120, 120)});

        auto spacerock = std::make_unique<sf::ConvexShape>();
        spacerock -> setPointCount(4);
        spacerock -> setPoint(0, sf::Vector2f(0, 0));
        spacerock -> setPoint(1, sf::Vector2f(30, 10));
        spacerock -> setPoint(2, sf::Vector2f(20, 29));
        spacerock -> setPoint(3, sf::Vector2f(10, 20));
        spacerock -> setFillColor(sf::Color(20, 20, 20));
        spacerock -> setPosition(sf::Vector2f(440, 40));
        bkgdelements.push_back({0.1, 0.02, std::move(spacerock), sf::Vector2f(440, 40)});
    }
    void makestars (int stars) {
        for (int i = 0; i < stars; i++) {
            float star_radius = std::rand() % 3;
            star = sf::CircleShape(star_radius);

            float starx = std::rand() % width*1.2;
            float stary = std::rand() % height*1.2;
            star.setPosition(sf::Vector2f(starx, stary));
            
            int starbrightness = 134 + std::rand() % 122;
            star.setFillColor(sf::Color(starbrightness, starbrightness, starbrightness));

            starlist.push_back(star);
        };
    }
    void drawstars (sf::RenderWindow& window, sf::Vector2f center) {
        for (int i = 0; i < std::size(starlist); i++) {
            sf::Transform transvector;
            transvector.translate(sf::Vector2f(-center.x*0.07f, -center.y*0.03f));
            window.draw(starlist[i], transvector);
        }
    }
    void drawsky (sf::RenderWindow& window) {
        window.draw(skyblock);
    }
    void drawbkgd (sf::RenderWindow& window, sf::Vector2f center) {
        for (auto& pos: bkgdelements) {
            sf::Transform transvector; 
            transvector.translate(sf::Vector2f(-center.x*pos.scrollx, -center.x*pos.scrolly));
            window.draw(*pos.element, transvector);
        }
    }
};