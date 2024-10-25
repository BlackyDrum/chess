#include "Chess/Pieces/Bishop.h"

bool Bishop::Move(const sf::Vector2i& newPos, std::array<std::unique_ptr<Piece>, 32>& pieces)
{
    // Check if the bishop is moving diagonally
    if (std::abs(newPos.x - m_Position.x) == std::abs(newPos.y - m_Position.y))
    {
        // Check if the bishop is moving to the right and down
        if (newPos.x > m_Position.x && newPos.y > m_Position.y)
        {
            for (int i = 1; i < newPos.x - m_Position.x; i++)
            {
                if (IsPathBlocked(sf::Vector2i(m_Position.x + i, m_Position.y + i), pieces))
                    return false;
            }
        }
        // Check if the bishop is moving to the right and up
        else if (newPos.x > m_Position.x && newPos.y < m_Position.y)
        {
            for (int i = 1; i < newPos.x - m_Position.x; i++)
            {
                if (IsPathBlocked(sf::Vector2i(m_Position.x + i, m_Position.y - i), pieces))
                    return false;
            }
        }
        // Check if the bishop is moving to the left and down
        else if (newPos.x < m_Position.x && newPos.y > m_Position.y)
        {
            for (int i = 1; i < m_Position.x - newPos.x; i++)
            {
                if (IsPathBlocked(sf::Vector2i(m_Position.x - i, m_Position.y + i), pieces))
                    return false;
            }
        }
        // Check if the bishop is moving to the left and up
        else if (newPos.x < m_Position.x && newPos.y < m_Position.y)
        {
            for (int i = 1; i < m_Position.x - newPos.x; i++)
            {
                if (IsPathBlocked(sf::Vector2i(m_Position.x - i, m_Position.y - i), pieces))
                    return false;
            }
        }

        m_Position = newPos;

        CheckCapture(newPos, pieces);

        return true;
    }

    return false;
}

std::vector<sf::Vector2i> Bishop::GetPossibleMoves(std::array<std::unique_ptr<Piece>, 32>& pieces)
{
    std::vector<sf::Vector2i> possibleMoves;

    // Check if the bishop can move to the right and down
    for (int i = 1; m_Position.x + i < 8 && m_Position.y + i < 8; i++)
    {
        if (!IsPathBlocked(sf::Vector2i(m_Position.x + i, m_Position.y + i), pieces))
            possibleMoves.push_back(sf::Vector2i(m_Position.x + i, m_Position.y + i));
        else
            break;
    }
    // Check if the bishop can move to the right and up
    for (int i = 1; m_Position.x + i < 8 && m_Position.y - i >= 0; i++)
    {
        if (!IsPathBlocked(sf::Vector2i(m_Position.x + i, m_Position.y - i), pieces))
            possibleMoves.push_back(sf::Vector2i(m_Position.x + i, m_Position.y - i));
        else
            break;
    }
    // Check if the bishop can move to the left and down
    for (int i = 1; m_Position.x - i >= 0 && m_Position.y + i < 8; i++)
    {
        if (!IsPathBlocked(sf::Vector2i(m_Position.x - i, m_Position.y + i), pieces))
            possibleMoves.push_back(sf::Vector2i(m_Position.x - i, m_Position.y + i));
        else
            break;
    }
    // Check if the bishop can move to the left and up
    for (int i = 1; m_Position.x - i >= 0 && m_Position.y - i >= 0; i++)
    {
        if (!IsPathBlocked(sf::Vector2i(m_Position.x - i, m_Position.y - i), pieces))
            possibleMoves.push_back(sf::Vector2i(m_Position.x - i, m_Position.y - i));
        else
            break;
    }

    return possibleMoves;
}