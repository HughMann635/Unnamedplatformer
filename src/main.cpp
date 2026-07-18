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

	for (auto& pos: map.tilelist) {
		if (pos.type == tiletype::ground) {
			ground_* G = dynamic_cast<ground_*>(pos.tile.get());
			auto verticeslist_ = getvertices(G -> ground_block);
			for (auto& rest: verticeslist_) std::cout << rest.x << "," << rest.y << "\n";
			break;
		}
	}

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

		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) jumpkeyheld = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) && !jumpkeyheld) {
			auto verticeslist = getvertices(currentplayer -> shape());
			for (auto& pos: verticeslist) std::cout << pos.x << "," << pos.y << "\n";
			jumpkeyheld = true;
		}

		window.clear();
		window.setView(view);
		sky.drawsky(window);
		sky.drawstars(window);
		currentplayer -> drawscreen(window);
		map.drawmap(window);
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