#include "Chess/Pieces/Pawn.h"

bool Pawn::Move(const sf::Vector2i& newPos, std::array<std::unique_ptr<Piece>, 32>& pieces)
{
    int direction = IsWhite() ? -1 : +1;
    int startRow = IsWhite() ? 6 : 1;

    // Check if the pawn is moving forward
    if (newPos.x == m_Position.x)
    {
        // Check if the pawn is moving two squares forward
        if (newPos.y == m_Position.y + (2 * direction) && m_Position.y == startRow)
        {
            if (IsPathBlocked(sf::Vector2i(m_Position.x, m_Position.y + (2 * direction)), pieces))
                return false;

            m_Position = newPos;

            return true;
        }
        // Check if the pawn is moving one square forward
        else if (newPos.y == m_Position.y + direction)
        {
            if (IsPathBlocked(sf::Vector2i(m_Position.x, m_Position.y + direction), pieces))
                return false;

            m_Position = newPos;

            return true;
        }
    }
    // Check if the pawn is capturing a piece
    else if (std::abs(newPos.x - m_Position.x) == 1 && newPos.y == m_Position.y + direction)
    {
        for (auto& piece : pieces)
        {
            // Check if there is a piece in the target position
            if (piece && piece->GetPosition() == newPos)
            {
                // Check if the piece is an enemy piece
                if (piece->IsWhite() != IsWhite())
                {
                    m_Position = newPos;
                    piece.reset();

                    return true;
                }
            }
        }
    }

    return false;
}

std::vector<sf::Vector2i> Pawn::GetPossibleMoves(std::array<std::unique_ptr<Piece>, 32>& pieces)
{
    std::vector<sf::Vector2i> possibleMoves;

    int direction = IsWhite() ? -1 : +1;
    int startRow = IsWhite() ? 6 : 1;

	// Check if the pawn can move two squares forward
	if (m_Position.y == startRow)
	{
		if (!IsPathBlocked(sf::Vector2i(m_Position.x, m_Position.y + (2 * direction)), pieces))
			possibleMoves.push_back(sf::Vector2i(m_Position.x, m_Position.y + (2 * direction)));
	}
    // Check if the pawn can move one square forward
    if (m_Position.y + direction >= 0 && m_Position.y + direction < 8)
    {
        if (!IsPathBlocked(sf::Vector2i(m_Position.x, m_Position.y + direction), pieces))
            possibleMoves.push_back(sf::Vector2i(m_Position.x, m_Position.y + direction));
    }
    // Check if the pawn can capture a piece
    if (m_Position.y + direction >= 0 && m_Position.y + direction < 8)
    {
        if (m_Position.x + 1 < 8)
        {
            for (auto& piece : pieces)
            {
                if (piece && piece->GetPosition() == sf::Vector2i(m_Position.x + 1, m_Position.y + direction))
                {
                    if (piece->IsWhite() != IsWhite())
                        possibleMoves.push_back(sf::Vector2i(m_Position.x + 1, m_Position.y + direction));
                }
            }
        }
        if (m_Position.x - 1 >= 0)
        {
            for (auto& piece : pieces)
            {
                if (piece && piece->GetPosition() == sf::Vector2i(m_Position.x - 1, m_Position.y + direction))
                {
                    if (piece->IsWhite() != IsWhite())
                        possibleMoves.push_back(sf::Vector2i(m_Position.x - 1, m_Position.y + direction));
                }
            }
        }
    }

    return possibleMoves;
}

