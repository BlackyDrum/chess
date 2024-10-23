#pragma once

#include "Chess/Piece.h"

class Knight : public Piece
{
public:
    Knight(const std::string& filename, size_t x, size_t y, bool isWhite, PieceType type)
        : Piece(filename, x, y, isWhite, type)
    {

    }

    void Move() override;
};