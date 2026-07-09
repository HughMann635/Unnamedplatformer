#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>
#include "vars.h"
#include "tiletypes.h"

class player;

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
    sf::Vector2f finish;

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
                        finish = sf::Vector2f(i*playerdim, j*playerdim);
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

    void checkCollisions (player& Player) {
        for (auto& pos: tilelist) {
            if (pos.type == tiletype::empty) { continue; }

            sf::FloatRect playerbounds = Player.playershape.getGlobalBounds();
            sf::FloatRect tilebounds = pos.tile -> collide();
            
            //MOST OF THESE ARE PLACEHOLDER ACTIONS
            switch (pos.type) {
                case tiletype::empty:
                continue;
                case tiletype::ground:
                continue; //WILL CHANGE LATER
                case tiletype::spike:
                case tiletype::doublespike:
                case tiletype::lava:
                case tiletype::blackhole:
                running = false;
                case tiletype::water:
                case tiletype::zero_g:
                case tiletype::block_push:
                Player.velocity.y = -500.f;
                case tiletype::spring:
                Player.velocity.y = -1000.f;
            }
        }
    }

    void drawmap (sf::RenderWindow& window) {
        for (auto& pos: tilelist) {
            if (pos.type != tiletype::empty && pos.type != tiletype::spawn && pos.type != tiletype::exit) {
                pos.tile -> draw(window);
            }
        }
    }
};