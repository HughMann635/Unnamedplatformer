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
	ground.setFillColor(sf::Color(255,200,200));
	ground.setPosition(sf::Vector2f(0.f, height-100.f));

	sf::Vector2f velocity = (sf::Vector2f(0.f, gravity));
	sf::Clock timer;
	bool grounded = false;

	while ( window.isOpen() ) {
		float deltatime = timer.restart().asSeconds();
		
		while ( const std::optional event = window.pollEvent() ) {
			if ( event->is<sf::Event::Closed>() )
				window.close();

			if ( event->is<sf::Event::KeyPressed>() ) {
				auto& key = event->getIf<sf::Event::KeyPressed>()->code;
				if (key == sf::Keyboard::Key::Up || key == sf::Keyboard::Key::W) {
					if (grounded) {
						velocity.y -= jumpforce;
						grounded = false;
					}
				} 
			}
		}

		if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed (sf::Keyboard::Key::D)) {
			velocity.x = movespeed;
		} else if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed (sf::Keyboard::Key::A)) {
			velocity.x = -movespeed;
		} else {velocity.x = 0.f; }

		if (!grounded) {
			velocity.y += gravity * deltatime;
		}

		player.move(velocity * deltatime);

		float groundlevel = ground.getPosition().y-playerdim;
		float playerlevel = player.getPosition().y;

		if (playerlevel >= groundlevel) {
			player.setPosition(sf::Vector2f(player.getPosition().x, ground.getPosition().y-playerdim));
			grounded = true;
			velocity.y = 0.f;
		}

		window.clear();
		window.draw(player);
		window.draw(ground);
		window.display();
	}
}