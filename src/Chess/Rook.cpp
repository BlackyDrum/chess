#include "Chess/Rook.h"

bool Rook::Move(const sf::Vector2i& newPos, std::array<std::unique_ptr<Piece>, 32>& pieces)
{
    // Check if the rook is moving horizontally
    if (newPos.y == m_Position.y)
    {
        // Check if the rook is moving to the right
        if (newPos.x > m_Position.x)
        {
            for (int x = m_Position.x + 1; x < newPos.x; x++)
            {
                if (IsPathBlocked(sf::Vector2i(x, m_Position.y), pieces))
                    return false;
            }
        }
        // Check if the rook is moving to the left
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
    // Check if the rook is moving vertically
    else if (newPos.x == m_Position.x)
    {
        // Check if the rook is moving down
        if (newPos.y > m_Position.y)
        {
            for (int y = m_Position.y + 1; y < newPos.y; y++)
            {
                if (IsPathBlocked(sf::Vector2i(m_Position.x, y), pieces))
                    return false;
            }
        }
        // Check if the rook is moving up
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

    return false;
}

std::vector<sf::Vector2i> Rook::GetPossibleMoves(std::array<std::unique_ptr<Piece>, 32>& pieces)
{
    std::vector<sf::Vector2i> possibleMoves;

    // Check if the rook can move to the right
    for (int x = m_Position.x + 1; x < 8; x++)
    {
        if (!IsPathBlocked(sf::Vector2i(x, m_Position.y), pieces))
            possibleMoves.push_back(sf::Vector2i(x, m_Position.y));
        else
            break;
    }
    // Check if the rook can move to the left
    for (int x = m_Position.x - 1; x >= 0; x--)
    {
        if (!IsPathBlocked(sf::Vector2i(x, m_Position.y), pieces))
            possibleMoves.push_back(sf::Vector2i(x, m_Position.y));
        else
            break;
    }
    // Check if the rook can move down
    for (int y = m_Position.y + 1; y < 8; y++)
    {
        if (!IsPathBlocked(sf::Vector2i(m_Position.x, y), pieces))
            possibleMoves.push_back(sf::Vector2i(m_Position.x, y));
        else
            break;
    }
    // Check if the rook can move up
    for (int y = m_Position.y - 1; y >= 0; y--)
    {
        if (!IsPathBlocked(sf::Vector2i(m_Position.x, y), pieces))
            possibleMoves.push_back(sf::Vector2i(m_Position.x, y));
        else
            break;
    }

    return possibleMoves;
}