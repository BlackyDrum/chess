#pragma once

#include <SFML/Graphics.hpp>

#include "Chess/Chess.h"

class Piece
{
public:
    Piece(const std::string& filename, size_t x, size_t y, bool isWhite, PieceType type);

    void Draw(sf::RenderWindow& window);

    virtual void Move() = 0;
protected:
    PieceType m_PieceType;

    sf::Vector2i m_Position;
private:
    sf::Texture m_PieceTexture;
    sf::Sprite m_PieceSprite;

    bool m_IsWhite;
private:
    void LoadAssets(const std::string& filename);
};