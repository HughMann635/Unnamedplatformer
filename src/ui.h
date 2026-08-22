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
        font("AldotheApache.ttf"),
        title(font),
        startbtn(font)
    {
        //font.openFromFile("AldotheApache.ttf");
        title.setFont(font);
        title.setString("WORLDS OF BLOCKMAN");
        title.setCharacterSize(55);
        title.setFillColor(sf::Color(170, 100, 255));
        title.setPosition(sf::Vector2f((width-title.getGlobalBounds().size.x)/2, 100));

        startbtn.setFont(font);
        startbtn.setString("SPACE TO PLAY, ESC FROM GAME TO QUIT"); //WILL MAKE INTO A CLICKABLE BUTTON
        startbtn.setCharacterSize(35);
        startbtn.setFillColor(sf::Color(170, 100, 255));
        startbtn.setPosition(sf::Vector2f((width-startbtn.getGlobalBounds().size.x)/2, 500));
    }

    void play () {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) state = State::playing;
    }

    void draw (sf::RenderWindow& window) {
        window.draw(title);
        window.draw(startbtn);
    }
};

class playing {

};