#pragma once

#include "Snake.h"
#include "Seed.h"
#include "Utility.h"
#include "CellBoard.h"

namespace sf
{
	class RenderWindow;
	class RectangleShape;
}

class World:private UnCopyable
{
public:
	World(sf::RenderWindow& target);
	void update(sf::Time dt);
	void render();
	void handleEvent(sf::Event& event);
	bool isGameOver()const;
private: 
	void handleCollision();
	void seedGenerator();
private:
	CellBoard mCellBoard;
	float mCellSize;
	Snake mSnake;
	Seed mSeed;
	sf::RenderWindow& mTarget;
	bool mIsGameOver;
	//shapes
	sf::RectangleShape mWindowBorder;
	sf::RectangleShape mPauseCover;
	sf::Text mPauseText;
	sf::Text mScoreText;

};
