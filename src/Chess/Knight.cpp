#include "Chess/Knight.h"

bool Knight::Move(const sf::Vector2i& newPos, std::array<std::unique_ptr<Piece>, 32>& pieces)
{
	m_Position = newPos;

	return false;
}