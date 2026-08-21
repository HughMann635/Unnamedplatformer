#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "vars.h"
#include "states.h"

class mainmenu {
public:
    sf::Font font;
    sf::Text title;
    sf::Text startbtn;
    
    mainmenu() :
        title(font),
        startbtn(font)
    {
        font.openFromFile("AldotheApache.ttf");
        title.setFont(font);
        title.setString("WORLDS OF BLOCKMAN");
        title.setCharacterSize(55);
        title.setFillColor(sf::Color(170, 100, 255));
        title.setPosition(sf::Vector2f(width/2-(title.getGlobalBounds().size.x), 100));

        startbtn.setFont(font);
        startbtn.setString("PLAY");
        startbtn.setCharacterSize(35);
        startbtn.setFillColor(sf::Color(170, 100, 255));
        startbtn.setPosition(sf::Vector2f(width/2-(title.getGlobalBounds().size.x), 100));
    }
};

class playing {

};