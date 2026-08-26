#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "vars.h"
#include "states.h"

sf::Text txtshadow (int shade, int depth, sf::Text text) {
    sf::Text shadow = text;
    shadow.setFillColor(sf::Color(0, 0, 0, shade));
    shadow.setPosition(text.getPosition()+sf::Vector2f(depth, depth));
    return shadow;
}

sf::RectangleShape rectshadow (int shade, int depth, sf::RectangleShape shape) {
    sf::RectangleShape shadow = shape;
    shadow.setFillColor(sf::Color(0, 0, 0, shade));
    shadow.setPosition(shape.getPosition()+sf::Vector2f(depth, depth));
    return shadow;
}

class mainmenu {
public:
    sf::Font font;
    sf::Text title;
    sf::Text starttxt;
    sf::RectangleShape startbtn;
    sf::Text titleshadow;
    sf::Text starttxtshadow;
    sf::RectangleShape startbtnshadow;
    
    mainmenu() :
        font("AldotheApache.ttf"),
        title(font),
        titleshadow(font),
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

        titleshadow = title;
        titleshadow.setFillColor(sf::Color(0, 0, 0, 235));
        titleshadow.setPosition(title.getPosition() + sf::Vector2f(6, 6));
        starttxtshadow = starttxt;
        starttxtshadow.setFillColor(sf::Color(0, 0, 0, 120));
        starttxtshadow.setPosition(starttxt.getPosition() + sf::Vector2f(4, 4));
        startbtnshadow = startbtn;
        startbtnshadow.setFillColor(sf::Color(0, 0, 0, 235));
        startbtnshadow.setPosition(startbtn.getPosition() + sf::Vector2f(6, 6));
    }

    void play (sf::RenderWindow& window) {
        sf::Vector2i mouse_ = sf::Mouse::getPosition(window);
        sf::Vector2f mousepos = sf::Vector2f((float)mouse_.x, (float)mouse_.y);
        if (startbtn.getGlobalBounds().contains(mousepos)) {
            starttxt.setFillColor(sf::Color(255, 170, 30));
            startbtn.setFillColor(sf::Color(185, 100, 30));
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) state = State::levelselect;
        }
        else { 
            starttxt.setFillColor(sf::Color(170, 100, 255));
            startbtn.setFillColor(sf::Color(100, 30, 155));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) state = State::levelselect;
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
        window.draw(titleshadow);
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
    int levelshade = 225;

    playing() :
        font("AldotheApache.ttf"),
        level(font)
    {
        level.setFont(font);
        level.setString("Level "+(setnum*6+levelnum+1));
        level.setCharacterSize(35);
        level.setPosition(sf::Vector2f((width-level.getGlobalBounds().size.x)/2, 60));
        level.setFillColor(sf::Color(255, 45, 200, levelshade));
    }

    void draw (sf::RenderWindow& window) {
        level.setString("Level "+std::to_string(setnum*6+levelnum+1));
        sf::Vector2i mouse_ = sf::Mouse::getPosition(window);
        if (mouse_.y >= 200 && levelshade > 0) levelshade -= 3;
        else if (mouse_.y < 200 && levelshade < 225) levelshade += 3;
        level.setFillColor(sf::Color(255, 45, 200, levelshade));
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
    sf::Text resumetxtshadow;
    sf::Text exittxtshadow;
    sf::RectangleShape resumebtnshadow;
    sf::RectangleShape exitbtnshadow;

    pause() :
        font("AldotheApache.ttf"),
        paused(font),
        resumetxt(font),
        exittxt(font),
        resumetxtshadow(font),
        exittxtshadow(font)
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
        
        resumetxtshadow = resumetxt;
        resumetxtshadow.setFillColor(sf::Color(0, 0, 0, 120));
        resumetxtshadow.setPosition(resumetxt.getPosition()+sf::Vector2f(4, 4));
        exittxtshadow = exittxt;
        exittxtshadow.setFillColor(sf::Color(0, 0, 0, 120));
        exittxtshadow.setPosition(exittxt.getPosition()+sf::Vector2f(4, 4));
        resumebtnshadow = resumebtn;
        resumebtnshadow.setFillColor(sf::Color(0, 0, 0, 235));
        resumebtnshadow.setPosition(resumebtn.getPosition()+sf::Vector2f(6, 6));
        exitbtnshadow = exitbtn;
        exitbtnshadow.setFillColor(sf::Color(0, 0, 0, 235));
        exitbtnshadow.setPosition(exitbtnshadow.getPosition()+sf::Vector2f(6, 6));
    }

    void draw (sf::RenderWindow& window) {
        window.draw(paused);
        window.draw(resumebtnshadow);
        window.draw(resumebtn);
        window.draw(resumetxtshadow);
        window.draw(resumetxt);
        window.draw(exitbtnshadow);
        window.draw(exitbtn);
        window.draw(exittxtshadow);
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

class levelselect {
public:
    sf::Font font;
    sf::Text goright;
    sf::Text goleft;
    sf::Text set;
    sf::RectangleShape gorightbtn;
    sf::RectangleShape goleftbtn;
    int page = 0;
    sf::Text levelnums[6];
    sf::Text numshadows[6];
    sf::RectangleShape levelbtns[6];
    sf::RectangleShape btnshadows[6];

    levelselect() :
        font("AldotheApache.ttf"),
        goright(font),
        goleft(font),
        set(font),
        levelnums{font, font, font, font, font, font},
        numshadows{font, font, font, font, font, font}
    {
        goright.setString(">");
        goright.setCharacterSize(30);
        goright.setFillColor(sf::Color(140, 225, 10));
        sf::FloatRect gorightbounds = goright.getLocalBounds();
        goright.setOrigin(sf::Vector2f(gorightbounds.position.x + gorightbounds.size.x/2, gorightbounds.position.y + gorightbounds.size.y/2));
        goright.setPosition(sf::Vector2f(1180, height/2));

        goleft.setString("<");
        goleft.setCharacterSize(30);
        goleft.setFillColor(sf::Color(140, 225, 10));
        sf::FloatRect goleftbounds = goleft.getLocalBounds();
        goleft.setOrigin(sf::Vector2f(goleftbounds.position.x + goleftbounds.size.x/2, goleftbounds.position.y + goleftbounds.size.y/2));
        goleft.setPosition(sf::Vector2f(100, height/2));

        gorightbtn.setSize(sf::Vector2f(40, 40));
        gorightbtn.setFillColor(sf::Color(240, 255, 80));
        sf::FloatRect rightbtnbounds = gorightbtn.getLocalBounds();
        gorightbtn.setOrigin(sf::Vector2f(rightbtnbounds.position.x + rightbtnbounds.size.x/2, rightbtnbounds.position.y + rightbtnbounds.size.y/2));
        gorightbtn.setPosition(goright.getPosition());

        goleftbtn.setSize(sf::Vector2f(40, 40));
        goleftbtn.setFillColor(sf::Color(240, 255, 80));
        sf::FloatRect leftbtnbounds = goleftbtn.getLocalBounds();
        goleftbtn.setOrigin(sf::Vector2f(leftbtnbounds.position.x + leftbtnbounds.size.x/2, leftbtnbounds.position.y + leftbtnbounds.size.y/2));
        goleftbtn.setPosition(goleft.getPosition());

        set.setString("set " + std::to_string(page+1));
        set.setCharacterSize(45);
        set.setFillColor(sf::Color(120, 100, 190));
        sf::FloatRect setbounds = set.getLocalBounds();
        set.setOrigin(sf::Vector2f(setbounds.position.x + setbounds.size.x/2, setbounds.position.y + setbounds.size.y/2));
        set.setPosition(sf::Vector2f(width/2, 100));

        for (int i = 0; i < 6; i++) {
            levelnums[i].setCharacterSize(45);
            levelnums[i].setFillColor(sf::Color(0, 100, 240));
            levelbtns[i].setSize(sf::Vector2f(70, 70));
            levelbtns[i].setFillColor(sf::Color(0, 150, 250));
            //levelbtns[i].setOutlineColor(sf::Color(0, 100, 240));
            //levelbtns[i].setOutlineThickness(-2);
            levelbtns[i].setOrigin(sf::Vector2f(levelbtns[i].getLocalBounds().position.x + levelbtns[i].getLocalBounds().size.x/2, levelbtns[i].getLocalBounds().position.y + levelbtns[i].getLocalBounds().size.y/2));
        }
    }

    void draw (sf::RenderWindow& window) {
        set.setString("set " + std::to_string(page+1));
        window.draw(set);
        window.draw(gorightbtn);
        window.draw(goright);
        window.draw(goleftbtn);
        window.draw(goleft);
        for (int i = 0; i < 6; i++) {
            window.draw(btnshadows[i]);
            window.draw(levelbtns[i]);
            window.draw(numshadows[i]);
            window.draw(levelnums[i]);
        }
    }

    void select(sf::RenderWindow& window) {
        sf::Vector2i mouse_ = sf::Mouse::getPosition(window);
        sf::Vector2f mousepos = sf::Vector2f((float)mouse_.x, (float)mouse_.y);
        if (gorightbtn.getGlobalBounds().contains(mousepos)) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !mouseheld && page < 4) {
                page += 1;
                mouseheld = true;
            } 
        }
        if (goleftbtn.getGlobalBounds().contains(mousepos)) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !mouseheld && page > 0) {
                page -= 1;
                mouseheld = true;
            } 
        }

        for (int i = 0; i < 6; i++) {
            if (levelbtns[i].getGlobalBounds().contains(mousepos)) {
                levelnums[i].setFillColor(sf::Color(170, 30, 80));
                levelbtns[i].setFillColor(sf::Color(100, 0, 30));
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    levelnum = i;
                    setnum = page;
                    state = State::playing;
                }
            } else {
                levelnums[i].setFillColor(sf::Color(0, 100, 240));
                levelbtns[i].setFillColor(sf::Color(0, 150, 250));
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) state = State::mainmenu;

        for (int i = 0; i < 6; i++) {
            int levelnumber = page * 6 + i + 1;
            levelnums[i].setString(std::to_string(levelnumber));
            levelnums[i].setOrigin(sf::Vector2f(levelnums[i].getLocalBounds().position.x + levelnums[i].getLocalBounds().size.x/2, levelnums[i].getLocalBounds().position.y + levelnums[i].getLocalBounds().size.y/2));
            if (i < 3) levelnums[i].setPosition(sf::Vector2f(400 * i + 240, 250));
            else levelnums[i].setPosition(sf::Vector2f(400 * (i-3) + 240, 470));
            if (i < 3) levelbtns[i].setPosition(sf::Vector2f(400 * i + 240, 250));
            else levelbtns[i].setPosition(sf::Vector2f(400 * (i-3) + 240, 470));
            numshadows[i] = levelnums[i];
            numshadows[i].setFillColor(sf::Color(0, 0, 0, 120));
            numshadows[i].setPosition(levelnums[i].getPosition() + sf::Vector2f(3, 3));
            btnshadows[i] = levelbtns[i];
            btnshadows[i].setFillColor(sf::Color(0, 0, 0, 215));
            btnshadows[i].setPosition(levelbtns[i].getPosition() + sf::Vector2f(5, 5));
        }
    }
};