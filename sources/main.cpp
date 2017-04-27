#include "World.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>


#if 1
int main()
{
	sf::Time frameRate = sf::seconds(1.f / 30.f);
	sf::RenderWindow window(sf::VideoMode(800, 800), "Snake Eater");
	sf::View myView = window.getDefaultView();
	window.setVerticalSyncEnabled(false);
	window.setKeyRepeatEnabled(false);

	sf::Clock clock;
	sf::Time deltaTime= sf::Time::Zero;

	World world(window);

	while (window.isOpen())
	{
		sf::Event event;
		deltaTime += clock.restart();
		
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			world.handleEvent(event);
		}

		
		while (deltaTime >= frameRate)
		{
			world.update(frameRate);
			deltaTime -= frameRate;
		}

		world.render();
	}
}

#endif
