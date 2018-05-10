#include "Board.h"

Board::Board() : m_BoardSize(8)
{
}


Board::~Board()
{
}

void Board::ResetMap()
{
	for (size_t i = 0; i < m_BoardSize; i++)
	{
		for (size_t j = 0; j < m_BoardSize; j++)
		{
			Cell::State state(Cell::State::BLANK);
			if (i == 0 && j % 2 != 0)
				state = Cell::State::WHITE;
			else if (i == 1 && j % 2 == 0)
				state = Cell::State::WHITE;
			else if (i == 2 && j % 2 != 0)
				state = Cell::State::WHITE;
			else if (i == 5 && j % 2 == 0)
				state = Cell::State::BLACK;
			else if (i == 6 && j % 2 != 0)
				state = Cell::State::BLACK;
			else if (i == 7 && j % 2 == 0)
				state = Cell::State::BLACK;
			const pos position = pos(i, j);
			const Cell cell = Cell(Cell::State::BLANK);
			m_Cells.insert({std::move(position), std::move(state)});
		}
	}
}

Board::MoveResult Board::MakeMove(const pos&startPos,const pos &endPos,bool direction, bool forceCombat)
{
	Board::MoveResult moveResult = CheckMove(startPos, endPos, direction);

	switch (moveResult)
	{
	case Board::MoveResult::SUCCESSFULL_MOVE:
		m_Cells.at(endPos).SetState(m_Cells.at(startPos).GetState());
		m_Cells.at(startPos).SetState(Cell::State::BLANK);
		break;
	case Board::MoveResult::SUCCESSFULL_COMBAT:
		m_Cells.at(endPos).SetState(m_Cells.at(startPos).GetState());
		m_Cells.at(startPos).SetState(Cell::State::BLANK);
		m_Cells.at(pos((startPos.first+endPos.first)/2, 
			(startPos.second + endPos.second) / 2)).SetState(Cell::State::BLANK);
		break;
	}

	return moveResult;
}

const map& Board::GetMap() const
{
	return m_Cells;
}

Board::MoveResult Board::CheckMove(const pos &startPos, const pos &endPos, bool direction)
{
	const int dY = endPos.first - startPos.first;
	const int dX = endPos.second - startPos.second;
	Board::MoveResult result = Board::MoveResult::PROHOBITED;
	bool isCombat = false;

	if (dX == 0 && dY == 0 && endPos.first == 0 && endPos.second == 0)
		result = Board::MoveResult::FF;

	if (endPos.first >= 0 && endPos.first < m_BoardSize && 
		endPos.second >= 0 && endPos.second < m_BoardSize)
	{
		Cell::State targetCellState = m_Cells.at(endPos).GetState();


		if (targetCellState==Cell::State::BLANK)
		{
			if (abs(dX) == 2 && abs(dY) == 2)
			{
				pos victimPos((startPos.first + endPos.first) / 2, (startPos.second + endPos.second) / 2);
				Cell::State vistimCellState = m_Cells.at(victimPos).GetState();
				Cell::State StartCellState = m_Cells.at(startPos).GetState(); 
				result = targetCellState != vistimCellState &&
					StartCellState != vistimCellState ? 
					Board::MoveResult::SUCCESSFULL_COMBAT : result;
			}
			else if (((abs(dX) == 1 && dY == 1 && direction)) || (abs(dX) == 1 && dY == -1 && !direction))
			{
				result = Board::MoveResult::SUCCESSFULL_MOVE;
			}
		}
	}

	return result;
}
