#include "CellBoard.h"

#include <iostream>

#include <cassert>

typedef CellBoard::CellState CellState;//not sure if this is a good practice

CellBoard::CellBoard(int size)
	:mCellBoard(size)
{
	for (auto& vec : mCellBoard)
		for (int i=0;i<size;++i)
			vec.push_back(CellState::Empty);
}

CellState CellBoard::getCellState(int x, int y)
{
	assert(x < mCellBoard.size() && y < mCellBoard.size());

	return mCellBoard[x][y];
}

void CellBoard::changeCellState(CellState state, int x, int y)
{
	assert(x < mCellBoard.size() && y < mCellBoard.size());

	mCellBoard[x][y] = state;
}

int CellBoard::getCellBoardSize()const
{
	return mCellBoard.size();
}

CellBoard::CellVector CellBoard::getAvailablePlaces()const
{
	CellVector emptyCells;

	int size = mCellBoard.size();

	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			if (mCellBoard[i][j] == CellState::Empty)
				emptyCells.push_back(sf::Vector2i(i, j));

	return emptyCells;
}
