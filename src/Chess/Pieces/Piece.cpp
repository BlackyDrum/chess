#include "Chess/Pieces/Piece.h"

Piece::Piece(const std::string& filename, size_t x, size_t y, bool isWhite)
{
    LoadAssets(filename);

    m_Position = sf::Vector2i(x, y);

    sf::FloatRect spriteBounds = m_PieceSprite.getLocalBounds();
    m_PieceSprite.setOrigin(spriteBounds.width / 2.0f, spriteBounds.height / 2.0f);
    m_PieceSprite.setPosition((x * SQUARE_SIZE) + SQUARE_SIZE / 2.0f, (y * SQUARE_SIZE) + SQUARE_SIZE / 2.0f);

    m_PieceSprite.setScale(0.6f, 0.6f);

    m_IsWhite = isWhite;
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

bool Piece::IsPathBlocked(const sf::Vector2i& newPos, const std::array<std::unique_ptr<Piece>, 32>& pieces)
{
    for (const auto& piece : pieces)
    {
        if (piece && piece->GetPosition() == newPos)
            return true;
    }

    return false;
}

bool Piece::CheckCapture(const sf::Vector2i& newPos, std::array<std::unique_ptr<Piece>, 32>& pieces)
{
    for (auto& piece : pieces)
    {
        if (piece && piece->GetPosition() == newPos)
        {
            if (piece->IsWhite() != m_IsWhite)
            {
                piece.reset();

                return true;
            }
        }
    }

    return false;
}
