#pragma once

#include "Uncopyable.h"
#include "Utility.h"
#include "LogHandler.h"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include <vector>

class CellBoard;
class Snake : public sf::Drawable, public sf::Transformable, private UnCopyable
{
public:
	enum class Direction{ LEFT, UP, RIGHT, DOWN };
public:
	explicit Snake(sf::Color,float cellSize,CellBoard& cellBoard);
	void update(sf::Time dt);
	void handleEvent(sf::Event& event);
	sf::Vector2i getLeaderCellPosition()const;
	void addBodyBlock();	
	bool isSnakeAlive()const;
	int getSnakeSize()const;
private:
	struct BodyBlock:public sf::Drawable
	{
		sf::RectangleShape mBodyBlock;
		Direction mCurrentDir;
		Direction mPreviousDir;
		int mXCell;
		int mYCell;

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
	};
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
	void increaseSpeed();//increase speed if number of blocks grows
	bool validMove(sf::Keyboard::Key);
	void moveSnake();
	void moveBlockToCell(BodyBlock& block,int xCell,int yCell);
	void createBlockInCell(int xCell, int yCell, Direction dir);
private:
	std::vector<BodyBlock> mWormBody;
	sf::Color mColor;
	float mSpeed;//measured as moves per second
	sf::Time mAccumulatedTime;
	float mBlockSize;
	float mCellSize;
	CellBoard& mCellBoard;
	bool mIsAlive;
	bool mHasMove;
	LogHandler mLogHandler;
};
