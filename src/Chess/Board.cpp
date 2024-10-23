#include "Chess/Board.h"

Board::Board()
{
    LoadAssets();
}

void Board::Draw(sf::RenderWindow& window)
{
    window.draw(m_BoardSprite);
}

void Board::LoadAssets()
{
    m_BoardTexture.loadFromFile("assets/board.png");
    m_BoardSprite.setTexture(m_BoardTexture);
}