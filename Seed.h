#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/CircleShape.hpp>

class CellBoard;
namespace sf
{
	class Time;
}

class Seed :public sf::Drawable, public sf::Transformable
{
public:
	Seed(float CellSize);
	void moveToCell(int x, int y);
	sf::Vector2i getCellPosition()const;
	void update(sf::Time dt);
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
private:
	sf::CircleShape mCircle;
	bool mShrink;
	float mCellSize;
	float mMaxSize;
	float mMinSize;
	int mCellX;
	int mCellY;
	
};
