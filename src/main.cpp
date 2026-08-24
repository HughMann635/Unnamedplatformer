#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>

#include "states.h"
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
	sf::Vector2f lastframe_pos;
	sf::Vector2f lastframe_vel;
	sf::Clock timer;
	sf::Vector2f edge;
	sf::RenderTexture env (sf::Vector2u(width, height));
	sf::Sprite envsprite (env.getTexture());

	sf::View view;
	view.setSize(sf::Vector2f(camwidth, camheight));
	view.setCenter(sf::Vector2f(currentplayer -> shape().getPosition().x, currentplayer -> shape().getPosition().y));

	sky.makestars(stars);

	while (window.isOpen()) {
		float deltatime = timer.restart().asSeconds();
		
		while ( const std::optional event = window.pollEvent() ) if ( event->is<sf::Event::Closed>() || running == false) window.close();

		window.clear();

		if (state == State::playing) {
			menuenter = false;
			if (!gamestart) {
				map.statictilelist.clear();
				map.dynamictilelist.clear();
				map.envtilelist.clear();
				map.loadmap(levels[setnum][levelnum], levels_env[setnum][levelnum]);
				currentplayer -> shape().setPosition(map.spawn);
				currentplayer -> shape().setRotation(sf::degrees(0));
				currentplayer -> rotation = 0;
				currentplayer -> freefallingtip = false;
				tipping_right = false;
				tipping_left = false;
				
				env.clear(sf::Color::Transparent);
				map.drawenv(env);
				env.display();
				envsprite.setTexture((env.getTexture()));
				gamestart = true;
			}
			
			if (restart == true) {
				map.statictilelist.clear();
				map.dynamictilelist.clear();
				map.envtilelist.clear();
				map.loadmap(levels[setnum][levelnum], levels_env[setnum][levelnum]);
				env.clear(sf::Color::Transparent);
				map.drawenv(env);
				env.display();
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
			} 
			if (newlevel == true) {
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
			
			if (setnum >= 1) circlelocked = false;
			if (setnum >= 2) octagonlocked = false;
			if (setnum >= 3) trianglelocked = false;
			if (setnum >= 4) hexagonlocked = false;

			//TO DO: FIND WAY TO MAKE LVL 17 MORE EFFICIENT
			//RIGHT NOW IT DRAWS 1K+ TILES WHICH IS VERY INEFFICIENT
			//possible solution: split drawmap into drawmap for dynamics and drawenv for statics
			//and add render caching for static tiles
	
			swapped = false;
			if (currentplayer -> grounded) jumpcount = 2;
			currentplayer -> jump(deltatime);
			blockonhead = false;
			currentplayer -> grounded = false;
			if (!inblackhole && currentplayer -> shape().getPosition().y < 730) currentplayer -> updatepos(deltatime, map);
			if (currentplayer -> shape().getPosition().y >= 730) currentplayer -> shape().move(sf::Vector2f(0, currentplayer -> velocity.y*deltatime));
			if (currentplayer -> shape().getPosition().y > 1000) restart = true;
			map.updatemap(deltatime);
			inblackhole = false;
			map.checkCollisions(*currentplayer, deltatime);
			currentplayer -> rotateobject(edge, map, currentplayer -> shape(), deltatime, movespeed, swimming, zerogactive, currentplayer -> grounded, nearestedge);
			lastframe_pos = sf::Vector2f(currentplayer -> shape().getPosition());
			lastframe_vel = sf::Vector2f(currentplayer -> velocity);
	
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) restart = true;
	
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1) && !dynamic_cast<square*>(currentplayer.get())) { 
				currentplayer = std::make_unique<square>(); 
				swapped = true; 
				nearestedge = 90.f; 
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2) && !dynamic_cast<circle*>(currentplayer.get()) && !circlelocked) { 
				currentplayer = std::make_unique<circle>(); 
				swapped = true; 
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3) && !dynamic_cast<octagon*>(currentplayer.get()) && !octagonlocked) { 
				currentplayer = std::make_unique<octagon>(); 
				swapped = true; 
				nearestedge = 45.f; 
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4) && !dynamic_cast<triangle*>(currentplayer.get()) && !trianglelocked) { 
				currentplayer = std::make_unique<triangle>(); 
				swapped = true; 
				nearestedge = 120.f; 
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num5) && !dynamic_cast<hexagon*>(currentplayer.get()) && !hexagonlocked) { 
				currentplayer = std::make_unique<hexagon>(); 
				swapped = true; 
				nearestedge = 60.f; 
			}
			
			if (swapped) {
				currentplayer -> shape().setPosition(lastframe_pos);
				currentplayer -> velocity = lastframe_vel;
			}
			
			window.clear();
			window.setView(view);
			sky.drawsky(window);
			sky.drawstars(window);
			currentplayer -> drawscreen(window);
			map.drawmap(window);
			window.draw(envsprite);
			window.setView(window.getDefaultView());
			gameui.draw(window);
			window.setView(view);
			if (!esckeyheld) gameui.checkexit();

			//CAM SETTINGS
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
			gamestart = false;
			if (!menuenter) {
				map.statictilelist.clear();
				map.dynamictilelist.clear();
				map.envtilelist.clear();
				map.loadmap(menulevel, levels_env[0][0]);
				currentplayer -> shape().setPosition(map.spawn);
				map.drawmap(window);
				currentplayer -> drawscreen(window);
				menuenter = true;
			}
			sky.drawsky(window);
			sky.drawstars(window);
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
			if (!esckeyheld) menu.play(window);
		} else if (state == State::pause) {
			sky.drawsky(window);
			sky.drawstars(window);
			map.drawmap(window);
			currentplayer -> drawscreen(window);
			window.setView(window.getDefaultView());
			sf::RectangleShape pauseblur(sf::Vector2f(width, height));
			pauseblur.setFillColor(sf::Color(0, 0, 0, 135));
			window.draw(pauseblur);
			pausemenu.draw(window); 
			window.setView(view);
			if (!esckeyheld) pausemenu.checkaction();
		}

		window.display();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) esckeyheld = true;
		else esckeyheld = false;
	}
}