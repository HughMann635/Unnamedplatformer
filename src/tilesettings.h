#pragma once
#include <SFML/Graphics.hpp>
#include "vars.h"
#include "tilemap.h"

enum class tiletype {
    //Basic tile types
    empty,
    spawn,
    exit,
    solid,
    //Obstacles / non-player entities
    spike,
    doublespike,
    pushblock,
    spring,
    blackhole,
    //Environments
    lava,
    water,
    zero_g
};

struct Tile {
    tiletype type;
    sf::RectangleShape tile;
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
                        new_tile.tile.setFillColor(sf::Color(255, 200, 200));
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
                        tilelist.push_back(new_tile);
                        break;
                    case '"':
                        new_tile.type = tiletype::doublespike;
                        tilelist.push_back(new_tile);
                        break;
                    case 'L':
                        new_tile.type = tiletype::lava;
                        tilelist.push_back(new_tile);
                        break;
                    case 'W':
                        new_tile.type = tiletype::water;
                        tilelist.push_back(new_tile);
                        break;
                    case 'Z':
                        new_tile.type = tiletype::zero_g;
                        tilelist.push_back(new_tile);
                        break;
                    case 'B':
                        new_tile.type = tiletype::blackhole;
                        tilelist.push_back(new_tile);
                        break;
                    case 'P':
                        new_tile.type = tiletype::pushblock;
                        tilelist.push_back(new_tile);
                        break;
                    case '^':
                        new_tile.type = tiletype::spring;
                        tilelist.push_back(new_tile);
                        break;
                }
            }
        }
    }
};