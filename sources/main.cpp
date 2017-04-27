#include "World.h"
#include "LogHandler.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>
#include <memory>

#if 1
int main()
{
	const sf::Time frameRate = sf::seconds(1.f / 30.f);
	sf::RenderWindow window(sf::VideoMode(800, 800), "Snake Eater");
	window.setVerticalSyncEnabled(false);
	window.setKeyRepeatEnabled(false);

	sf::Clock clock;
	sf::Time deltaTime= sf::Time::Zero;

	while (window.isOpen())
	{
		auto worldPtr = std::make_unique<World>(window);
		while (!worldPtr->isGameOver())
		{
			sf::Event event;
			deltaTime += clock.restart();

			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
				worldPtr->handleEvent(event);
			}


			while (deltaTime >= frameRate)
			{
				worldPtr->update(frameRate);
				deltaTime -= frameRate;
			}

			worldPtr->render();
		}
		using std::cout;
		using std::endl;
		using std::cin;
		cout << "Do you want to play?(press y as yes, any other key as no)" << endl;
		char choice;
		cin >> choice;
		if (choice != 'y')
		{
			window.close();
		}
	}
}

#endif

