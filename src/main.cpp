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

	sf::View view;
	view.setSize(sf::Vector2f(camwidth, camheight));
	view.setCenter(sf::Vector2f(currentplayer -> shape().getPosition().x, currentplayer -> shape().getPosition().y));

	sky.makestars(stars);

	map.loadmap(levels[setnum][levelnum]);
	currentplayer -> shape().setPosition(map.spawn);

	while (window.isOpen()) {
		float deltatime = timer.restart().asSeconds();
		
		if (restart == true) {
			map.tilelist.clear();
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
				setnum += 1;
				if (setnum > 4) {
					std::cout << "Congrats!";
					window.close();
				}
			}

			map.tilelist.clear();
			currentplayer = std::make_unique<square>();
			map.loadmap(levels[setnum][levelnum]);
			currentplayer -> shape().setPosition(map.spawn);
			currentplayer -> velocity = sf::Vector2f(0.f, 0.f);
			gravity = 1800.f;
			newlevel = false;
		} 

		while ( const std::optional event = window.pollEvent() ) {
			if ( event->is<sf::Event::Closed>() || running == false)
				window.close();
		}
		
		swapped = false;

		if ((swimming || zerogactive) && currentplayer -> shape().getRotation().asDegrees() != 0) {
			currentplayer -> rotating = false;
			currentplayer -> rotation = 0;
			currentplayer -> shape().getRotation().asDegrees() > 180 ? currentplayer -> shape().rotate(sf::degrees(1)) : currentplayer -> shape().rotate(sf::degrees(-1));
			if (abs(currentplayer -> shape().getRotation().asDegrees()) < 5) currentplayer -> shape().setRotation(sf::degrees(0));
		} 
		if (currentplayer -> rotating) {
			if (std::abs(currentplayer -> rotation) <= std::abs(currentplayer -> velocity.x / (playerdim))) currentplayer -> rotation += 1.15 * currentplayer -> velocity.x / movespeed; 
			currentplayer -> shape().rotate(sf::radians(currentplayer -> rotation * deltatime));
			currentplayer -> rotation *= 0.90;
		}
		if (currentplayer -> grounded && std::abs(currentplayer -> velocity.x) <= 5.f) {
			float currentangle = currentplayer -> shape().getRotation().asDegrees();
			float nearestangle = 360.f;
			for (int i = 0; i <= (360 / nearestedge); i++) {
				if (std::abs(std::fmod(currentangle - i * nearestedge + 540.f, 360.f) - 180.f) < std::abs(std::fmod(currentangle - nearestangle + 540.f, 360.f) - 180.f)) {
					nearestangle = i * nearestedge;
				}
			}
			if (std::fmod(currentangle - nearestangle + 540.f, 360.f) - 180.f > 3.5) currentplayer -> shape().rotate(sf::degrees(-3.5)); 
			else if (std::fmod(currentangle - nearestangle + 540.f, 360.f) - 180.f < -3.5) currentplayer -> shape().rotate(sf::degrees(3.5));
			else currentplayer -> shape().setRotation(sf::degrees(nearestangle));
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) std::cout << currentangle << "," << nearestangle << "\n";
		}
		
		currentplayer -> jump(deltatime);
		currentplayer -> updatepos(deltatime, map);
		currentplayer -> grounded = false;
		map.updatemap(deltatime);
		map.checkCollisions(*currentplayer);
		lastframe_pos = sf::Vector2f(currentplayer -> shape().getPosition());
		lastframe_vel = sf::Vector2f(currentplayer -> velocity);

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
			if (dynamic_cast<square*>(currentplayer.get())) std::cout << "SQUARE COORDS\n";
			if (dynamic_cast<circle*>(currentplayer.get())) std::cout << "CIRCLE COORDS\n";
			if (dynamic_cast<triangle*>(currentplayer.get())) std::cout << "TRIANGLE COORDS\n";
			if (dynamic_cast<hexagon*>(currentplayer.get())) std::cout << "HEXAGON COORDS\n";
			if (dynamic_cast<octagon*>(currentplayer.get())) std::cout << "OCTAGON COORDS\n";
			for (auto& pos: verticeslist) std::cout << pos.x << "," << pos.y << "\n";
			for (auto& pos: map.tilelist) {
				if (pos.type == tiletype::ground) {
					ground_* G = dynamic_cast<ground_*>(pos.tile.get());
					auto verticeslist = getvertices(G -> ground_block);
					std::cout << "GROUND COORDS\n";
					for (auto& rest: verticeslist) std::cout << rest.x << "," << rest.y << "\n";
					break;
				}
			}
			for (auto& pos: map.tilelist) {
				if (pos.type == tiletype::spike) {
					spike* G = dynamic_cast<spike*>(pos.tile.get());
					auto verticeslist = getvertices(G -> spikeblock);
					std::cout << "SPIKR COORDS\n";
					for (auto& rest: verticeslist) std::cout << rest.x << "," << rest.y << "\n";
					break;
				}
			}
			for (auto& pos: map.tilelist) {
				if (pos.type == tiletype::lava) {
					lava* G = dynamic_cast<lava*>(pos.tile.get());
					auto verticeslist = getvertices(G -> lavablock);
					std::cout << "LAVA COORDS\n";
					for (auto& rest: verticeslist) std::cout << rest.x << "," << rest.y << "\n";
					break;
				}
			}
			for (auto& pos: map.tilelist) {
				if (pos.type == tiletype::spring) {
					spring* G = dynamic_cast<spring*>(pos.tile.get());
					auto verticeslist = getvertices(G -> springblock);
					std::cout << "SPRING COORDS\n";
					for (auto& rest: verticeslist) std::cout << rest.x << "," << rest.y << "\n";
					break;
				}
			}
			for (auto& pos: map.tilelist) {
				if (pos.type == tiletype::block_push) {
					block* G = dynamic_cast<block*>(pos.tile.get());
					auto verticeslist = getvertices(G -> blockblock);
					std::cout << "ALL PUSHBLOCK COORDS\n";
					for (auto& rest: verticeslist) std::cout << rest.x << "," << rest.y << "\n";
				}
			}
		}
		
		auto vertices = getvertices(currentplayer -> shape());
		std::sort(vertices.begin(), vertices.end(), [](sf::Vector2f pt1, sf::Vector2f pt2) {return pt1.y > pt2.y; });
		sf::Vector2f btm1 = vertices[0];
		sf::Vector2f btm2 = vertices[1];
		sf::Vector2f center = currentplayer -> shape().getPosition();
		if (btm1.x > btm2.x) std::swap(btm1, btm2);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
			std::cout << "Left side: " << map.cliffCheck(btm1) << "\nRight side: " << map.cliffCheck(btm2) << "\n";
		}

		bool grounded_left = map.cliffCheck(btm1);
		bool grounded_right = map.cliffCheck(btm2);
		bool grounded_center = map.cliffCheck(center);
		if (grounded_left && !grounded_right && !grounded_center) {
			sf::Vector2f edge = sf::Vector2f(std::floor(center.x / playerdim) * playerdim, currentplayer -> shape().getPosition().y + playerdim / 2);
			tipShape(edge, currentplayer -> shape(), deltatime, 1);
		} else if (grounded_right && !grounded_left && !grounded_center) {
			sf::Vector2f edge = sf::Vector2f(std::ceil(center.x / playerdim) * playerdim, currentplayer -> shape().getPosition().y + playerdim / 2);
			tipShape(edge, currentplayer -> shape(), deltatime, -1);
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

			for (auto& pos : map.tilelist) {
				std::vector<sf::Vector2f> tilevertices;
		
				if (pos.type == tiletype::block_push) {
					block* G = dynamic_cast<block*>(pos.tile.get());
					if (G) tilevertices = getvertices(G->blockblock);
					drawdebug(window, tilevertices, tilevertices);
				}
				else if (pos.type == tiletype::lava) {
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