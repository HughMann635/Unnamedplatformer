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
#include "sat(TESTING).h"

int main()
{
	sf::RenderWindow window( sf::VideoMode( { width, height } ), title );
	window.setFramerateLimit(120);

	std::unique_ptr<player> currentplayer = std::make_unique<square>();
	sky sky;
	tilemap map;
	sf::Vector2f lastframe_pos;
	sf::Vector2f lastframe_vel;
	sf::Clock timer;
	sf::Vector2f edge;

	sf::View view;
	view.setSize(sf::Vector2f(camwidth, camheight));
	view.setCenter(sf::Vector2f(currentplayer -> shape().getPosition().x, currentplayer -> shape().getPosition().y));

	sky.makestars(stars);

	map.loadmap(levels[setnum][levelnum]);
	currentplayer -> shape().setPosition(map.spawn);

	while (window.isOpen()) {
		float deltatime = timer.restart().asSeconds();
		
		if (restart == true) {
			map.statictilelist.clear();
			map.dynamictilelist.clear();
			map.loadmap(levels[setnum][levelnum]);
			currentplayer = std::make_unique<square>();
			currentplayer -> shape().setPosition(map.spawn);
			currentplayer -> velocity = sf::Vector2f(0.f, 0.f);
			gravity = 1800.f;
			restart = false;
		} 

		if (newlevel == true) {
			levelnum += 1;
			if (levelnum > 5) {
				levelnum = 0;
				if (setnum > 4) {
					std::cout << "Congrats!";
					window.close();
				}
				setnum += 1;
			}

			map.statictilelist.clear();
			map.dynamictilelist.clear();
			currentplayer = std::make_unique<square>();
			map.loadmap(levels[setnum][levelnum]);
			currentplayer -> shape().setPosition(map.spawn);
			currentplayer -> velocity = sf::Vector2f(0.f, 0.f);
			gravity = 1800.f;
			newlevel = false;
		} 

		while ( const std::optional event = window.pollEvent() ) if ( event->is<sf::Event::Closed>() || running == false) window.close();


		//WILL ADD BACK EXTRA CHECKCOLLISIONS LATER ONCE I MAKE IT MORE EFFICIENT


		swapped = false;
		currentplayer -> jump(deltatime);
		blockonhead = false;
		currentplayer -> grounded = false;
		currentplayer -> updatepos(deltatime, map);
		map.updatemap(deltatime);
		//NOTE TO SELF figure out a way to get multiple checkCollisions working
		//map.checkCollisions(*currentplayer);
		//map.checkCollisions(*currentplayer);
		map.checkCollisions(*currentplayer);
		currentplayer -> rotateobject(edge, map, currentplayer -> shape(), deltatime, movespeed, swimming, zerogactive, currentplayer -> grounded, nearestedge);
		lastframe_pos = sf::Vector2f(currentplayer -> shape().getPosition());
		lastframe_vel = sf::Vector2f(currentplayer -> velocity);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) restart = true;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1) && !dynamic_cast<square*>(currentplayer.get())) { 
			currentplayer = std::make_unique<square>(); 
			swapped = true; 
			nearestedge = 90.f; 
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2) && !dynamic_cast<circle*>(currentplayer.get())) { 
			currentplayer = std::make_unique<circle>(); 
			swapped = true; 
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3) && !dynamic_cast<triangle*>(currentplayer.get())) { 
			currentplayer = std::make_unique<triangle>(); 
			swapped = true; 
			nearestedge = 120.f; 
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4) && !dynamic_cast<hexagon*>(currentplayer.get())) { 
			currentplayer = std::make_unique<hexagon>(); 
			swapped = true; 
			nearestedge = 60.f; 
			jumpcount = 1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num5) && !dynamic_cast<octagon*>(currentplayer.get())) { 
			currentplayer = std::make_unique<octagon>(); 
			swapped = true; 
			nearestedge = 45.f; 
		}
		
		if (swapped) {
			currentplayer -> shape().setPosition(lastframe_pos);
			currentplayer -> velocity = lastframe_vel;
		}
		
		//SAT COLLISION STUFF
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) enterkeyheld = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) && !enterkeyheld) {
			auto verticeslist = getvertices(currentplayer -> shape());
			for (auto& pos: verticeslist) std::cout << pos.x << "," << pos.y << "\n";
			for (auto& pos: map.dynamictilelist) {
				if (pos.type == tiletype::block_push) {
					block* G = dynamic_cast<block*>(pos.tile.get());
					auto verticeslist = getvertices(G -> blockblock);
					std::cout << "ALL PUSHBLOCK COORDS\n";
					for (auto& rest: verticeslist) std::cout << rest.x << "," << rest.y << "\n";
					std::cout << "Y-VELOCITY = " << G -> velocity.y << "\n";
				}
			}
			enterkeyheld = false;
		}

		window.clear();
		window.setView(view);
		sky.drawsky(window);
		sky.drawstars(window);
		currentplayer -> drawscreen(window);
		map.drawmap(window);
		
		//DEBUG DRAWING STUFF
		if (draw) {
			auto playervertices = getvertices(currentplayer->shape());
			sf::Vector2f center = sf::Vector2f(0, 0);
			for (const auto& pos : playervertices) center += pos;
    		center /= static_cast<float>(playervertices.size());
			std::vector<sf::Vector2f> closestvertices;
    		float closestdist = std::numeric_limits<float>::max();

			for (auto& pos : map.statictilelist) {
				std::vector<sf::Vector2f> tilevertices;
				if (pos.type == tiletype::lava) {
					lava* G = dynamic_cast<lava*>(pos.tile.get());
					if (G) tilevertices = getvertices(G->lavablock);
					drawdebug(window, tilevertices, tilevertices);
				}
				else if (pos.type == tiletype::spike) {
					spike* G = dynamic_cast<spike*>(pos.tile.get());
					if (G) tilevertices = getvertices(G->spikeblock);
					drawdebug(window, tilevertices, tilevertices);
				}
				else if (pos.type == tiletype::ground) {
					ground_* G = dynamic_cast<ground_*>(pos.tile.get());
					if (G) tilevertices = getvertices(G->ground_block);
				}
				sf::Vector2f tilecenter = sf::Vector2f(0, 0);
				for (auto& rest: tilevertices) tilecenter += rest;
				if (!tilevertices.empty()) {
					tilecenter /= static_cast<float>(tilevertices.size());
					float dist = (center.x - tilecenter.x) * (center.x - tilecenter.x) + (center.y - tilecenter.y) * (center.y - tilecenter.y);
					if (dist < closestdist) {
						closestdist = dist;
						closestvertices = tilevertices;
					}
				}
			}
			drawdebug(window, playervertices, closestvertices);
		}
		
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
		window.display();
	}
}