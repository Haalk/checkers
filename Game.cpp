#include "Game.h"
#include <iostream>
#include <stdlib.h>

Game::Game() : m_LastPlayer(Player::NONE), m_WhiteScore(0), m_BlackScore(0),
				m_isSurrender(false)
{
}


Game::~Game()
{
}

Game::Player Game::GetWinner() const
{
	Player winner(Player::NONE);

	if (m_isSurrender)
	{
		if (m_LastPlayer == Player::WHITE)
			winner = Player::BLACK;
		else if (m_LastPlayer == Player::BLACK)
			winner = Player::WHITE;
	}
	else
	{
		if (m_WhiteScore == 12)
		{
			winner = Player::WHITE;
		}
		else if (m_BlackScore == 12)
		{
			winner = Player::BLACK;
		}
	}
	return winner;
}

void Game::Start()
{
	m_board.ResetMap();
	while (GetWinner() == Player::NONE)
	{
		Board::MoveResult moveResult (Board::MoveResult::PROHOBITED);

		while (moveResult == Board::MoveResult::PROHOBITED)
		{
			auto newMove = MakeIO();

			bool direction = GetDirection();
			moveResult = m_board.MakeMove(newMove.first, newMove.second, direction);
		}

		if (moveResult == Board::MoveResult::FF)
		{
			m_isSurrender = true;
			break;
		}

		if (moveResult == Board::MoveResult::SUCCESSFULL_COMBAT)
		{
			UpdateScore();
		}

		SwitchPlayer();
	}
	m_io.EndGame(CastPlayer(GetWinner()));
}

bool Game::GetDirection() const
{
	bool direction;
	switch (m_LastPlayer)
	{
	case Player::WHITE:
		direction = false;
		break;
	default:
		direction = true;
		break;
	}


	return direction; 
}

movePos Game::MakeIO()
{
	system("cls");
	auto map = m_board.GetMap();
	m_io.DrawBoard(map);
	m_io.PrintScore(m_WhiteScore, m_BlackScore);

	std::string player = GetCurrentPlayer();

	auto newMove = m_io.GetMove(player);

	return std::move(newMove);
}

void Game::SwitchPlayer()
{
	if (m_LastPlayer == Player::WHITE)
		m_LastPlayer = Player::BLACK;
	else
		m_LastPlayer = Player::WHITE;
}

void Game::UpdateScore()
{
	if (m_LastPlayer == Player::WHITE)
		m_BlackScore++;
	else
		m_WhiteScore++;
}

std::string Game::GetCurrentPlayer() const
{
	std::string player;

	if (m_LastPlayer == Player::WHITE)
		player= "Black";
	else
		player = "White";
	return std::move(player);
}

std::string Game::CastPlayer(Player player) const
{

	std::string str_player;
	switch (player)
	{
	case Player::WHITE:str_player = "White player"; break;
	//case Player::BLACK:str_player = "Black player"; break;
	default:
		str_player = "Black player"; break;
	}

	return str_player;
}
