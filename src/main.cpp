#include <SFML/Graphics.hpp>
#include <iostream>

#include "states.h"
#include "players.h"
#include "obstacles.h"
#include "scenes.h"
#include "ui.h"
#include "vars.h"

int main()
{
	sf::RenderWindow window( sf::VideoMode( { width, height } ), title );
	window.setFramerateLimit(60);

	player player;
	ground ground;
	sf::Clock timer;

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
		ground.drawscreen(window);
		player.drawscreen(window);
		window.display();
	}
}