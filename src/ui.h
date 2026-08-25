#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "vars.h"
#include "states.h"

class mainmenu {
public:
    sf::Font font;
    sf::Text title;
    sf::Text starttxt;
    sf::RectangleShape startbtn;
    
    mainmenu() :
        font("AldotheApache.ttf"),
        title(font),
        starttxt(font)
    {
        title.setFont(font);
        title.setString("WORLDS OF BLOCKMAN");
        title.setCharacterSize(55);
        title.setFillColor(sf::Color(170, 100, 255));
        title.setPosition(sf::Vector2f((width-title.getGlobalBounds().size.x)/2, 100));

        starttxt.setFont(font);
        starttxt.setString("SPACE TO PLAY, ESC FROM GAME TO QUIT");
        starttxt.setCharacterSize(35);
        starttxt.setFillColor(sf::Color(170, 100, 255));
        starttxt.setOrigin(sf::Vector2f(starttxt.getLocalBounds().position.x + starttxt.getLocalBounds().size.x/2, starttxt.getLocalBounds().position.y + starttxt.getLocalBounds().size.y/2));
        starttxt.setPosition(sf::Vector2f(width/2, 450));

        startbtn.setSize(sf::Vector2f(starttxt.getLocalBounds().size.x*1.2, starttxt.getLocalBounds().size.y*2));
        startbtn.setFillColor(sf::Color(100, 30, 155));
        startbtn.setOrigin(sf::Vector2f(startbtn.getLocalBounds().size.x/2, startbtn.getLocalBounds().size.y/2));
        startbtn.setPosition(sf::Vector2f(width/2, starttxt.getPosition().y));
    }

    void play (sf::RenderWindow& window) {
        sf::Vector2i mouse_ = sf::Mouse::getPosition(window);
        sf::Vector2f mousepos = sf::Vector2f((float)mouse_.x, (float)mouse_.y);
        if (starttxt.getGlobalBounds().contains(mousepos)) {
            starttxt.setFillColor(sf::Color(255, 170, 30));
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) state = State::playing;
        }
        else starttxt.setFillColor(sf::Color(170, 100, 255));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) state = State::playing;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) std::cout <<
            "\nbutton origin: " << startbtn.getOrigin().x << ", " << startbtn.getOrigin().y <<
            "\ntext origin: " << starttxt.getOrigin().x << ", " << starttxt.getOrigin().y <<
            "\nbutton size: " << startbtn.getSize().x << ", " << startbtn.getSize().y <<
            "\ntext size: " << starttxt.getGlobalBounds().size.x << ", " << starttxt.getGlobalBounds().size.y <<
            "\nbutton pos: " << startbtn.getPosition().x << ", " << startbtn.getPosition().y <<
            "\ntext pos: " << starttxt.getPosition().x << ", " << starttxt.getPosition().y;
    }

    void draw (sf::RenderWindow& window) {
        window.draw(title);
        window.draw(startbtn);
        window.draw(starttxt);
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
        level.setFillColor(sf::Color(255, 45, 200, 200));
    }

    void draw (sf::RenderWindow& window) {
        level.setString("Level "+std::to_string(setnum*6+levelnum+1));
        level.setPosition(sf::Vector2f((width-level.getGlobalBounds().size.x)/2, 60));
        window.draw(level);
    }

    void checkexit () {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) state = State::pause;
    }
};

class pause {
public:
    sf::Font font;
    sf::Text paused;
    sf::Text resumetxt;
    sf::Text exittxt;

    pause() :
        font("AldotheApache.ttf"),
        paused(font),
        resumetxt(font),
        exittxt(font)
    {
        paused.setFont(font);
        paused.setString("PAUSED");
        paused.setFillColor(sf::Color(170, 170, 110));
        paused.setCharacterSize(35);
        paused.setPosition(sf::Vector2f((width-paused.getGlobalBounds().size.x)/2, 340));

        resumetxt.setFont(font);
        resumetxt.setString("SPACE TO RESUME");
        resumetxt.setFillColor(sf::Color(80, 210, 145));
        resumetxt.setCharacterSize(25);
        resumetxt.setPosition(sf::Vector2f((width-resumetxt.getGlobalBounds().size.x)/2, 440));

        exittxt.setFont(font);
        exittxt.setString("ESCAPE TO EXIT");
        exittxt.setFillColor(sf::Color(145, 80, 210));
        exittxt.setCharacterSize(25);
        exittxt.setPosition(sf::Vector2f((width-exittxt.getGlobalBounds().size.x)/2, 490));
    }

    void draw (sf::RenderWindow& window) {
        window.draw(paused);
        window.draw(resumetxt);
        window.draw(exittxt);
    }

    void checkaction(sf::RenderWindow& window) {
        sf::Vector2i mouse_ = sf::Mouse::getPosition(window);
        sf::Vector2f mousepos = sf::Vector2f((float)mouse_.x, (float)mouse_.y);
        if (resumetxt.getGlobalBounds().contains(mousepos)) {
            resumetxt.setFillColor(sf::Color(180, 200, 20));
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) state = State::playing;
        } else resumetxt.setFillColor(sf::Color(80, 210, 145));
        if (exittxt.getGlobalBounds().contains(mousepos)) {
            exittxt.setFillColor(sf::Color(20, 120, 255));
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) state = State::mainmenu;
        } else exittxt.setFillColor(sf::Color(145, 80, 210));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) state = State::playing;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) state = State::mainmenu; 
    }
};