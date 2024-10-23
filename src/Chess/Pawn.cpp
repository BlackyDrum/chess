#include "Chess/Pawn.h"

bool Pawn::IsPathBlocked(const sf::Vector2i& start, const sf::Vector2i& end, const std::array<std::unique_ptr<Piece>, 32>& pieces)
{
    for (const auto& piece : pieces)
    {
        if (piece && piece->GetPosition() == end)
            return true; // A piece is blocking the path
    }

    return false;
}

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
            if (IsPathBlocked(m_Position, sf::Vector2i(m_Position.x, m_Position.y + direction), pieces))
                return false;

            m_Position = newPos;

            return true;
        }
        // Check if the pawn is moving one square forward
        else if (newPos.y == m_Position.y + direction)
        {
            if (IsPathBlocked(m_Position, sf::Vector2i(m_Position.x, m_Position.y + direction), pieces))
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
