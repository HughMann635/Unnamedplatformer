#include <SFML/Graphics.hpp>
#include <iostream>

#include "states.h"
#include "players.h"
#include "tiletypes.h"
#include "scenes.h"
#include "ui.h"
#include "vars.h"
#include "tilesettings.h"

int main()
{
	sf::RenderWindow window( sf::VideoMode( { width, height } ), title );
	window.setFramerateLimit(60);

	player player;
	ground ground;
	sky sky;
	tilemap map;
	sf::Clock timer;

	sf::View view;
	view.setSize(sf::Vector2f(camwidth, camheight));
	view.setCenter(sf::Vector2f(player.playershape.getPosition().x, player.playershape.getPosition().y));

	sky.makestars(stars);

	while ( window.isOpen() ) {
		float deltatime = timer.restart().asSeconds();
		
		while ( const std::optional event = window.pollEvent() ) {
			if ( event->is<sf::Event::Closed>() )
				window.close();
			player.jump(event);
		}

		player.updatepos(deltatime);
		player.checkground(ground.getgroundlevel());

		window.clear();
		window.setView(view);
		sky.drawsky(window);
		sky.drawstars(window);
		ground.drawscreen(window);
		player.drawscreen(window);
		if (player.playershape.getPosition().x < camwidth/2.f) {
			if (player.playershape.getPosition().y < camheight/2.f) {
				view.setCenter(sf::Vector2f(camwidth/2.f, camheight/2.f));
			} else if (player.playershape.getPosition().y > height-camheight/2.f) {
				view.setCenter(sf::Vector2f(camwidth/2.f, height-camheight/2.f));
			} else {
				view.setCenter(sf::Vector2f(camwidth/2.f, player.playershape.getPosition().y));
			}
		} else if (player.playershape.getPosition().x > width-camwidth/2.f) {
			if (player.playershape.getPosition().y < camheight/2.f) {
				view.setCenter(sf::Vector2f(width-camwidth/2.f, camheight/2.f));
			} else if (player.playershape.getPosition().y > height-camheight/2.f) {
				view.setCenter(sf::Vector2f(width-camwidth/2.f, height-camheight/2.f));
			} else {
				view.setCenter(sf::Vector2f(width-camwidth/2.f, player.playershape.getPosition().y));
			}
		} else {
			if (player.playershape.getPosition().y < camheight/2.f) {
				view.setCenter(sf::Vector2f(player.playershape.getPosition().x, camheight/2.f));
			} else if (player.playershape.getPosition().y > height-camheight/2.f) {
				view.setCenter(sf::Vector2f(player.playershape.getPosition().x, height-camheight/2.f));
			} else {
				view.setCenter(sf::Vector2f(player.playershape.getPosition().x, player.playershape.getPosition().y));
			}
		}
		window.display();
	}
}