#include "Chess/Pieces/King.h"

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

std::vector<sf::Vector2i> King::GetPossibleMoves(std::array<std::unique_ptr<Piece>, 32>& pieces)
{
    std::vector<sf::Vector2i> possibleMoves;

    // Check if the king can move to the right
    if (m_Position.x + 1 < 8)
    {
        if (!IsPathBlocked(sf::Vector2i(m_Position.x + 1, m_Position.y), pieces))
            possibleMoves.push_back(sf::Vector2i(m_Position.x + 1, m_Position.y));
    }
    // Check if the king can move to the left
    if (m_Position.x - 1 >= 0)
    {
        if (!IsPathBlocked(sf::Vector2i(m_Position.x - 1, m_Position.y), pieces))
            possibleMoves.push_back(sf::Vector2i(m_Position.x - 1, m_Position.y));
    }
    // Check if the king can move down
    if (m_Position.y + 1 < 8)
    {
        if (!IsPathBlocked(sf::Vector2i(m_Position.x, m_Position.y + 1), pieces))
            possibleMoves.push_back(sf::Vector2i(m_Position.x, m_Position.y + 1));
    }
    // Check if the king can move up
    if (m_Position.y - 1 >= 0)
    {
        if (!IsPathBlocked(sf::Vector2i(m_Position.x, m_Position.y - 1), pieces))
            possibleMoves.push_back(sf::Vector2i(m_Position.x, m_Position.y - 1));
    }
    // Check if the king can move to the right and down
    if (m_Position.x + 1 < 8 && m_Position.y + 1 < 8)
    {
        if (!IsPathBlocked(sf::Vector2i(m_Position.x + 1, m_Position.y + 1), pieces))
            possibleMoves.push_back(sf::Vector2i(m_Position.x + 1, m_Position.y + 1));
    }
    // Check if the king can move to the right and up
    if (m_Position.x + 1 < 8 && m_Position.y - 1 >= 0)
    {
        if (!IsPathBlocked(sf::Vector2i(m_Position.x + 1, m_Position.y - 1), pieces))
            possibleMoves.push_back(sf::Vector2i(m_Position.x + 1, m_Position.y - 1));
    }
    // Check if the king can move to the left and down
    if (m_Position.x - 1 >= 0 && m_Position.y + 1 < 8)
    {
        if (!IsPathBlocked(sf::Vector2i(m_Position.x - 1, m_Position.y + 1), pieces))
            possibleMoves.push_back(sf::Vector2i(m_Position.x - 1, m_Position.y + 1));
    }
    // Check if the king can move to the left and up
    if (m_Position.x - 1 >= 0 && m_Position.y - 1 >= 0)
    {
        if (!IsPathBlocked(sf::Vector2i(m_Position.x - 1, m_Position.y - 1), pieces))
            possibleMoves.push_back(sf::Vector2i(m_Position.x - 1, m_Position.y - 1));
    }

    return possibleMoves;
}