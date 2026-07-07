#pragma once
#include <SFML/Graphics.hpp>
#include "vars.h"
#include "tilemap.h"
#include "tiletypes.h"

enum class tiletype {
    //Basic tile types
    empty,
    spawn,
    exit,
    solid,
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
// ' = single spike (same size as player)
// " = double spike (two spikes right beside each other)"
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
            for (int j = 0; j < 64; j++) {
                char tilecode = level[i*64+j];
                Tile new_tile;
                switch (tilecode) {
                    case '*': 
                        new_tile.type = tiletype::empty;
                        tilelist.push_back(new_tile);
                        break;
                    case '#':
                        new_tile.type = tiletype::solid;
                        new_tile.tile = std::make_unique<ground_>(sf::Vector2f(j*playerdim, i*playerdim));
                        tilelist.push_back(new_tile);
                        break;   
                    case 'S':
                        new_tile.type = tiletype::spawn;
                        spawn = sf::Vector2f(i*playerdim, j*playerdim);
                        tilelist.push_back(new_tile);
                        break;
                    case 'F':
                        new_tile.type = tiletype::exit;
                        finish = sf::Vector2f(i*playerdim, j*playerdim);
                        tilelist.push_back(new_tile);
                        break;
                    case '\'':
                        new_tile.type = tiletype::spike;
                        new_tile.tile = std::make_unique<spike>(sf::Vector2f(j*playerdim, i*playerdim));
                        tilelist.push_back(new_tile);
                        break;
                    case '"':
                        new_tile.type = tiletype::doublespike;
                        new_tile.tile = std::make_unique<doublespike>(sf::Vector2f(j*playerdim, i*playerdim));
                        tilelist.push_back(new_tile);
                        break;
                    case 'L':
                        new_tile.type = tiletype::lava;
                        new_tile.tile = std::make_unique<lava>(sf::Vector2f(j*playerdim, i*playerdim));
                        tilelist.push_back(new_tile);
                        break;
                    case 'W':
                        new_tile.type = tiletype::water;
                        new_tile.tile = std::make_unique<water>(sf::Vector2f(j*playerdim,i*playerdim));
                        tilelist.push_back(new_tile);
                        break;
                    case 'Z':
                        new_tile.type = tiletype::zero_g;
                        new_tile.tile = std::make_unique<zero_g>(sf::Vector2f(j*playerdim,i*playerdim));
                        tilelist.push_back(new_tile);
                        break;
                    case 'B':
                        new_tile.type = tiletype::blackhole;
                        new_tile.tile = std::make_unique<blackhole>(sf::Vector2f(j*playerdim, i*playerdim));
                        tilelist.push_back(new_tile);
                        break;
                    case 'P':
                        new_tile.type = tiletype::block_push; //cuz i cant have two 'B' cases
                        new_tile.tile = std::make_unique<block>(sf::Vector2f(j*playerdim, i*playerdim));
                        tilelist.push_back(new_tile);
                        break;
                    case '^':
                        new_tile.type = tiletype::spring;
                        new_tile.tile = std::make_unique<spring>(sf::Vector2f(j*playerdim, i*playerdim));
                        tilelist.push_back(new_tile);
                        break;
                }
            }
        }
    }
};