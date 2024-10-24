#include "Chess/Knight.h"

bool Knight::Move(const sf::Vector2i& newPos, std::array<std::unique_ptr<Piece>, 32>& pieces)
{
	// Check if the knight is moving in an L shape
	if ((std::abs(newPos.x - m_Position.x) == 2 && std::abs(newPos.y - m_Position.y) == 1) ||
		(std::abs(newPos.x - m_Position.x) == 1 && std::abs(newPos.y - m_Position.y) == 2))
	{
		m_Position = newPos;

		CheckCapture(newPos, pieces);

		return true;
	}

	return false;
}