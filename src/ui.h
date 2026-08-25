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
    sf::Text starttxtshadow;
    sf::RectangleShape startbtnshadow;
    
    mainmenu() :
        font("AldotheApache.ttf"),
        title(font),
        starttxt(font),
        starttxtshadow(font)
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

        sf::FloatRect starttxtbounds = starttxt.getLocalBounds();
        starttxt.setOrigin(sf::Vector2f(starttxtbounds.position.x + starttxtbounds.size.x/2, starttxtbounds.position.y + starttxtbounds.size.y/2));
        starttxt.setPosition(sf::Vector2f(width/2, 450));

        startbtn.setSize(sf::Vector2f(starttxtbounds.size.x*1.2, starttxtbounds.size.y*2));
        startbtn.setFillColor(sf::Color(100, 30, 155));
        startbtn.setOrigin(sf::Vector2f(startbtn.getLocalBounds().size.x/2, startbtn.getLocalBounds().size.y/2));
        startbtn.setPosition(sf::Vector2f(width/2, starttxt.getPosition().y));

        starttxtshadow = starttxt;
        starttxtshadow.setFillColor(sf::Color(0, 0, 0, 120));
        starttxtshadow.setPosition(starttxt.getPosition() + sf::Vector2f(4, 4));
        startbtnshadow = startbtn;
        startbtnshadow.setFillColor(sf::Color(0, 0, 0, 255));
        startbtnshadow.setPosition(startbtn.getPosition() + sf::Vector2f(6, 6));
    }

    void play (sf::RenderWindow& window) {
        sf::Vector2i mouse_ = sf::Mouse::getPosition(window);
        sf::Vector2f mousepos = sf::Vector2f((float)mouse_.x, (float)mouse_.y);
        if (startbtn.getGlobalBounds().contains(mousepos)) {
            starttxt.setFillColor(sf::Color(255, 170, 30));
            startbtn.setFillColor(sf::Color(185, 100, 30));
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) state = State::playing;
        }
        else { 
            starttxt.setFillColor(sf::Color(170, 100, 255));
            startbtn.setFillColor(sf::Color(100, 30, 155));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) state = State::playing;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) { std::cout <<
            "\nbutton origin: " << startbtn.getOrigin().x << ", " << startbtn.getOrigin().y <<
            "\ntext origin: " << starttxt.getOrigin().x << ", " << starttxt.getOrigin().y <<
            "\nbutton size: " << startbtn.getSize().x << ", " << startbtn.getSize().y <<
            "\ntext size: " << starttxt.getGlobalBounds().size.x << ", " << starttxt.getGlobalBounds().size.y <<
            "\nbutton pos: " << startbtn.getPosition().x << ", " << startbtn.getPosition().y <<
            "\ntext pos: " << starttxt.getPosition().x << ", " << starttxt.getPosition().y;
        }
    }

    void draw (sf::RenderWindow& window) {
        window.draw(title);
        window.draw(startbtnshadow);
        window.draw(startbtn);
        window.draw(starttxtshadow);
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
    sf::RectangleShape resumebtn;
    sf::RectangleShape exitbtn;

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

        sf::FloatRect resumetxtbounds = resumetxt.getLocalBounds();
        resumetxt.setOrigin(sf::Vector2f(resumetxtbounds.position.x + resumetxtbounds.size.x/2, resumetxtbounds.position.y + resumetxtbounds.size.y/2));
        resumetxt.setPosition(sf::Vector2f(width/2, 440));

        resumebtn.setSize(sf::Vector2f(resumetxtbounds.size.x*1.2, resumetxtbounds.size.y*2));
        resumebtn.setFillColor(sf::Color(10, 140, 75));
        resumebtn.setOrigin(sf::Vector2f(resumebtn.getLocalBounds().position.x + resumebtn.getLocalBounds().size.x/2, resumebtn.getLocalBounds().position.y + resumebtn.getLocalBounds().size.y/2));
        resumebtn.setPosition(sf::Vector2f(width/2, 440));

        exittxt.setFont(font);
        exittxt.setString("ESCAPE TO EXIT");
        exittxt.setFillColor(sf::Color(145, 80, 210));
        exittxt.setCharacterSize(25);

        sf::FloatRect exittxtbounds = exittxt.getLocalBounds();
        exittxt.setOrigin(sf::Vector2f(exittxtbounds.position.x + exittxtbounds.size.x/2, exittxtbounds.position.y + exittxtbounds.size.y/2));
        exittxt.setPosition(sf::Vector2f(width/2, 490));

        exitbtn.setSize(sf::Vector2f(resumetxtbounds.size.x*1.2, resumetxtbounds.size.y*2));
        exitbtn.setFillColor(sf::Color(75, 10, 140));
        exitbtn.setOrigin(sf::Vector2f(exitbtn.getLocalBounds().position.x + exitbtn.getLocalBounds().size.x/2, exitbtn.getLocalBounds().position.y + exitbtn.getLocalBounds().size.y/2));
        exitbtn.setPosition(sf::Vector2f(width/2, 490));    
    }

    void draw (sf::RenderWindow& window) {
        window.draw(paused);
        window.draw(resumebtn);
        window.draw(resumetxt);
        window.draw(exitbtn);
        window.draw(exittxt);
    }

    void checkaction(sf::RenderWindow& window) {
        sf::Vector2i mouse_ = sf::Mouse::getPosition(window);
        sf::Vector2f mousepos = sf::Vector2f((float)mouse_.x, (float)mouse_.y);
        if (resumebtn.getGlobalBounds().contains(mousepos)) {
            resumetxt.setFillColor(sf::Color(180, 200, 20));
            resumebtn.setFillColor(sf::Color(110, 130, 20));
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) state = State::playing;
        } else {
            resumetxt.setFillColor(sf::Color(80, 210, 145));
            resumebtn.setFillColor(sf::Color(10, 140, 75));
        }
        if (exitbtn.getGlobalBounds().contains(mousepos)) {
            exittxt.setFillColor(sf::Color(20, 120, 255));
            exitbtn.setFillColor(sf::Color(20, 50, 185));
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) state = State::mainmenu;
        } else {
            exittxt.setFillColor(sf::Color(145, 80, 210));
            exitbtn.setFillColor(sf::Color(75, 10, 140));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) state = State::playing;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) state = State::mainmenu; 
    }
};