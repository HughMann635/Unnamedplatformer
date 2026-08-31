#pragma once

#include <SFML/Graphics.hpp>
#include <cstdlib> 
#include "tilemap.h"


//PLANNING!!!

/*
- STARS - flashing
- COMETS - prodecurally generated?
- FLOATING ROCKS - they just drift
- PLANETS - static, ez
- A BLACK HOLE? - static, ez
- MOON - static, ez
---- volcano and horizonland, MAYBE.

STRUCTS FOR 5 GUARANTEEDS + ONE MOON
STARS: position, circleshape, brightness
COMETS: trail, pos, shape, cd
BLACK HOLES: pos | Maybe 1 or 2 on the screen.
FLOATING ROCKS: speed, shape,
PLANETS: color, circleshape, size, pos

UPDATE FUNCTION to update pos, brightness...of shapes
DRAW to draw everything, will do away w/ stars and whatnot.

*/


struct parallaxlayer {
    float scrollx;
    float scrolly;
    std::unique_ptr<sf::Shape> element;
    sf::Vector2f pos;
};

struct star {
    sf::Vector2f pos;
    sf::CircleShape star;
    int brightness;
    int speed;
    int phase;
};

struct comet {
    sf::Vector2f pos;
    sf::Vector2f vel;
    std::vector<sf::Vector2f> trail;
    bool cometinsky = false;
    int cd = 20;
    sf::Clock comet_cooldown;
};

struct blackhole_bkgd {
    sf::Vector2f pos;
    sf::CircleShape bh;
};

struct planet {
    sf::Color color;
    sf::CircleShape planet;
};

struct rock {
    sf::ConvexShape rock;
    sf::Vector2f pos;
    sf::Vector2f drift;
    int rotation;
};

class sky {
public:
    std::vector<star> starlist;
    std::vector<rock> rocklist;
    std::vector<planet> planetlist;
    std::vector<blackhole_bkgd> blackholelist;
    std::vector<comet> cometlist;
    sf::Clock bkgd_clock;
    sf::RectangleShape skyblock;

    sky::sky() {
        skyblock = sf::RectangleShape(sf::Vector2f(width, height));
        skyblock.setFillColor(sf::Color(0, 0, 35));
        skyblock.setPosition(sf::Vector2f(0, 0));
    }

    void makestars (int stars) {
        for (int i = 0; i < stars; i++) {
            star star;
            float radius = 1.f + (std::rand() % 2);
            star.star.setRadius(radius);
            star.star.setPosition(sf::Vector2f((std::rand() % width)*1.2, (std::rand() % height)*1.2));
            star.brightness = 140 + (std::rand() % 115);
            star.star.setFillColor(sf::Color(star.brightness, star.brightness, star.brightness));
            star.phase = std::rand() % 500 / 100.f;
            star.speed = (1 + std::rand() % 100) / 100.f;
            starlist.push_back(star);
        };
    }

    void updatesky (float deltatime) {
        float time = bkgd_clock.getElapsedTime().asSeconds();
        for (auto& pos: starlist) {
            int alpha = 140 + 80 * std::sin(time * pos.speed * pos.phase);
            sf::Color color = pos.star.getFillColor();            
            if (alpha > 255) alpha = 255;
            if (alpha < 0) alpha = 0;
            color.a = alpha;
        }
    }

    void drawsky (sf::RenderWindow& window, sf::Vector2f center) {
        window.draw(skyblock);
        sf::Transform farparallax;
        sf::Transform midparallax;
        sf::Transform nearparallax;
        farparallax.translate(sf::Vector2f(-center.x*0.06, -center.y*0.02));
        midparallax.translate(sf::Vector2f(-center.x*0.15, center.y*0.04));
        nearparallax.translate(sf::Vector2f(-center.x*0.24, center.y*0.06));

        for (auto& pos: starlist) {
            window.draw(pos.star, farparallax);
        }
    }
};