#pragma once

#include "Cell.h"
#include <map>

using map = std::map<pos, Cell>;

class Board
{
public:
	Board();
	~Board();
	enum class MoveResult {SUCCESSFULL_MOVE,SUCCESSFULL_COMBAT,PROHOBITED,FF};
	void ResetMap();
	MoveResult MakeMove(const pos&, const pos &, bool,bool=false);
	const map& GetMap() const;

private:
	const size_t m_BoardSize;
	map m_Cells;
	MoveResult CheckMove(const pos &, const pos &, bool);
};

