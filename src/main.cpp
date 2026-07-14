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

int main()
{
	sf::RenderWindow window( sf::VideoMode( { width, height } ), title );
	window.setFramerateLimit(120);

	circle player;
	sky sky;
	tilemap map;
	sf::Clock timer;

	sf::View view;
	view.setSize(sf::Vector2f(camwidth, camheight));
	view.setCenter(sf::Vector2f(player.shape().getPosition().x, player.shape().getPosition().y));

	sky.makestars(stars);

	map.loadmap(levels[0][0]);
	player.shape().setPosition(map.spawn);

	while (window.isOpen()) {
		float deltatime = timer.restart().asSeconds();
		
		if (restart == true) {
			map.tilelist.clear();
			map.loadmap(levels[0][0]);
			player.shape().setPosition(map.spawn);
			player.velocity = sf::Vector2f(0.f, 0.f);
			gravity = 1800.f;
			restart = false;
		} 
		while ( const std::optional event = window.pollEvent() ) {
			if ( event->is<sf::Event::Closed>() || running == false)
				window.close();
		}
		
		player.jump(deltatime);
		player.updatepos(deltatime);
		map.checkCollisions(player);
		map.updatemap(deltatime);

		window.clear();
		window.setView(view);
		sky.drawsky(window);
		sky.drawstars(window);
		player.drawscreen(window);
		map.drawmap(window);
		if (player.shape().getPosition().x < camwidth/2.f) {
			if (player.shape().getPosition().y < camheight/2.f) {
				view.setCenter(sf::Vector2f(camwidth/2.f, camheight/2.f));
			} else if (player.shape().getPosition().y > height-camheight/2.f) {
				view.setCenter(sf::Vector2f(camwidth/2.f, height-camheight/2.f));
			} else {
				view.setCenter(sf::Vector2f(camwidth/2.f, player.shape().getPosition().y));
			}
		} else if (player.shape().getPosition().x > width-camwidth/2.f) {
			if (player.shape().getPosition().y < camheight/2.f) {
				view.setCenter(sf::Vector2f(width-camwidth/2.f, camheight/2.f));
			} else if (player.shape().getPosition().y > height-camheight/2.f) {
				view.setCenter(sf::Vector2f(width-camwidth/2.f, height-camheight/2.f));
			} else {
				view.setCenter(sf::Vector2f(width-camwidth/2.f, player.shape().getPosition().y));
			}
		} else {
			if (player.shape().getPosition().y < camheight/2.f) {
				view.setCenter(sf::Vector2f(player.shape().getPosition().x, camheight/2.f));
			} else if (player.shape().getPosition().y > height-camheight/2.f) {
				view.setCenter(sf::Vector2f(player.shape().getPosition().x, height-camheight/2.f));
			} else {
				view.setCenter(sf::Vector2f(player.shape().getPosition().x, player.shape().getPosition().y));
			}
		}
		window.display();
	}
}