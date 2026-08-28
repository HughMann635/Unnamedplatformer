#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "vars.h"
#include "states.h"

inline sf::Text textshadow (int shade, int depth, sf::Text text) {
    sf::Text shadow = text;
    shadow.setFillColor(sf::Color(0, 0, 0, shade));
    shadow.setPosition(text.getPosition()+sf::Vector2f(depth, depth));
    return shadow;
}

inline sf::RectangleShape rectshadow (int shade, int depth, sf::RectangleShape shape) {
    sf::RectangleShape shadow = shape;
    shadow.setFillColor(sf::Color(0, 0, 0, shade));
    shadow.setPosition(shape.getPosition()+sf::Vector2f(depth, depth));
    return shadow;
}

inline sf::Text maketext (int size, sf::Color color, const std::string& string, sf::Font& font, sf::Vector2f position) {
    sf::Text text(font);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setString(string);
    sf::FloatRect textbounds = text.getLocalBounds();
    text.setOrigin(sf::Vector2f(textbounds.position.x + textbounds.size.x/2, textbounds.position.y + textbounds.size.y/2));
    text.setPosition(position);
    return text;
}

inline sf::RectangleShape makebtn (sf::Vector2f size, sf::Color color, sf::Vector2f position) {
    sf::RectangleShape button;
    button.setSize(size);
    button.setFillColor(color);
    button.setOrigin(sf::Vector2f(button.getLocalBounds().size.x/2, button.getLocalBounds().size.y/2));
    button.setPosition(position);
    return button;

}

class mainmenu {
public:
    sf::Font font;
    sf::Text title;
    sf::Text starttxt;
    sf::RectangleShape startbtn;
    sf::Text creditstxt;
    sf::RectangleShape creditsbtn;
    sf::Text settingstxt;
    sf::RectangleShape settingsbtn;
    sf::Text handbooktxt;
    sf::RectangleShape handbookbtn;
    sf::Text titleshadow;
    sf::Text starttxtshadow;
    sf::RectangleShape startbtnshadow;
    sf::Text creditstxtshadow;
    sf::RectangleShape creditsbtnshadow;
    sf::Text settingstxtshadow;
    sf::RectangleShape settingsbtnshadow;
    sf::Text handbooktxtshadow;
    sf::RectangleShape handbookbtnshadow;
    
    mainmenu() :
        font("AldotheApache.ttf"),
        title(font),
        titleshadow(font),
        starttxt(font),
        starttxtshadow(font),
        creditstxt(font),
        creditstxtshadow(font),
        settingstxt(font),
        settingstxtshadow(font),
        handbooktxt(font),
        handbooktxtshadow(font)
    {
        title = maketext(55, sf::Color(170, 100, 255), "WORLDS OF BLOCKMAN", font, sf::Vector2f(width/2, 100));
        titleshadow = textshadow(235, 6, title);

        starttxt = maketext(35, sf::Color(170, 100, 255), "PLAY", font, sf::Vector2f(width/2, 450));
        startbtn = makebtn(sf::Vector2f(starttxt.getLocalBounds().size.x*2, starttxt.getLocalBounds().size.y*2.5), sf::Color(100, 30, 155), sf::Vector2f(width/2, 450));
        starttxtshadow = textshadow(120, 3, starttxt);
        startbtnshadow = rectshadow(235, 6, startbtn);

        creditstxt = maketext(25, sf::Color(255, 20, 50), "CREDITS", font, sf::Vector2f(490, 550));
        creditsbtn = makebtn(sf::Vector2f(creditstxt.getLocalBounds().size.x*1.5, creditstxt.getLocalBounds().size.y*2.5), sf::Color(115, 0, 0), sf::Vector2f(490, 550));
        creditstxtshadow = textshadow(120, 3, creditstxt);
        creditsbtnshadow = rectshadow(235, 6, creditsbtn);

        settingstxt = maketext(25, sf::Color(20, 255, 50), "SETTINGS", font, sf::Vector2f(790, 550));
        settingsbtn = makebtn(sf::Vector2f(creditstxt.getLocalBounds().size.x*1.5, creditstxt.getLocalBounds().size.y*2.5), sf::Color(0, 115, 0), sf::Vector2f(790, 550));
        settingstxtshadow = textshadow(120, 3, settingstxt);
        settingsbtnshadow = rectshadow(235, 6, settingsbtn);

        handbooktxt = maketext(25, sf::Color(20, 50, 255), "HANDBOOK", font, sf::Vector2f(640, 550));
        handbookbtn = makebtn(sf::Vector2f(creditstxt.getLocalBounds().size.x*1.5, creditstxt.getLocalBounds().size.y*2.5), sf::Color(0, 0, 115), sf::Vector2f(640, 550));
        handbooktxtshadow = textshadow(120, 3, handbooktxt);
        handbookbtnshadow = rectshadow(235, 6, handbookbtn);
    }

    void play (sf::RenderWindow& window) {
        sf::Vector2i mouse_ = sf::Mouse::getPosition(window);
        sf::Vector2f mousepos = sf::Vector2f((float)mouse_.x, (float)mouse_.y);
        if (startbtn.getGlobalBounds().contains(mousepos)) {
            starttxt.setFillColor(sf::Color(255, 170, 30));
            startbtn.setFillColor(sf::Color(185, 100, 30));
            starttxt.setPosition(sf::Vector2f(640, 453));
            startbtn.setPosition(sf::Vector2f(640, 453));
            starttxtshadow.setPosition(sf::Vector2f(643, 456));
            startbtnshadow.setPosition(sf::Vector2f(643, 456));
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) state = State::levelselect;
        }
        else { 
            starttxt.setFillColor(sf::Color(170, 100, 255));
            startbtn.setFillColor(sf::Color(100, 30, 155));
            starttxt.setPosition(sf::Vector2f(640, 450));
            startbtn.setPosition(sf::Vector2f(640, 450));
            starttxtshadow.setPosition(sf::Vector2f(643, 453));
            startbtnshadow.setPosition(sf::Vector2f(646, 456));
        }

        if (creditsbtn.getGlobalBounds().contains(mousepos)) {
            creditstxt.setFillColor(sf::Color(100, 0, 0));
            creditsbtn.setFillColor(sf::Color(180, 180, 180));
            creditstxt.setPosition(sf::Vector2f(490, 553));
            creditsbtn.setPosition(sf::Vector2f(490, 553));
            creditstxtshadow.setPosition(sf::Vector2f(493, 556));
            creditsbtnshadow.setPosition(sf::Vector2f(493, 556));
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) state = State::credits;
        }
        else { 
            creditstxt.setFillColor(sf::Color(255, 20, 50));
            creditsbtn.setFillColor(sf::Color(115, 0, 0));
            creditstxt.setPosition(sf::Vector2f(490, 550));
            creditsbtn.setPosition(sf::Vector2f(490, 550));
            creditstxtshadow.setPosition(sf::Vector2f(493, 553));
            creditsbtnshadow.setPosition(sf::Vector2f(496, 556));
        }

        if (handbookbtn.getGlobalBounds().contains(mousepos)) {
            handbooktxt.setFillColor(sf::Color(0, 0, 100));
            handbookbtn.setFillColor(sf::Color(180, 180, 180));
            handbooktxt.setPosition(sf::Vector2f(640, 553));
            handbookbtn.setPosition(sf::Vector2f(640, 553));
            handbooktxtshadow.setPosition(sf::Vector2f(643, 556));
            handbookbtnshadow.setPosition(sf::Vector2f(643, 556));
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) state = State::handbook;
        }
        else { 
            handbooktxt.setFillColor(sf::Color(20, 50, 255));
            handbookbtn.setFillColor(sf::Color(0, 0, 115));
            handbooktxt.setPosition(sf::Vector2f(640, 550));
            handbookbtn.setPosition(sf::Vector2f(640, 550));
            handbooktxtshadow.setPosition(sf::Vector2f(643, 553));
            handbookbtnshadow.setPosition(sf::Vector2f(646, 556));
        }

        if (settingsbtn.getGlobalBounds().contains(mousepos)) {
            settingstxt.setFillColor(sf::Color(0, 70, 0));
            settingsbtn.setFillColor(sf::Color(180, 180, 180));
            settingstxt.setPosition(sf::Vector2f(790, 553));
            settingsbtn.setPosition(sf::Vector2f(790, 553));
            settingstxtshadow.setPosition(sf::Vector2f(793, 556));
            settingsbtnshadow.setPosition(sf::Vector2f(793, 556));
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) state = State::settings;
        }
        else { 
            settingstxt.setFillColor(sf::Color(20, 255, 50));
            settingsbtn.setFillColor(sf::Color(0, 115, 0));
            settingstxt.setPosition(sf::Vector2f(790, 550));
            settingsbtn.setPosition(sf::Vector2f(790, 550));
            settingstxtshadow.setPosition(sf::Vector2f(793, 553));
            settingsbtnshadow.setPosition(sf::Vector2f(796, 556));
        }
    }

    void draw (sf::RenderWindow& window) {
        window.draw(titleshadow);
        window.draw(title);
        window.draw(startbtnshadow);
        window.draw(startbtn);
        window.draw(starttxtshadow);
        window.draw(starttxt);
        window.draw(creditsbtnshadow);
        window.draw(creditsbtn);
        window.draw(creditstxtshadow);
        window.draw(creditstxt);
        window.draw(settingsbtnshadow);
        window.draw(settingsbtn);
        window.draw(settingstxtshadow);
        window.draw(settingstxt);
        window.draw(handbookbtnshadow);
        window.draw(handbookbtn);
        window.draw(handbooktxtshadow);
        window.draw(handbooktxt);
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
        level = maketext(35, sf::Color(255, 45, 200, levelshade), "Level "+std::to_string(setnum*6+levelnum+1), font, sf::Vector2f(width/2, 60));
    }

    void draw (sf::RenderWindow& window) {
        level.setString("Level "+std::to_string(setnum*6+levelnum+1));
        sf::Vector2i mouse_ = sf::Mouse::getPosition(window);
        if (mouse_.y >= 200 && levelshade > 0) levelshade -= 3;
        else if (mouse_.y < 200 && levelshade < 225) levelshade += 3;
        level.setFillColor(sf::Color(255, 45, 200, levelshade));
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
        paused = maketext(40, sf::Color(170, 170, 80), "PAUSED", font, sf::Vector2f(width/2, 295));
        resumetxt = maketext(25, sf::Color(80, 210, 145), "SPACE TO RESUME", font, sf::Vector2f(width/2, 395));
        exittxt = maketext(25, sf::Color(145, 80, 210), "ESCAPE TO EXIT", font, sf::Vector2f(width/2, 445));

        resumebtn.setSize(sf::Vector2f(resumetxt.getLocalBounds().size.x*1.2, resumetxt.getLocalBounds().size.y*2));
        resumebtn.setFillColor(sf::Color(10, 140, 75));
        resumebtn.setOrigin(sf::Vector2f(resumebtn.getLocalBounds().position.x + resumebtn.getLocalBounds().size.x/2, resumebtn.getLocalBounds().position.y + resumebtn.getLocalBounds().size.y/2));
        resumebtn.setPosition(sf::Vector2f(width/2, 395));

        exitbtn.setSize(sf::Vector2f(resumetxt.getLocalBounds().size.x*1.2, resumetxt.getLocalBounds().size.y*2));
        exitbtn.setFillColor(sf::Color(75, 10, 140));
        exitbtn.setOrigin(sf::Vector2f(exitbtn.getLocalBounds().position.x + exitbtn.getLocalBounds().size.x/2, exitbtn.getLocalBounds().position.y + exitbtn.getLocalBounds().size.y/2));
        exitbtn.setPosition(sf::Vector2f(width/2, 445));   
        
        resumetxtshadow = textshadow(120, 3, resumetxt);
        exittxtshadow = textshadow(120, 3, exittxt);
        resumebtnshadow = rectshadow(235, 6, resumebtn);
        exitbtnshadow = rectshadow(235, 6, exitbtn);
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
    sf::Text gorightshadow;
    sf::Text goleftshadow;
    sf::Text setshadow;
    sf::RectangleShape rightbtnshadow;
    sf::RectangleShape leftbtnshadow;
    int page = 0;
    sf::Text levelnums[6];
    sf::Text numshadows[6];
    sf::RectangleShape levelbtns[6];
    sf::RectangleShape btnshadows[6];

    levelselect() :
        font("AldotheApache.ttf"),
        goright(font),
        gorightshadow(font),
        goleft(font),
        goleftshadow(font),
        set(font),
        setshadow(font),
        levelnums{font, font, font, font, font, font},
        numshadows{font, font, font, font, font, font}
    {
        goright = maketext(30, sf::Color(140, 225, 10), ">", font, sf::Vector2f(1180, height/2));
    
        goleft = maketext(30, sf::Color(140, 225, 10), "<", font, sf::Vector2f(100, height/2));

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

        set = maketext(45, sf::Color(120, 100, 190), "set" + std::to_string(page+1), font, sf::Vector2f(width/2, 100));

        gorightshadow = textshadow(120, 2, goright);
        goleftshadow = textshadow(120, 2, goleft);
        rightbtnshadow = rectshadow(235, 6, gorightbtn);
        leftbtnshadow = rectshadow(235, 6, goleftbtn);
        setshadow = textshadow(235, 6, set);

        for (int i = 0; i < 6; i++) {
            levelnums[i].setCharacterSize(45);
            levelnums[i].setFillColor(sf::Color(0, 100, 240));
            levelbtns[i].setSize(sf::Vector2f(70, 70));
            levelbtns[i].setFillColor(sf::Color(0, 150, 250));
            levelbtns[i].setOrigin(sf::Vector2f(levelbtns[i].getLocalBounds().position.x + levelbtns[i].getLocalBounds().size.x/2, levelbtns[i].getLocalBounds().position.y + levelbtns[i].getLocalBounds().size.y/2));
        }
    }

    void draw (sf::RenderWindow& window) {
        set.setString("set " + std::to_string(page+1));
        setshadow.setString("set " + std::to_string(page+1));
        window.draw(setshadow);
        window.draw(set);
        window.draw(rightbtnshadow);
        window.draw(gorightbtn);
        window.draw(gorightshadow);
        window.draw(goright);
        window.draw(leftbtnshadow);
        window.draw(goleftbtn);
        window.draw(goleftshadow);
        window.draw(goleft);
        for (int i = 0; i < 6; i++) {
            window.draw(btnshadows[i]);
            window.draw(levelbtns[i]);
            window.draw(numshadows[i]);
            window.draw(levelnums[i]);
        }
    }

    void select(sf::RenderWindow& window) {
        for (int i = 0; i < 6; i++) {
            int levelnumber = page * 6 + i + 1;
            sf::Vector2f numpos;
            if (i < 3) numpos = sf::Vector2f(400 * i + 240, 250);
            else numpos = sf::Vector2f(400 * (i-3) + 240, 470);

            levelnums[i] = maketext(45, sf::Color(0, 100, 240), std::to_string(levelnumber), font, numpos);

            if (i < 3) levelbtns[i].setPosition(sf::Vector2f(400 * i + 240, 250));
            else levelbtns[i].setPosition(sf::Vector2f(400 * (i-3) + 240, 470));

            numshadows[i] = textshadow(120, 3, levelnums[i]);
            btnshadows[i] = rectshadow(215, 5, levelbtns[i]);
        }
        
        sf::Vector2i mouse_ = sf::Mouse::getPosition(window);
        sf::Vector2f mousepos = sf::Vector2f((float)mouse_.x, (float)mouse_.y);
        if (gorightbtn.getGlobalBounds().contains(mousepos)) {
            gorightbtn.setFillColor(sf::Color(200, 80, 0));
            goright.setFillColor(sf::Color(255, 120, 0));
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !mouseheld && page < 4) {
                page += 1;
                mouseheld = true;
            } 
        } else {
            gorightbtn.setFillColor(sf::Color(240, 255, 80));
            goright.setFillColor(sf::Color(140, 255, 10));
        }
        if (goleftbtn.getGlobalBounds().contains(mousepos)) {
            goleftbtn.setFillColor(sf::Color(200, 80, 0));
            goleft.setFillColor(sf::Color(255, 120, 0));
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !mouseheld && page > 0) {
                page -= 1;
                mouseheld = true;
            } 
        } else {
            goleftbtn.setFillColor(sf::Color(240, 255, 80));
            goleft.setFillColor(sf::Color(140, 255, 10));
        }

        for (int i = 0; i < 6; i++) {
            if (levelbtns[i].getGlobalBounds().contains(mousepos) && !mouseheld) {
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
    }
};

class settings {
public:
    sf::Font font;
    sf::Text settingstxt;
    sf::Text settingstxtshadow;

    settings () :
        font("AldotheApache.ttf"),
        settingstxt(font),
        settingstxtshadow(font)
    {
        settingstxt = maketext(45, sf::Color(170, 255, 80), "SETTINGS", font, sf::Vector2f(width/2, 190));
        settingstxtshadow = textshadow(235, 6, settingstxt);
    }

    void draw (sf::RenderWindow& window) {
        window.draw(settingstxtshadow);
        window.draw(settingstxt);
    }
};

class credits {
    
};

class handbook {

};