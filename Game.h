#pragma once

#include "Board.h"
#include "IO.h"

class Game
{
public:
	Game();
	~Game();
	enum class Player { NONE, BLACK, WHITE };
	Player GetWinner() const;
	void Start();
private:
	size_t m_WhiteScore;
	size_t m_BlackScore;
	Player m_LastPlayer;
	bool m_isSurrender;
	Board m_board;
	IO m_io;
	bool GetDirection() const;
	movePos MakeIO();
	void SwitchPlayer();
	void UpdateScore();
	std::string GetCurrentPlayer() const;
	std::string CastPlayer(Player) const;
};

