#pragma once

#include <SFML/Graphics.hpp>

#include "Chess/Chess.h"
#include "Chess/Audio.h"

class Piece
{
public:
    Piece(const std::string& filename, size_t x, size_t y, bool isWhite);

    void Draw(sf::RenderWindow& window);
    bool IsWhite() const { return m_IsWhite; };
    sf::Vector2i GetPosition() const { return m_Position; };

    virtual bool Move(const sf::Vector2i& newPos, std::array<std::unique_ptr<Piece>, 32>& pieces) = 0;
    virtual std::vector<sf::Vector2i> GetPossibleMoves(std::array<std::unique_ptr<Piece>, 32>& pieces) = 0;
protected:
    sf::Vector2i m_Position;

    Audio m_Audio;
protected:
    bool IsPathBlocked(const sf::Vector2i& newPos, const std::array<std::unique_ptr<Piece>, 32>& pieces);
    bool CheckCapture(const sf::Vector2i& newPos, std::array<std::unique_ptr<Piece>, 32>& pieces);
private:
    sf::Texture m_PieceTexture;
    sf::Sprite m_PieceSprite;

    bool m_IsWhite;
private:
    void LoadAssets(const std::string& filename);
};