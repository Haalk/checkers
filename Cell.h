#pragma once
#include <utility>

using pos = std::pair<size_t, size_t>;

class Cell
{
public:
	enum class State { BLACK, WHITE, BLANK };
	State GetState() const;
	void SetState(State);
	//const pos& GetPosition() const;
	//void SetPosition(const pos&);

	Cell(/*const pos&,*/ State);
	~Cell();
	
private:
	State m_State;
	//std::pair<size_t, size_t> m_Position; 
};

