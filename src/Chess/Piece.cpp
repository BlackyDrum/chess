#include "Chess/Piece.h"

Piece::Piece(const std::string& filename, size_t x, size_t y, bool isWhite, PieceType type)
{
    LoadAssets(filename);

    m_Position = sf::Vector2i(x, y);

    sf::FloatRect spriteBounds = m_PieceSprite.getLocalBounds();
    m_PieceSprite.setOrigin(spriteBounds.width / 2.0f, spriteBounds.height / 2.0f);
    m_PieceSprite.setPosition((x * SQUARE_SIZE) + SQUARE_SIZE / 2.0f, (y * SQUARE_SIZE) + SQUARE_SIZE / 2.0f);

    m_PieceSprite.setScale(0.6f, 0.6f);

    m_IsWhite = isWhite;

    m_PieceType = type;
}

void Piece::Draw(sf::RenderWindow& window)
{
	m_PieceSprite.setPosition((m_Position.x * SQUARE_SIZE) + SQUARE_SIZE / 2.0f, (m_Position.y * SQUARE_SIZE) + SQUARE_SIZE / 2.0f);

    window.draw(m_PieceSprite);
}

void Piece::LoadAssets(const std::string& filename)
{
    m_PieceTexture.loadFromFile("assets/pieces/" + filename);
    m_PieceSprite.setTexture(m_PieceTexture);
}