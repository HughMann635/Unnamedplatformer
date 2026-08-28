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

inline void btnpress (sf::RenderWindow& window, sf::Text& txt, sf::RectangleShape& btn, sf::Text& txtshade, sf::RectangleShape& btnshade, sf::Vector2f pos, sf::Color txtcolor, sf::Color btncolor, sf::Color txthover, sf::Color btnhover, State state_) {
    sf::Vector2f mousepos = window.mapPixelToCoords(sf::Mouse::getPosition(window), window.getDefaultView());
    if (btn.getGlobalBounds().contains(mousepos)) {
        txt.setFillColor(txthover);
        btn.setFillColor(btnhover);
        txt.setPosition(pos+sf::Vector2f(0, 3));
        btn.setPosition(pos+sf::Vector2f(0, 3));
        txtshade.setPosition(pos+sf::Vector2f(3, 6));
        btnshade.setPosition(pos+sf::Vector2f(3, 6));
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) state = state_;
    } else {
        txt.setFillColor(txtcolor);
        btn.setFillColor(btncolor);
        txt.setPosition(pos);
        btn.setPosition(pos);
        txtshade.setPosition(pos+sf::Vector2f(3, 3));
        btnshade.setPosition(pos+sf::Vector2f(6, 6));
    }
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
        btnpress(window, starttxt, startbtn, starttxtshadow, startbtnshadow, sf::Vector2f(640, 450), sf::Color(170, 100, 255), sf::Color(100, 30, 155), sf::Color(255, 170, 30), sf::Color(185, 100, 30), State::levelselect);
        btnpress(window, creditstxt, creditsbtn, creditstxtshadow, creditsbtnshadow, sf::Vector2f(490, 550), sf::Color(255, 20, 50), sf::Color(115, 0, 0), sf::Color(100, 0, 0), sf::Color(180, 180, 180), State::credits);
        btnpress(window, handbooktxt, handbookbtn, handbooktxtshadow, handbookbtnshadow, sf::Vector2f(640, 550), sf::Color(20, 50, 255), sf::Color(0, 0, 115), sf::Color(0, 0, 100), sf::Color(180, 180, 180), State::handbook);
        btnpress(window, settingstxt, settingsbtn, settingstxtshadow, settingsbtnshadow, sf::Vector2f(790, 550), sf::Color(20, 255, 50), sf::Color(0, 115, 0), sf::Color(0, 70, 0), sf::Color(180, 180, 180), State::settings);
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
    sf::Text pausedshadow;
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
        pausedshadow(font),
        resumetxt(font),
        exittxt(font),
        resumetxtshadow(font),
        exittxtshadow(font)
    {
        paused = maketext(40, sf::Color(170, 170, 80), "PAUSED", font, sf::Vector2f(width/2, 295));
        pausedshadow = textshadow(235, 6, paused);

        resumetxt = maketext(25, sf::Color(80, 210, 145), "SPACE TO RESUME", font, sf::Vector2f(width/2, 395));
        resumebtn = makebtn(sf::Vector2f(resumetxt.getLocalBounds().size.x*1.2, resumetxt.getLocalBounds().size.y*2), sf::Color(10, 140, 75), sf::Vector2f(width/2, 395));
        resumetxtshadow = textshadow(120, 3, resumetxt);
        resumebtnshadow = rectshadow(235, 6, resumebtn);

        exittxt = maketext(25, sf::Color(145, 80, 210), "ESCAPE TO EXIT", font, sf::Vector2f(width/2, 445));
        exitbtn = makebtn(sf::Vector2f(resumetxt.getLocalBounds().size.x*1.2, resumetxt.getLocalBounds().size.y*2), sf::Color(75, 10, 140), sf::Vector2f(width/2, 445));
        exittxtshadow = textshadow(120, 3, exittxt);
        exitbtnshadow = rectshadow(235, 6, exitbtn);
    }

    void draw (sf::RenderWindow& window) {
        window.draw(pausedshadow);
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
        btnpress(window, resumetxt, resumebtn, resumetxtshadow, resumebtnshadow, sf::Vector2f(width/2, 395), sf::Color(80, 210, 145), sf::Color(10, 145, 75), sf::Color(180, 200, 20), sf::Color(110, 130, 20), State::playing);
        btnpress(window, exittxt, exitbtn, exittxtshadow, exitbtnshadow, sf::Vector2f(width/2, 445), sf::Color(145, 80, 210), sf::Color(75, 10, 140), sf::Color(20, 120, 255), sf::Color(20, 50, 185), State::mainmenu);
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
        gorightbtn = makebtn(sf::Vector2f(40, 40), sf::Color(240, 255, 80), goright.getPosition());
        gorightshadow = textshadow(120, 2, goright);
        rightbtnshadow = rectshadow(235, 6, gorightbtn);
        
        goleft = maketext(30, sf::Color(140, 225, 10), "<", font, sf::Vector2f(100, height/2));
        goleftbtn = makebtn(sf::Vector2f(40, 40), sf::Color(240, 255, 80), goleft.getPosition());
        goleftshadow = textshadow(120, 2, goleft);
        leftbtnshadow = rectshadow(235, 6, goleftbtn);

        set = maketext(45, sf::Color(120, 100, 190), "set" + std::to_string(page+1), font, sf::Vector2f(width/2, 100));
        setshadow = textshadow(235, 6, set);

        update();
    }

    void draw (sf::RenderWindow& window) {
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

    void update() {
        set.setString("set " + std::to_string(page+1));
        setshadow.setString("set " + std::to_string(page+1));
        for (int i = 0; i < 6; i++) {
            int levelnumber = page * 6 + i + 1;
            sf::Vector2f numpos;
            if (i < 3) numpos = sf::Vector2f(400 * i + 240, 250);
            else numpos = sf::Vector2f(400 * (i-3) + 240, 470);

            levelnums[i] = maketext(45, sf::Color(0, 100, 240), std::to_string(levelnumber), font, numpos);
            levelbtns[i] = makebtn(sf::Vector2f(70, 70), sf::Color(0, 150, 250), numpos);
            numshadows[i] = textshadow(120, 3, levelnums[i]);
            btnshadows[i] = rectshadow(215, 5, levelbtns[i]);
        }
    }

    void select(sf::RenderWindow& window) {
        sf::Vector2i mouse_ = sf::Mouse::getPosition(window);
        sf::Vector2f mousepos = sf::Vector2f((float)mouse_.x, (float)mouse_.y);
        if (gorightbtn.getGlobalBounds().contains(mousepos)) {
            gorightbtn.setFillColor(sf::Color(200, 80, 0));
            goright.setFillColor(sf::Color(255, 120, 0));
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !mouseheld && page < 4) {
                page += 1;
                mouseheld = true;
                update();
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
                update();
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