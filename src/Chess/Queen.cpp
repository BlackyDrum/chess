#include "Chess/Queen.h"

bool Queen::Move(const sf::Vector2i& newPos, std::array<std::unique_ptr<Piece>, 32>& pieces)
{
	// Check if the queen is moving horizontally
	if (newPos.y == m_Position.y)
	{
		// Check if the queen is moving to the right
		if (newPos.x > m_Position.x)
		{
			for (int x = m_Position.x + 1; x < newPos.x; x++)
			{
				if (IsPathBlocked(sf::Vector2i(x, m_Position.y), pieces))
					return false;
			}
		}
		// Check if the queen is moving to the left
		else if (newPos.x < m_Position.x)
		{
			for (int x = m_Position.x - 1; x > newPos.x; x--)
			{
				if (IsPathBlocked(sf::Vector2i(x, m_Position.y), pieces))
					return false;
			}
		}

		m_Position = newPos;

		CheckCapture(newPos, pieces);

		return true;
	}
	// Check if the queen is moving vertically
	else if (newPos.x == m_Position.x)
	{
		// Check if the queen is moving down
		if (newPos.y > m_Position.y)
		{
			for (int y = m_Position.y + 1; y < newPos.y; y++)
			{
				if (IsPathBlocked(sf::Vector2i(m_Position.x, y), pieces))
					return false;
			}
		}
		// Check if the queen is moving up
		else if (newPos.y < m_Position.y)
		{
			for (int y = m_Position.y - 1; y > newPos.y; y--)
			{
				if (IsPathBlocked(sf::Vector2i(m_Position.x, y), pieces))
					return false;
			}
		}

		m_Position = newPos;

		CheckCapture(newPos, pieces);

		return true;
	}
	// Check if the queen is moving diagonally
	else if (std::abs(newPos.x - m_Position.x) == std::abs(newPos.y - m_Position.y))
	{
		// Check if the queen is moving to the right and down
		if (newPos.x > m_Position.x && newPos.y > m_Position.y)
		{
			for (int i = 1; i < newPos.x - m_Position.x; i++)
			{
				if (IsPathBlocked(sf::Vector2i(m_Position.x + i, m_Position.y + i), pieces))
					return false;
			}

			m_Position = newPos;

			CheckCapture(newPos, pieces);

			return true;
		}
		// Check if the queen is moving to the right and up
		else if (newPos.x > m_Position.x && newPos.y < m_Position.y)
		{
			for (int i = 1; i < newPos.x - m_Position.x; i++)
			{
				if (IsPathBlocked(sf::Vector2i(m_Position.x + i, m_Position.y - i), pieces))
					return false;
			}

			m_Position = newPos;

			CheckCapture(newPos, pieces);

			return true;
		}
		// Check if the queen is moving to the left and down
		else if (newPos.x < m_Position.x && newPos.y > m_Position.y)
		{
			for (int i = 1; i < m_Position.x - newPos.x; i++)
			{
				if (IsPathBlocked(sf::Vector2i(m_Position.x - i, m_Position.y + i), pieces))
					return false;
			}

			m_Position = newPos;

			CheckCapture(newPos, pieces);

			return true;
		}
		// Check if the queen is moving to the left and up
		else if (newPos.x < m_Position.x && newPos.y < m_Position.y)
		{
			for (int i = 1; i < m_Position.x - newPos.x; i++)
			{
				if (IsPathBlocked(sf::Vector2i(m_Position.x - i, m_Position.y - i), pieces))
					return false;
			}

			m_Position = newPos;

			CheckCapture(newPos, pieces);

			return true;
		}

		m_Position = newPos;

		CheckCapture(newPos, pieces);

		return true;
	}
}