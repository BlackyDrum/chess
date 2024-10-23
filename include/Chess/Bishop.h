#pragma once

#include "Chess/Piece.h"

class Bishop : public Piece
{
public:
    Bishop(const std::string& filename, size_t x, size_t y, bool isWhite, PieceType type)
        : Piece(filename, x, y, isWhite, type)
    {

    }

    void Move(sf::Vector2i& newPos) override;
};