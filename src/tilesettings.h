#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>
#include "vars.h"
#include "tiletypes.h"
#include "players.h"

//class player;

enum class tiletype {
    //Basic tile types
    empty,
    spawn,
    exit,
    ground,
    //Obstacles / non-player entities
    spike,
    doublespike,
    block_push,
    spring,
    blackhole,
    //Environments
    lava,
    water,
    zero_g
};

struct Tile {
    tiletype type;
    std::unique_ptr<tileTypes> tile;
};

//TILE CODES
// * = empty
// # = solid
// S = spawn point
// F = finish point
// 1 = single spike (same size as player)
// 2 = double spike (two spikes right beside each other)"
// L = lava
// W = water
// Z = zero-g zone
// B = black hole
// P = pushable block
// ^ = spring

class tilemap {
public:
    std::vector<Tile> tilelist;
    sf::Vector2f spawn;
    sf::Vector2f finishpoint;

    void loadmap (std::string level) {
        for (int i = 0; i < 36; i++) {
            for (int j = 0; j < 65; j++) {
                if (level[i*65+j] == '\n') {
                    continue;
                }
                char tilecode = level[i*65+j];
                Tile new_tile;
                switch (tilecode) {
                    case '*': 
                        new_tile.type = tiletype::empty;
                        tilelist.push_back(std::move(new_tile));
                        break;
                    case '#':
                        new_tile.type = tiletype::ground;
                        new_tile.tile = std::make_unique<ground_>(sf::Vector2f(j*playerdim, i*playerdim));
                        tilelist.push_back(std::move(new_tile));
                        break;   
                    case 'S':
                        new_tile.type = tiletype::spawn;
                        spawn = sf::Vector2f(j*playerdim, i*playerdim);
                        tilelist.push_back(std::move(new_tile));
                        break;
                    case 'F':
                        new_tile.type = tiletype::exit;
                        finishpoint = sf::Vector2f(i*playerdim, j*playerdim);
                        new_tile.tile = std::make_unique<finish>(sf::Vector2f(j*playerdim, i*playerdim));
                        tilelist.push_back(std::move(new_tile));
                        break;
                    case '1':
                        new_tile.type = tiletype::spike;
                        new_tile.tile = std::make_unique<spike>(sf::Vector2f(j*playerdim, i*playerdim));
                        tilelist.push_back(std::move(new_tile));
                        break;
                    case '2':
                        new_tile.type = tiletype::doublespike;
                        new_tile.tile = std::make_unique<doublespike>(sf::Vector2f(j*playerdim, i*playerdim));
                        tilelist.push_back(std::move(new_tile));
                        break;
                    case 'L':
                        new_tile.type = tiletype::lava;
                        new_tile.tile = std::make_unique<lava>(sf::Vector2f(j*playerdim, i*playerdim));
                        tilelist.push_back(std::move(new_tile));
                        break;
                    case 'W':
                        new_tile.type = tiletype::water;
                        new_tile.tile = std::make_unique<water>(sf::Vector2f(j*playerdim,i*playerdim));
                        tilelist.push_back(std::move(new_tile));
                        break;
                    case 'Z':
                        new_tile.type = tiletype::zero_g;
                        new_tile.tile = std::make_unique<zero_g>(sf::Vector2f(j*playerdim,i*playerdim));
                        tilelist.push_back(std::move(new_tile));
                        break;
                    case 'B':
                        new_tile.type = tiletype::blackhole;
                        new_tile.tile = std::make_unique<blackhole>(sf::Vector2f(j*playerdim, i*playerdim));
                        tilelist.push_back(std::move(new_tile));
                        break;
                    case 'P':
                        new_tile.type = tiletype::block_push; //cuz i cant have two 'B' cases
                        new_tile.tile = std::make_unique<block>(sf::Vector2f(j*playerdim, i*playerdim));
                        tilelist.push_back(std::move(new_tile));
                        break;
                    case '^':
                        new_tile.type = tiletype::spring;
                        new_tile.tile = std::make_unique<spring>(sf::Vector2f(j*playerdim, i*playerdim));
                        tilelist.push_back(std::move(new_tile));
                        break;
                }
            }
        }
    }

    void checkCollisions (entity& Object) {
        swimming = false;
        zerogactive = false;
        for (auto& pos: tilelist) {
            if (pos.type != tiletype::block_push) { continue; }

            block* block_ = dynamic_cast<block*>(pos.tile.get());
            if (!block_) { continue; }

            sf::FloatRect blockbounds = block_ -> collide();

            sf::FloatRect playerbounds = Object.shape().getGlobalBounds();
            if (blockbounds.findIntersection(playerbounds)) {
                float playercenter = playerbounds.position.y + playerbounds.size.y / 2;
                float blocktop = blockbounds.position.y;
                float blockbottom = blockbounds.position.y + blockbounds.size.y;
                if ((playercenter > blocktop && playercenter < blockbottom)) {
                    if (Object.shape().getPosition().x < block_ -> shape().getPosition().x) {
                        block_ -> velocity.x = trianglepushspeed;
                    } else if (Object.shape().getPosition().x > block_ -> shape().getPosition().x) {
                        block_ -> velocity.x = -trianglepushspeed;
                    }
                }
            }

            for (auto& rest: tilelist) {
               if (pos.tile != rest.tile && rest.type != tiletype::empty && rest.type != tiletype::spawn) {
                    sf::FloatRect restbounds = rest.tile -> collide();
                    if (!blockbounds.findIntersection(restbounds)) { continue; }
                    else {
                        switch (rest.type) {
                            case tiletype::ground:
                            groundCollide(*block_, restbounds);                      
                            break;
                            case tiletype::block_push:
                            block_ -> velocity.x = 0;
                            break;
                            case tiletype::zero_g:
                            blockgravity = 0;
                            break;
                            case tiletype::water:
                            case tiletype::lava:
                            blockgravity = 500;
                            break;
                            default:
                            break;
                        }
                    }
                }
            }
        }
        for (auto& pos: tilelist) {
            if (pos.type == tiletype::empty || pos.type == tiletype::spawn) { continue; }

            sf::FloatRect playerbounds = Object.shape().getGlobalBounds();
            sf::FloatRect tilebounds = pos.tile -> collide();

            if (!playerbounds.findIntersection(tilebounds)) { continue; }
            else {
                switch (pos.type) {
                    case tiletype::empty:
                    break;
                    case tiletype::ground:
                    groundCollide(Object, tilebounds);
                    break;
                    case tiletype::spike:
                    case tiletype::doublespike:
                    case tiletype::lava:
                    case tiletype::blackhole:
                    std::cout << "You died :(";
                    running = false;
                    break;
                    case tiletype::exit:
                    running = false;
                    break;
                    case tiletype::water:
                    swimming = true;
                    break;
                    case tiletype::zero_g:
                    zerogactive = true;
                    break;
                    case tiletype::block_push:
                    groundCollide(Object, tilebounds);
                    break;
                    case tiletype::spring:
                    Object.velocity.y = -1000.f;
                    break;
                    default: 
                    break;
                    }
                }
            }
    }

    void groundCollide(entity& Object, sf::FloatRect& bounds) {
        float topside1 = Object.shape().getPosition().y;
        float leftside1 = Object.shape().getPosition().x;
        float rightside1 = Object.shape().getPosition().x + Object.shape().getGlobalBounds().size.x;
        float bottomside1 = Object.shape().getPosition().y + Object.shape().getGlobalBounds().size.y;

        float topside2 = bounds.position.y;
        float leftside2 = bounds.position.x;
        float rightside2 = bounds.position.x + bounds.size.x;
        float bottomside2 = bounds.position.y + bounds.size.y;

        float topovlp = bottomside2-topside1; //hit from below i.e. knocking on the roof
        float bottomovlp = bottomside1-topside2; //hit from above i.e. landing
        float leftovlp = rightside2-leftside1; //hit on left side
        float rightovlp = rightside1-leftside2; //right hit
        
        //any comments here are for my own sake
        float lowestoverlap = std::min({topovlp, bottomovlp, leftovlp, rightovlp});

        if (topside1 < bottomside2 && bottomside1 > topside2 && leftside1 < rightside2 && rightside1 > leftside2) {
            if (lowestoverlap == topovlp) {
                Object.shape().setPosition(sf::Vector2f(Object.shape().getPosition().x, bottomside2));
                Object.velocity.y = 0;
            } else if (lowestoverlap == bottomovlp) {
                Object.shape().setPosition(sf::Vector2f(Object.shape().getPosition().x, topside2-Object.shape().getGlobalBounds().size.y));
                Object.velocity.y = 0;
                Object.grounded = true;
            } else if (lowestoverlap == rightovlp) {
                Object.shape().setPosition(sf::Vector2f(leftside2-Object.shape().getGlobalBounds().size.x, Object.shape().getPosition().y));
            } else if (lowestoverlap == leftovlp) {
                Object.shape().setPosition(sf::Vector2f(rightside2, Object.shape().getPosition().y));
            }
        }
    }

    void updatemap (float deltatime) {
        for (auto& pos: tilelist) {
            if (pos.type != tiletype::empty && pos.type != tiletype::spawn) {
                pos.tile -> movetile(deltatime);
            }
        }
    }

    void drawmap (sf::RenderWindow& window) {
        for (auto& pos: tilelist) {
            if (pos.type != tiletype::empty && pos.type != tiletype::spawn) {
                pos.tile -> draw(window);
            }
        }
    }
};