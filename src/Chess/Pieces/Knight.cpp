#include "Chess/Pieces/Knight.h"

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

std::vector<sf::Vector2i> Knight::GetPossibleMoves(std::array<std::unique_ptr<Piece>, 32>& pieces)
{
    std::vector<sf::Vector2i> possibleMoves;

    // Check if the knight can move to the right and down
    if (m_Position.x + 2 < 8 && m_Position.y + 1 < 8)
    {
        if (!IsPathBlocked(sf::Vector2i(m_Position.x + 2, m_Position.y + 1), pieces))
            possibleMoves.push_back(sf::Vector2i(m_Position.x + 2, m_Position.y + 1));
    }
    // Check if the knight can move to the right and up
    if (m_Position.x + 2 < 8 && m_Position.y - 1 >= 0)
    {
        if (!IsPathBlocked(sf::Vector2i(m_Position.x + 2, m_Position.y - 1), pieces))
            possibleMoves.push_back(sf::Vector2i(m_Position.x + 2, m_Position.y - 1));
    }
    // Check if the knight can move to the left and down
    if (m_Position.x - 2 >= 0 && m_Position.y + 1 < 8)
    {
        if (!IsPathBlocked(sf::Vector2i(m_Position.x - 2, m_Position.y + 1), pieces))
            possibleMoves.push_back(sf::Vector2i(m_Position.x - 2, m_Position.y + 1));
    }
    // Check if the knight can move to the left and up
    if (m_Position.x - 2 >= 0 && m_Position.y - 1 >= 0)
    {
        if (!IsPathBlocked(sf::Vector2i(m_Position.x - 2, m_Position.y - 1), pieces))
            possibleMoves.push_back(sf::Vector2i(m_Position.x - 2, m_Position.y - 1));
    }
    // Check if the knight can move to the right and down
    if (m_Position.x + 1 < 8 && m_Position.y + 2 < 8)
    {
        if (!IsPathBlocked(sf::Vector2i(m_Position.x + 1, m_Position.y + 2), pieces))
            possibleMoves.push_back(sf::Vector2i(m_Position.x + 1, m_Position.y + 2));
    }
    // Check if the knight can move to the right and up
    if (m_Position.x + 1 < 8 && m_Position.y - 2 >= 0)
    {
        if (!IsPathBlocked(sf::Vector2i(m_Position.x + 1, m_Position.y - 2), pieces))
            possibleMoves.push_back(sf::Vector2i(m_Position.x + 1, m_Position.y - 2));
    }
    // Check if the knight can move to the left and down
    if (m_Position.x - 1 >= 0 && m_Position.y + 2 < 8)
    {
        if (!IsPathBlocked(sf::Vector2i(m_Position.x - 1, m_Position.y + 2), pieces))
            possibleMoves.push_back(sf::Vector2i(m_Position.x - 1, m_Position.y + 2));
    }
    // Check if the knight can move to the left and up
    if (m_Position.x - 1 >= 0 && m_Position.y - 2 >= 0)
    {
        if (!IsPathBlocked(sf::Vector2i(m_Position.x - 1, m_Position.y - 2), pieces))
            possibleMoves.push_back(sf::Vector2i(m_Position.x - 1, m_Position.y - 2));
    }

    return possibleMoves;
}