#pragma once

//Divide the Screen to conceptual cubic cells, make it easier to detect collision with seeds
//and randomly generate seeds

#include <vector>
#include <SFML/System/Vector2.hpp>

class CellBoard
{
public:
	enum class CellState { Empty, Snake, Seed };
	typedef std::vector < std::vector<CellState>> Vector2D;
	typedef std::vector < sf::Vector2i> CellVector;
public:
	CellBoard(int size);
	CellState getCellState(int x,int y);
	void changeCellState(CellState state,int x,int y);
	CellVector getAvailablePlaces()const;
	int getCellBoardSize()const;
private:
	Vector2D mCellBoard;
};
