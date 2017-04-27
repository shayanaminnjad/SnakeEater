#include "World.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace
{
	DataTable dataTable = getDataTable();
}

World::World(sf::RenderWindow& target)
	:mCellBoard(dataTable.cellNumber)
	, mCellSize(target.getSize().x / dataTable.cellNumber)
	, mSnake(dataTable.defaultColor, mCellSize, mCellBoard)
	, mSeed(mCellSize)
	, mTarget(target)
	, mIsGameOver(false)
	, mWindowBorder()
	, mPauseCover()
	, mPauseText()
	, mScoreText()
{
	mSnake.addBodyBlock();
	mSnake.addBodyBlock();
	mSnake.addBodyBlock();
	seedGenerator();

	mWindowBorder.setFillColor(sf::Color::Transparent);
	mWindowBorder.setSize(sf::Vector2f(mTarget.getSize().x - 10, mTarget.getSize().y - 10));
	mWindowBorder.setPosition(sf::Vector2f(5, 5));
	mWindowBorder.setOutlineColor(sf::Color::White);
	mWindowBorder.setOutlineThickness(5.f);

	mPauseCover.setSize(sf::Vector2f(mTarget.getSize().x - 10, mTarget.getSize().y - 10));
	mPauseCover.setPosition(sf::Vector2f(5, 5));
	mPauseCover.setFillColor(sf::Color(0, 0, 0, 200));

	mPauseText.setString("GAME OVER");
	mPauseText.setFont(dataTable.font);
	mPauseText.setCharacterSize(90u);
	mPauseText.setPosition(30.f, 30.f);

	mScoreText.setFont(dataTable.font);
	mScoreText.setString("Score : 00");
	mScoreText.setPosition(mTarget.getSize().x - 130, 5);
	mScoreText.setCharacterSize(22u);
}

void World::update(sf::Time dt)
{
	if (!mIsGameOver)
	{
		mSnake.update(dt);
		handleCollision();
		mSeed.update(dt);
		mScoreText.setString("Score : " + std::to_string((mSnake.getSnakeSize() - 3) * 10));
	}

	if (!mSnake.isSnakeAlive())
	{
		mIsGameOver = true;
	}
}

void World::render()
{
	mTarget.clear();
	mTarget.draw(mSnake);
	mTarget.draw(mSeed);
	mTarget.draw(mWindowBorder);
	mTarget.draw(mScoreText);
	if (mIsGameOver)
	{
		mTarget.draw(mPauseCover);
		mTarget.draw(mPauseText);
	}
	mTarget.display();
}

void World::handleEvent(sf::Event& event)
{
	mSnake.handleEvent(event);
}

bool World::isGameOver()const
{
	return mIsGameOver;
}

void World::handleCollision()
{
	if (mSnake.getLeaderCellPosition() == mSeed.getCellPosition())
	{
		mCellBoard.changeCellState(CellBoard::CellState::Empty, mSeed.getCellPosition().x, mSeed.getCellPosition().y);
		seedGenerator();
		mSnake.addBodyBlock();
	}
}

void World::seedGenerator()
{
	CellBoard::CellVector emptyPlaces(mCellBoard.getAvailablePlaces());
	
	if (emptyPlaces.size() != 0)
	{
		int rand = utl::randomInt(emptyPlaces.size());
		mCellBoard.changeCellState(CellBoard::CellState::Seed, emptyPlaces[rand].x, emptyPlaces[rand].y);
		mSeed.moveToCell(emptyPlaces[rand].x, emptyPlaces[rand].y);
	}
}
