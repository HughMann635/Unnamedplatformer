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
    sf::Vector2f velocity;
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
    sf::VertexArray ring_back;
    sf::VertexArray ring_front;
    float ring_angle;
    bool has_ring;
    std::vector<sf::CircleShape> details;
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
        makestars(stars);
        makeplanets(planets);
        makecomet();
    }

    sf::VertexArray makeplanetrings(float radius, float thickness, float startangle, float endangle, sf::Color color) {
        sf::VertexArray ring_arc(sf::PrimitiveType::TriangleStrip);

        float innerradius = radius - (thickness / 2);
        float outerradius = radius + (thickness / 2);

        float startradians = startangle * (3.14159265358979 / 180);
        float endradians = endangle * (3.14159265358979 / 180);
        float dists = (endradians - startradians) / 25;

        for (int i = 0; i < 27; i++) {
            float angle = startradians + (i * dists);
            float cos = std::cos(angle);
            float sin = std::sin(angle);

            ring_arc.append(sf::Vertex{sf::Vector2f(outerradius*cos, outerradius*sin), color});
            ring_arc.append(sf::Vertex{sf::Vector2f(innerradius*cos, innerradius*sin), color});
        }
        return ring_arc;
    }

    void makestars (int stars) {
        for (int i = 0; i < stars; i++) {
            star star;
            float radius = 1.f + (std::rand() % 2);
            star.star.setRadius(radius);
            star.star.setPosition(sf::Vector2f((std::rand() % width)*1.2, (std::rand() % height)*1.2));
            if (starlist.size() > 0) {
                for (auto& pos: starlist) {
                    while (pos.star.getGlobalBounds().findIntersection(star.star.getGlobalBounds())) {
                        if (!pos.star.getGlobalBounds().findIntersection(star.star.getGlobalBounds())) {
                            break;
                        }
                        star.star.setPosition(sf::Vector2f((std::rand() % width)*1.2, (std::rand() % 520)*1.2));
                    }
                }
            } 
            star.brightness = 215 + (std::rand() % 40);
            star.star.setFillColor(sf::Color(star.brightness, star.brightness, star.brightness));
            star.phase = std::rand() % 500 / 100.f;
            star.speed = (1 + std::rand() % 100) / 100.f;
            starlist.push_back(star);
        };
    }

    void makeplanets (int planets) {
        for (int i = 0; i < planets; i++) {
            planet planet;
            float radius = 5.f + (std::rand() % 20);
            planet.planet.setRadius(radius);
            planet.planet.setOrigin(sf::Vector2f(radius, radius));
            planet.planet.setPosition(sf::Vector2f((std::rand() % width) * 1.1 + 20, (std::rand() % 520) + 20));
            if (starlist.size() > 0) {
                for (auto& pos: planetlist) {
                    while (pos.planet.getGlobalBounds().findIntersection(planet.planet.getGlobalBounds())) {
                        if (!pos.planet.getGlobalBounds().findIntersection(planet.planet.getGlobalBounds())) {
                            break;
                        }
                        planet.planet.setPosition(sf::Vector2f((std::rand() % width) * 1.1 + 20, (std::rand() % 520) + 20));
                    }
                }
            }
            planet.planet.setFillColor(sf::Color(std::rand() % 50 + 95, std::rand() % 50 + 95, std::rand() % 50 + 95));
            
            if (std::rand() % 5 > 1) {
                planet.ring_back = makeplanetrings(radius*1.4, std::rand() % 1 + 2, 180, 360, sf::Color(170, 100, 80));
                planet.ring_front = makeplanetrings(radius*1.4, std::rand() % 1 + 2, 0, 180, sf::Color(170, 100, 80));
                planet.ring_angle = std::rand() % 40 - 20;
            }

            for (int i = 0; i < std::rand() % 4 + 2; i++) {
                sf::CircleShape crater;
                crater.setRadius(planet.planet.getRadius()/(5 + std::rand() % 5));
                crater.setOrigin(sf::Vector2f(crater.getRadius(), crater.getRadius()));
                float crateroffset = std::rand() % static_cast<int>(radius * 0.7);
                float crateroffsetangle = std::rand() % 360 * (3.14159265358979/180);
                crater.setPosition(sf::Vector2f(std::cos(crateroffsetangle)*crateroffset, std::sin(crateroffsetangle)*crateroffset));
                if (planet.details.size() > 0) {
                    for (auto& pos: planet.details) {
                        while (pos.getGlobalBounds().findIntersection(crater.getGlobalBounds())) {
                            if (!pos.getGlobalBounds().findIntersection(crater.getGlobalBounds())) break;
                            crateroffset = std::rand() % static_cast<int>(radius * 0.7);
                            crateroffsetangle = std::rand() % 360 * (3.14159265358979/180);
                            crater.setPosition(sf::Vector2f(std::cos(crateroffsetangle)*crateroffset, std::sin(crateroffsetangle)*crateroffset));
                        }
                    }
                }
                crater.setPosition(sf::Vector2f(std::cos(crateroffsetangle)*crateroffset, std::sin(crateroffsetangle)*crateroffset));
                crater.setFillColor(sf::Color(planet.planet.getFillColor().r * 0.7, planet.planet.getFillColor().g * 0.7, planet.planet.getFillColor().b * 0.7));
                planet.details.push_back(crater);
            }
            planetlist.push_back(planet);
        }
        std::sort(planetlist.begin(), planetlist.end(), [](const planet& a, const planet& b) { return a.planet.getRadius() < b.planet.getRadius(); });
    }
    
    void makecomet () {
        cometlist.clear();
        int comets = 3;

        for (int i = 0; i < comets; i++) {
            comet comet;
            comet.cd = 5 + std::rand() % 15;
            comet.cometinsky = false;
            comet.comet_cooldown.restart();
            cometlist.push_back(comet);
        }
    }

    void makerocks () {

    }

    void makeblackholes () {

    }

    void updatesky (float deltatime) {
        float time = bkgd_clock.getElapsedTime().asSeconds();
        for (auto& pos: starlist) {
            int alpha = 170 + 85 * std::sin(time * pos.speed * pos.phase);
            sf::Color color = pos.star.getFillColor();            
            if (alpha > 255) alpha = 255;
            if (alpha < 0) alpha = 0;
            color.a = alpha;
            pos.star.setFillColor(color);
        }   
        for (auto& pos: cometlist) {
            if (!pos.cometinsky) {
                if (pos.comet_cooldown.getElapsedTime().asSeconds() >= pos.cd) {
                    pos.cometinsky = true;
                    float startypos = 50 + std::rand() % 450;
                    pos.pos = sf::Vector2f(-30, startypos);
                    float speed = 320 + std::rand() % 300;
                    float angle = (-20 + std::rand() % 40) * (3.14159265358979/180);
                    pos.velocity = (sf::Vector2f(std::cos(angle)*speed, std::sin(angle)*speed));
                    if (std::rand() % 1000 >= 500) {
                        pos.pos = sf::Vector2f(width+30, startypos);
                        pos.velocity = (sf::Vector2f(-std::cos(angle)*speed, std::sin(angle)*speed));
                    }
                    pos.trail.clear();
                }
            } else {
                pos.pos += pos.velocity * deltatime;
                pos.trail.push_back(pos.pos);
                if (pos.trail.size() > 25) {
                    pos.trail.erase(pos.trail.begin());
                }
                if (pos.pos.x > width + 200 || pos.pos.x < -70 || pos.pos.y > height + 100 || pos.pos.y < -100) {
                    pos.cometinsky = false;
                    pos.comet_cooldown.restart();
                }
            }
        }
    }

    void drawsky (sf::RenderWindow& window, sf::Vector2f center) {
        window.draw(skyblock);
        sf::Transform farparallax;
        sf::Transform midparallax;
        sf::Transform nearparallax;
        farparallax.translate(sf::Vector2f(-center.x*0.06, -center.y*0.02));
        midparallax.translate(sf::Vector2f(-center.x*0.15, -center.y*0.04));
        nearparallax.translate(sf::Vector2f(-center.x*0.24, -center.y*0.06));

        for (auto& pos: starlist) {
            window.draw(pos.star, farparallax);
        }
        for (auto& pos: planetlist) {
            sf::Transform planetparallax;
            planetparallax.translate(sf::Vector2f(-center.x*(pos.planet.getRadius()/150), -center.y*(pos.planet.getRadius()/750)));

            sf::Transform ringparallax = planetparallax;
            ringparallax.translate(pos.planet.getPosition());
            ringparallax.rotate(sf::degrees(pos.ring_angle));
            ringparallax.scale(sf::Vector2f(1, 0.3));

            sf::Transform detailparallax = planetparallax;
            detailparallax.translate(pos.planet.getPosition());

            window.draw(pos.ring_back, ringparallax);
            window.draw(pos.planet, planetparallax);
            for (int i = 0; i < pos.details.size(); i++) {
                window.draw(pos.details[i], detailparallax);
            }
            window.draw(pos.ring_front, ringparallax);
        }
        for (auto& pos: cometlist) {
            if (!pos.cometinsky || pos.trail.size() < 2) continue;

            sf::VertexArray tail(sf::PrimitiveType::LineStrip);
            for (int i = 0; i < pos.trail.size(); i++) {
                float alphalevel = static_cast<float>(i) / static_cast<float>(pos.trail.size());
                float trailalpha = alphalevel * 230;
                sf::Color trailcolor (sf::Color(180, 230, 255, trailalpha));
                tail.append(sf::Vertex{pos.trail[i], trailcolor});
            }
            window.draw(tail, midparallax);

            sf::CircleShape head;
            head.setRadius(4);
            head.setOrigin(sf::Vector2f(4, 4));
            head.setPosition(pos.pos);
            head.setFillColor(sf::Color(255, 255, 240));
            window.draw(head, midparallax);
        }
    }
};