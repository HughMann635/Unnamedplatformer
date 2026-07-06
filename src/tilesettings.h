#pragma once
#include <SFML/Graphics.hpp>
#include "vars.h"

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
    
};