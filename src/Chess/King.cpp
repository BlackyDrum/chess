#include "Chess/King.h"

bool King::Move(const sf::Vector2i& newPos, std::array<std::unique_ptr<Piece>, 32>& pieces)
{
	// Check if the king is moving one square in any direction
	if (std::abs(newPos.x - m_Position.x) <= 1 && std::abs(newPos.y - m_Position.y) <= 1)
	{
		m_Position = newPos;

		CheckCapture(newPos, pieces);

		return true;
	}

	return false;
}