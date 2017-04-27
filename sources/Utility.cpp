#include "Utility.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <iostream>
using std::cout;
using std::endl;

#include <random>
#include <ctime>

namespace
{
	std::default_random_engine createRandomEngine()
	{
		auto seed = static_cast<unsigned int>(std::time(nullptr));
		return std::default_random_engine(seed);
	}

	auto randomEngine = createRandomEngine();
}

namespace utl
{
	void printvalidVideoModes()
	{
		std::vector<sf::VideoMode> validModes = sf::VideoMode::getFullscreenModes();
		cout << "All compaitalbe video modes: " << endl;

		for (auto& item : validModes)
			cout << item.width << " * " << item.height << endl;
	}

	void centerOrigin(sf::Shape& shape)
	{
		sf::FloatRect bounds = shape.getLocalBounds();
		shape.setOrigin(bounds.width / 2, bounds.height / 2);
	}

	int randomInt(int exclusiveMax)
	{
		std::uniform_int_distribution<> distr(0, exclusiveMax-1);
		return distr(randomEngine);
	}
}

DataTable getDataTable()
{
	DataTable data;
	data.cellNumber = 20;
	data.defaultColor = sf::Color::White;
	data.font.loadFromFile("main.ttf");
	return data;
}
