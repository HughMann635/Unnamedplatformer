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
public:
    sf::Font font;
    sf::Text level;

    playing() :
        font("AldotheApache.ttf"),
        level(font)
    {
        level.setFont(font);
        level.setString("Level "+(setnum*6+levelnum+1));
        level.setCharacterSize(35);
        level.setPosition(sf::Vector2f((width-level.getGlobalBounds().size.x)/2, 60));
        level.setFillColor(sf::Color(255, 45, 200));
    }

    void draw (sf::RenderWindow& window) {
        level.setString("Level "+std::to_string(setnum*6+levelnum+1));
        level.setPosition(sf::Vector2f((width-level.getGlobalBounds().size.x)/2, 60));
        window.draw(level);
    }

    void checkexit () {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) state = State::mainmenu;
    }
};