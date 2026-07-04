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

	//Placeholder player
	sf::RectangleShape player( sf::Vector2f(playerdim, playerdim));
	player.setFillColor(sf::Color::Red);
	player.setPosition(sf::Vector2f(100.f, 300.f));

	//Placeholder ground
	sf::RectangleShape ground( sf::Vector2f(width, 100.f));
	ground.setFillColor(sf::Color(255,0,200));
	ground.setPosition(sf::Vector2f(0.f, height-100.f));

	sf::Vector2f velocity = (sf::Vector2f(0.f, gravity));
	sf::Clock timer;

	while ( window.isOpen() ) {
		float deltatime = timer.restart().asSeconds();
		
		while ( const std::optional event = window.pollEvent() ) {
			if ( event->is<sf::Event::Closed>() )
				window.close();
		}
		window.clear();
		window.draw(player);
		window.draw(ground);
		window.display();
	}
}
