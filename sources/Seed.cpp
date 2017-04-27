#include "Seed.h"
#include "Utility.h"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <iostream>
using std::cout;
using std::endl;

Seed::Seed(float cellSize)
	:mCircle()
	, mShrink(false)
	, mCellSize(cellSize)
	, mMinSize(cellSize / 2 * 0.3)
	, mCellX(0)
	, mCellY(0)
{
	mCircle.setFillColor(sf::Color::Yellow);
	mCircle.setRadius(mMinSize);
	utl::centerOrigin(mCircle);
	
}

void Seed::moveToCell(int x, int y)
{
	mCellX = x;
	mCellY = y;
	float origin = mCellSize / 2;
	setPosition(x*mCellSize + origin, y*mCellSize + origin);
}

sf::Vector2i Seed::getCellPosition()const
{
	return sf::Vector2i(mCellX, mCellY);
}

void Seed::update(sf::Time dt)
{
	//seed animation
	if (mShrink)
		mCircle.scale(0.9f,0.9f);
	else
		mCircle.scale(1.1f, 1.1f);

	if (mCircle.getScale().x <= 0.3f && mCircle.getScale().y <=0.3f)
		mShrink = false;
	else if(mCircle.getScale().x >= 1.7f && mCircle.getScale().y >= 1.7f)
		mShrink = true;
}

void Seed::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
	states.transform *= getTransform();

	target.draw(mCircle, states);
}
