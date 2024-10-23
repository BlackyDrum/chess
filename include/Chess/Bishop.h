#pragma once

#include "Chess/Piece.h"

class Bishop : public Piece
{
public:
    Bishop(const std::string& filename, size_t x, size_t y, bool isWhite)
        : Piece(filename, x, y, isWhite)
    {

    }

    bool Move(const sf::Vector2i& newPos, std::array<std::unique_ptr<Piece>, 32>& pieces) override;
};