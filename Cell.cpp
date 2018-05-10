#include "Cell.h"

Cell::Cell(/*const pos& position,*/ Cell::State state) : m_State(state)//,m_Position(position),
{
}

Cell::State Cell::GetState() const
{
	return m_State;
}

void Cell::SetState(Cell::State state)
{
	m_State = state;
}

/*const pos &Cell::GetPosition() const
{
	return m_Position;
}

void Cell::SetPosition(const pos &position)
{
	m_Position = position;
}
*/
Cell::~Cell()
{
}
