#include <SFML/Graphics.hpp>
#include <iostream>

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
		
		currentplayer -> jump(deltatime);
		currentplayer -> updatepos(deltatime, map);
		currentplayer -> grounded = false;
		map.checkCollisions(*currentplayer);
		map.updatemap(deltatime);
		lastframe_pos = sf::Vector2f(currentplayer -> shape().getPosition());
		lastframe_vel = sf::Vector2f(currentplayer -> velocity);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1) && !dynamic_cast<square*>(currentplayer.get())) currentplayer = std::make_unique<square>();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2) && !dynamic_cast<circle*>(currentplayer.get())) currentplayer = std::make_unique<circle>();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3) && !dynamic_cast<triangle*>(currentplayer.get())) currentplayer = std::make_unique<triangle>();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4) && !dynamic_cast<hexagon*>(currentplayer.get())) currentplayer = std::make_unique<hexagon>();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num5) && !dynamic_cast<octagon*>(currentplayer.get())) currentplayer = std::make_unique<octagon>();

		currentplayer -> shape().setPosition(lastframe_pos);
		currentplayer -> velocity = lastframe_vel;
		currentplayer -> shape().rotate(sf::degrees(1));

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
			draw = !draw;
			enterkeyheld = true;
		}

		window.clear();
		window.setView(view);
		sky.drawsky(window);
		sky.drawstars(window);
		currentplayer -> drawscreen(window);
		map.drawmap(window);
		//DEBUG DRAWING STUFF
		if (draw) {
			for (auto& pos: map.tilelist) {
				if (pos.type == tiletype::block_push) {
					block* G = dynamic_cast<block*>(pos.tile.get());
					auto verticeslist = getvertices(G -> blockblock);
					drawdebug(window, verticeslist);
				}
				if (pos.type == tiletype::lava) {
					lava* G = dynamic_cast<lava*>(pos.tile.get());
					auto verticeslist = getvertices(G -> lavablock);
					drawdebug(window, verticeslist);
				}
				if (pos.type == tiletype::spike) {
					spike* G = dynamic_cast<spike*>(pos.tile.get());
					auto verticeslist = getvertices(G -> spikeblock);
					drawdebug(window, verticeslist);
				}
			}
			drawdebug(window, getvertices(currentplayer -> shape()));
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