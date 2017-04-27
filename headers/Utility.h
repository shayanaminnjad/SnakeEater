#pragma once

#include <vector>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>

namespace sf
{
	class Shape;
}

namespace utl
{
	void printvalidVideoModes();
	void centerOrigin(sf::Shape& rec);
	int randomInt(int exclusiveMax);
}

struct DataTable
{
	sf::Color defaultColor;
	int cellNumber;
	sf::Font font;
};

DataTable getDataTable();
