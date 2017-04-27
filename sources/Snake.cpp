#include "Snake.h"
#include "Utility.h"
#include "CellBoard.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include <iostream>

void Snake::BodyBlock::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mBodyBlock,states);
}

Snake::Snake(sf::Color color,float cellSize,CellBoard& cellBoard)
	:mColor(color)
	, mSpeed(1.f)
	, mAccumulatedTime(sf::Time::Zero)
	, mBlockSize(cellSize*0.7f)
	, mCellSize(cellSize)
	,mCellBoard(cellBoard)
	,mIsAlive(true)
	,mLogHandler("SnakeLog.txt")
{
}

void Snake::update(sf::Time dt)
{
	mAccumulatedTime += dt;
	increaseSpeed();
	moveSnake();

	//gameOver
	if (mWormBody.front().mXCell > mCellBoard.getCellBoardSize() ||
		mWormBody.front().mXCell < 0 ||
		mWormBody.front().mYCell < 0 ||
		mWormBody.front().mYCell > mCellBoard.getCellBoardSize())
		mIsAlive = false;

	for (int i = 1; i < mWormBody.size(); ++i)
	{
		if (mWormBody.front().mXCell == mWormBody[i].mXCell &&
			mWormBody.front().mYCell == mWormBody[i].mYCell)
			mIsAlive = false;
	}
}

void Snake::handleEvent(sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		BodyBlock* leader = &mWormBody.front();
		switch (event.key.code)
		{
		case sf::Keyboard::A:
		case sf::Keyboard::Left:
			if (validMove(sf::Keyboard::A))
			{
				leader->mPreviousDir = leader->mCurrentDir;
				leader->mCurrentDir = Direction::LEFT;
			}
			break;
		case sf::Keyboard::D:
		case sf::Keyboard::Right:
			if (validMove(sf::Keyboard::D))
			{
				leader->mPreviousDir = leader->mCurrentDir;
				leader->mCurrentDir = Direction::RIGHT;
			}
			break;
		case sf::Keyboard::W:
		case sf::Keyboard::Up:
			if (validMove(sf::Keyboard::W))
			{
				leader->mPreviousDir = leader->mCurrentDir;
				leader->mCurrentDir = Direction::UP;
			}
			break;
		case sf::Keyboard::S:
		case sf::Keyboard::Down:
			if (validMove(sf::Keyboard::S))
			{
				leader->mPreviousDir = leader->mCurrentDir;
				leader->mCurrentDir = Direction::DOWN;
			}
			break;
		}
	}
}

sf::Vector2i Snake::getLeaderCellPosition()const
{
	BodyBlock body = mWormBody.front();
	return sf::Vector2i(body.mXCell, body.mYCell);
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
	states.transform *= getTransform();

	for (auto &i : mWormBody)
	{
		target.draw(i, states);
	}
}

void Snake::increaseSpeed()
{
	mSpeed = getSnakeSize() / 5 + 1;
}

void Snake::addBodyBlock()
{
	if (mWormBody.size() > 0)
	{
		const BodyBlock& leaderBlock = mWormBody.back();

		sf::Vector2i cellCoordinate(leaderBlock.mXCell, leaderBlock.mYCell);

		switch (leaderBlock.mCurrentDir)
		{
		case Direction::UP:
			createBlockInCell(cellCoordinate.x, cellCoordinate.y + 1,Direction::UP);
			break;
		case Direction::DOWN:
			createBlockInCell(cellCoordinate.x, cellCoordinate.y - 1,Direction::DOWN);
			break;
		case Direction::RIGHT:
			createBlockInCell(cellCoordinate.x - 1, cellCoordinate.y,Direction::RIGHT);
			break;
		case Direction::LEFT:
			createBlockInCell(cellCoordinate.x + 1, cellCoordinate.y,Direction::LEFT);
			break;
		}
	}
	else
	{
		createBlockInCell(4, 0, Direction::RIGHT);
	}
}

bool Snake::isSnakeAlive()const
{
	return mIsAlive;
}

int Snake::getSnakeSize()const
{
	return mWormBody.size();
}

void Snake::moveSnake()
{
	sf::Time moveTime(sf::seconds(1.f / mSpeed));

	while (mAccumulatedTime >= moveTime)
	{
		mHasMove = false;
		mAccumulatedTime -= moveTime;
		Direction previousBlockDir = mWormBody.front().mCurrentDir;
		
		
		for (auto &block : mWormBody)
		{
			block.mCurrentDir = previousBlockDir;
			previousBlockDir = block.mPreviousDir;
			switch (block.mCurrentDir)
			{
			case Direction::UP:
				moveBlockToCell(block, block.mXCell, block.mYCell - 1);
				break;
			case Direction::RIGHT:
				moveBlockToCell(block, block.mXCell + 1, block.mYCell);
				break;
			case Direction::DOWN:
				moveBlockToCell(block, block.mXCell, block.mYCell + 1);
				break;
			case Direction::LEFT:
				moveBlockToCell(block, block.mXCell - 1, block.mYCell);
				break;
			}

			block.mPreviousDir = block.mCurrentDir;
		}
	}
}

void Snake::moveBlockToCell(BodyBlock& body, int xCell, int yCell)
{	
	if (xCell >= mCellBoard.getCellBoardSize() || xCell < 0 ||
		yCell >= mCellBoard.getCellBoardSize() || yCell < 0)
	{
		mIsAlive = false;
		return;
	}
	mCellBoard.changeCellState(CellBoard::CellState::Empty, body.mXCell, body.mYCell);
	mCellBoard.changeCellState(CellBoard::CellState::Snake, xCell, yCell);

	body.mXCell = xCell;
	body.mYCell = yCell;

	float origin = mCellSize / 2;
	body.mBodyBlock.setPosition(sf::Vector2f(xCell*mCellSize + origin, yCell*mCellSize + origin));
}

void Snake::createBlockInCell( int xCell, int yCell,Snake::Direction dir)
{
	//create the body rectangle
	BodyBlock body;
	body.mBodyBlock.setFillColor(mColor);
	body.mBodyBlock.setSize({ mBlockSize,mBlockSize });
	utl::centerOrigin(body.mBodyBlock);

	//set the direction of the body
	body.mCurrentDir = dir;
	body.mPreviousDir = dir;

	//set the cell position and real coordinate of the block
	body.mXCell = xCell;
	body.mYCell = yCell;
	moveBlockToCell(body, xCell, yCell);

	//add the block to worm body
	mWormBody.push_back(body);
}

bool Snake::validMove(sf::Keyboard::Key key)
{
	Direction newDir;
	Direction currentDir = mWormBody.front().mCurrentDir;
	switch (key)
	{
	case sf::Keyboard::A:
		newDir = Direction::LEFT;
		break;
	case sf::Keyboard::D:
		newDir = Direction::RIGHT;
		break;
	case sf::Keyboard::W:
		newDir = Direction::UP;
		break;
	case sf::Keyboard::S:
		newDir = Direction::DOWN;
		break;
	}

	if ((currentDir == Direction::RIGHT && newDir == Direction::LEFT) ||
		(currentDir == Direction::LEFT && newDir == Direction::RIGHT) ||
		(currentDir == Direction::UP && newDir == Direction::DOWN) ||
		(currentDir == Direction::DOWN && newDir == Direction::UP))
		return false;

	if (mHasMove)
		return false;

	mHasMove = true;
	return true;
		
}
