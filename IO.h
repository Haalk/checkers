#pragma once
#include <utility>
#include <map>
#include "Cell.h"

class Cell;
using movePos = std::pair<pos,pos>;
using map = std::map<pos, Cell>;

class IO
{
public:
	IO();
	~IO();
	movePos GetMove(std::string player);
	void DrawBoard(const map&);
	void PrintScore(size_t whitescore, size_t blackscore);
	void EndGame(std::string);
private:
	std::string CastState(Cell::State);
};

