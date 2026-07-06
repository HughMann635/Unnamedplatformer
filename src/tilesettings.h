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

class tilemap {
public:
    std::vector<Tile> tilelist;
    sf::Vector2f spawn;
    sf::Vector2f finish;

    void loadmap (std::string level) {
        for (int i = 0; i < 36; i++) {
            for (int j = 0; j < 64; j++) {
                char tilecode = level[i][j];
                Tile new_tile;
                new_tile.tile.setSize(sf::Vector2f(playerdim, playerdim));
            }
        }
    }
};