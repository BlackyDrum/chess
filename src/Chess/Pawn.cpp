#include "Chess/Pawn.h"
#include <iostream>

void Pawn::Move(sf::Vector2i& newPos)
{
	m_Position = newPos;
}