#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <algorithm>

#include "players.h"
#include "tiletypes.h"
#include "scenes.h"
#include "ui.h"
#include "vars.h"
#include "tilesettings.h"
#include "tilemap.h"
#include "collision.h"

int main()
{
	sf::RenderWindow window( sf::VideoMode( { width, height } ), title );
	window.setFramerateLimit(120);

	std::unique_ptr<player> currentplayer = std::make_unique<square>();
	sky sky;
	tilemap map;
	mainmenu menu;
	playing gameui;
	pause pausemenu;
	levelselect lvlselect; 
	settings settings;
	credits credits;
	handbook handbook;
	menuswitch menuswitch;
	sf::Vector2f lastframe_pos;
	sf::Vector2f lastframe_vel;
	sf::Clock timer;
	sf::Vector2f edge;
	sf::RenderTexture env (sf::Vector2u(width, height));
	sf::Sprite envsprite (env.getTexture());
	sf::Clock background_lapse;
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("clicksound1.wav")) {
		std::cout << "Couldn't load file";
	}
	sf::Sound clicksound (buffer); 
	sf::Listener::setGlobalVolume(volumelevel*15);
	clicksound.setVolume(sf::Listener::getGlobalVolume());

	sf::View view;
	view.setSize(sf::Vector2f(camwidth, camheight));
	view.setCenter(sf::Vector2f(currentplayer -> shape().getPosition().x, currentplayer -> shape().getPosition().y));


	//BUGS!!!!!
	//rotation bugs
	//levels 13, 17, 26, 4, 8, look into
	//as well as other levels but these ones I can remember
	//ISSUES WITH WALKING THRU ONE TILE GAPS
	//YOU CANT FALL TO DEATH: YOURE STUCK BELOW SCREEN IF YOU FALL
	

	//TO ADD!!!!!
	//updating handbook (notif icon, hidden objects)
	//more sfx (death especially)
	

	//RETURNING TO OLD LEVELS - mainly done
	//but if you switch to a mroe advanced shape for a set that shouldn't have it the timer
	//- will change color -> red
	//- nullify the pb for that run


	while (window.isOpen()) {
		float deltatime = timer.restart().asSeconds();
		
		while ( const std::optional event = window.pollEvent() ) {
			if ( event->is<sf::Event::Closed>() || running == false) { window.close(); }
		}

		window.clear();

		window.setView(window.getDefaultView());
		sky.drawsky(window, view.getCenter());
		sky.updatesky(deltatime);
		if (state == State::playing) {
			window.setView(window.getDefaultView());
			window.setView(view);
			menuenter = false;
			if (!gamestart) {
				map.statictilelist.clear();
				map.dynamictilelist.clear();
				map.envtilelist.clear();
				map.loadmap(levels[setnum][levelnum], levels_env[setnum][levelnum]);
				currentplayer = std::make_unique<square>();
				currentplayer -> velocity = sf::Vector2f(0, 0);
				currentplayer -> shape().setPosition(map.spawn);
				currentplayer -> shape().setRotation(sf::degrees(0));
				currentplayer -> freefallingtip = false;
				tipping_right = false;
				tipping_left = false;
				
				env.clear(sf::Color::Transparent);
				map.drawenv(env);
				env.display();
				envsprite.setTexture((env.getTexture()));
				leveltimer.restart();
				gamestart = true;
			}
			if (restart) {
				if (currentplayer -> shape().getFillColor().a > 0) {
					currentplayer -> shape().setFillColor(sf::Color(currentplayer->shape().getFillColor().r, currentplayer->shape().getFillColor().g, currentplayer->shape().getFillColor().b, currentplayer->shape().getFillColor().a - (3)));
				} else {
					leveltimer.restart();
					deathcount += 1;
					map.statictilelist.clear();
					map.dynamictilelist.clear();
					map.envtilelist.clear();
					map.loadmap(levels[setnum][levelnum], levels_env[setnum][levelnum]);
					env.clear(sf::Color::Transparent);
					map.drawenv(env);
					env.display();
					tp_timer.restart();
					triangleshade = 255;
					tped = false;
					currentplayer = std::make_unique<square>();
					currentplayer -> shape().setPosition(map.spawn);
					currentplayer -> velocity = sf::Vector2f(0.f, 0.f);
					currentplayer -> shape().setRotation(sf::degrees(0));
					currentplayer -> rotation = 0;
					currentplayer -> freefallingtip = false;
					tipping_right = false;
					tipping_left = false;
					gravity = 1800.f;
					restart = false;
					restarted = false;
				}
			} 
			if (newlevel) {
				if (pbs[setnum*6+levelnum] > leveltimer.getElapsedTime().asMilliseconds() || pbs[setnum*6+levelnum] == 0) pbs[setnum*6+levelnum] = leveltimer.getElapsedTime().asMilliseconds();
				completed[setnum*6+levelnum] = 1;
				unlocked[setnum*6+levelnum+1] = 1;
				if ((setnum*6+levelnum+1) % 6 == 0) newnotif = true;
				else newnotif = false;
				levelnum += 1;
				if (levelnum > 5) {
					state = State::mainmenu;
					levelnum = 0;
					if (setnum == 4) {
						std::cout << "Congrats!";
						window.close();
					}
					else setnum += 1;
				}
				
				map.statictilelist.clear();
				map.dynamictilelist.clear();
				map.envtilelist.clear();
				currentplayer = std::make_unique<square>();
				map.loadmap(levels[setnum][levelnum], levels_env[setnum][levelnum]);
				env.clear(sf::Color::Transparent);
				map.drawenv(env);
				env.display();
				sf::Sprite envsprite(env.getTexture());
				tped = false;
				tp_timer.restart();
				leveltimer.restart();
				triangleshade = 255;
				currentplayer -> shape().setPosition(map.spawn);
				currentplayer -> velocity = sf::Vector2f(0.f, 0.f);
				gravity = 1800.f;
				currentplayer -> shape().setRotation(sf::degrees(0));
				currentplayer -> rotating = false;
				currentplayer -> freefallingtip = false;
				tipping_right = false;
				tipping_left = false;
				newlevel = false;
			} 
			
			circlelocked = false;
			octagonlocked = false;
			trianglelocked = false;
			hexagonlocked = false;
			
			for (int i = 0; i < 6; i++) { 
				if (completed[6+i] == 0 && !(setnum >= 1)) {
					circlelocked = true;
				}
				if (completed[12+i] == 0 && !(setnum >= 2)) {
					octagonlocked = true;
				}
				if (completed[18+i] == 0 && !(setnum >= 3)) {
					trianglelocked = true;
				}
				if (completed[24+i] == 0 && !(setnum >= 4)) {
					hexagonlocked = true;
				}
			}
	
			swapped = false;
			if (currentplayer -> grounded) jumpcount = 2;
			currentplayer -> jump(deltatime);
			blockonhead = false;
			currentplayer -> grounded = false;
			if (!inblackhole && currentplayer -> shape().getPosition().y < 730 && !restart) currentplayer -> updatepos(deltatime, map);
			if (restart && currentplayer -> shape().getPosition().y) currentplayer -> shape().move(sf::Vector2f(currentplayer -> velocity.x*deltatime*0.05, currentplayer -> velocity.y*deltatime*0.05));
			if (currentplayer -> shape().getPosition().y > 730) restart = true;
			map.updatemap(deltatime);
			inblackhole = false;
			map.checkCollisions(*currentplayer, deltatime);
			if (!restart) currentplayer -> rotateobject(edge, map, currentplayer -> shape(), deltatime, movespeed, swimming, zerogactive, currentplayer -> grounded, nearestedge);
			lastframe_pos = sf::Vector2f(currentplayer -> shape().getPosition());
			lastframe_vel = sf::Vector2f(currentplayer -> velocity);
	
			if (keypressed(Action::restart)) { 
				restart = true;
				restarted = true;
			}

			if (keypressed(Action::switch1) && !dynamic_cast<square*>(currentplayer.get()) && !restart) { 
				currentplayer = std::make_unique<square>(); 
				swapped = true; 
				nearestedge = 90.f; 
			}
			else if (keypressed(Action::switch2) && !dynamic_cast<circle*>(currentplayer.get()) && !circlelocked && !restart) { 
				currentplayer = std::make_unique<circle>(); 
				swapped = true; 
			}
			else if (keypressed(Action::switch3) && !dynamic_cast<octagon*>(currentplayer.get()) && !octagonlocked && !restart) { 
				currentplayer = std::make_unique<octagon>(); 
				swapped = true; 
				nearestedge = 45.f; 
			}
			else if (keypressed(Action::switch4) && !dynamic_cast<triangle*>(currentplayer.get()) && !trianglelocked && !restart) { 
				currentplayer = std::make_unique<triangle>(); 
				swapped = true; 
				nearestedge = 120.f; 
			}
			else if (keypressed(Action::switch5) && !dynamic_cast<hexagon*>(currentplayer.get()) && !hexagonlocked && !restart) { 
				currentplayer = std::make_unique<hexagon>(); 
				swapped = true; 
				nearestedge = 60.f; 
			}
			
			if (swapped) {
				currentplayer -> shape().setPosition(lastframe_pos);
				currentplayer -> velocity = lastframe_vel;
			}
			
			window.setView(view);
			
			currentplayer -> drawscreen(window);
			map.drawmap(window);
			window.draw(envsprite);
			window.setView(window.getDefaultView());
			gameui.draw(window);
			window.setView(view);
			if (!esckeyheld) gameui.checkexit(window, clicksound);

			if (currentplayer -> shape().getPosition().x < camwidth/2.f) {
				if (currentplayer -> shape().getPosition().y < camheight/2.f) {
					view.setCenter(sf::Vector2f(camwidth/2.f, camheight/2.f));
				} else if (currentplayer -> shape().getPosition().y > height-camheight/2.f) {
					view.setCenter(sf::Vector2f(camwidth/2.f, height-camheight/2.f));
				} else {
					view.setCenter(sf::Vector2f(camwidth/2.f, currentplayer -> shape().getPosition().y));
				}
			} else if (currentplayer -> shape().getPosition().x > width-camwidth/2.f) {
				if (currentplayer -> shape().getPosition().y < camheight/2.f) {
					view.setCenter(sf::Vector2f(width-camwidth/2.f, camheight/2.f));
				} else if (currentplayer -> shape().getPosition().y > height-camheight/2.f) {
					view.setCenter(sf::Vector2f(width-camwidth/2.f, height-camheight/2.f));
				} else {
					view.setCenter(sf::Vector2f(width-camwidth/2.f, currentplayer -> shape().getPosition().y));
				}
			} else {
				if (currentplayer -> shape().getPosition().y < camheight/2.f) {
					view.setCenter(sf::Vector2f(currentplayer -> shape().getPosition().x, camheight/2.f));
				} else if (currentplayer -> shape().getPosition().y > height-camheight/2.f) {
					view.setCenter(sf::Vector2f(currentplayer -> shape().getPosition().x, height-camheight/2.f));
				} else {
					view.setCenter(sf::Vector2f(currentplayer -> shape().getPosition().x, currentplayer -> shape().getPosition().y));
				}
			}
			
		} else if (state == State::mainmenu) {
			handbookenter = false;
			gamestart = false;
			if (!menuenter || restart) {
				map.statictilelist.clear();
				map.dynamictilelist.clear();
				map.envtilelist.clear();
				map.loadmap(menulevel, levels_env[0][0]);
				currentplayer -> shape().setPosition(map.spawn);
				map.drawmap(window);
				currentplayer -> drawscreen(window);
				menuenter = true;
			}
			restart = false;
			swapped = false;
			if (currentplayer -> grounded) jumpcount = 2;
			currentplayer -> jump(deltatime);
			currentplayer -> grounded = false;
			currentplayer -> updatepos(deltatime, map);
			map.updatemap(deltatime);
			map.checkCollisions(*currentplayer, deltatime);
			currentplayer -> rotateobject(edge, map, currentplayer -> shape(), deltatime, movespeed, swimming, zerogactive, currentplayer -> grounded, nearestedge);
			map.drawmap(window);
			currentplayer -> drawscreen(window);
			window.setView(window.getDefaultView());
			menu.draw(window);
			if (!esckeyheld) menu.play(window, clicksound);
		} else if (state == State::pause) {
			window.setView(view);
			map.drawmap(window);
			currentplayer -> drawscreen(window);
			map.drawenv(window);
			window.setView(window.getDefaultView());
			sf::RectangleShape pauseblur(sf::Vector2f(width, height));
			pauseblur.setFillColor(sf::Color(0, 0, 0, 135));
			window.draw(pauseblur);
			pausemenu.draw(window); 
			window.setView(view);
			if (!esckeyheld) pausemenu.checkaction(window, clicksound);
		} else if (state == State::levelselect) {
			if (menu.navback(window, clicksound)) state = State::mainmenu;
			map.drawmap(window);
			window.setView(window.getDefaultView());
			lvlselect.select(window, clicksound);
			lvlselect.draw(window);
		} else if (state == State::credits) {
			if (menu.navback(window, clicksound)) state = State::mainmenu;
			map.drawmap(window);
			window.setView(window.getDefaultView());
			credits.draw(window);
			credits.update(window);
		} else if (state == State::handbook) {
			if (menu.navback(window, clicksound)) state = State::mainmenu;
			if (!handbookenter) {
				handbook.tilename = maketext(35, sf::Color(255, 40, 60), "SELECT A TILE", handbook.font, sf::Vector2f(640, 370));
            	handbook.tiledesc = maketext(25, sf::Color(255, 40, 60), "AND ITS DESCRIPTION WILL APPEAR HERE", handbook.font, sf::Vector2f(640, 450));
            	handbook.tilenameshadow = textshadow(120, 3, handbook.tilename);
            	handbook.tiledescshadow = textshadow(120, 3, handbook.tiledesc);
				handbookenter = true;
			}
			map.drawmap(window);
			window.setView(window.getDefaultView());
			handbook.update(window, deltatime, clicksound);
			handbook.draw(window);
		} else if (state == State::settings) {
			if (menu.navback(window, clicksound)) state = State::mainmenu;
			map.drawmap(window);
			window.setView(window.getDefaultView());
			settings.draw(window);
			settings.update(window, clicksound);
			while (const std::optional keychecker = window.pollEvent()) { 
				settings.keybind(window, *keychecker, clicksound);
				if (keychecker->is<sf::Event::Closed>()) window.close();
			}
		}
		menuswitch.fade(window, switched, targetstate);
		window.display();
		if (keypressed(Action::goback)) esckeyheld = true;
		else esckeyheld = false;
		sf::Listener::setGlobalVolume(volumelevel*15);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) mouseheld = true; 
		else mouseheld = false;
	}
}