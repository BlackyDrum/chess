#pragma once

#include "Chess/Piece.h"

class Rook : public Piece
{
public:
    Rook(const std::string& filename, size_t x, size_t y, bool isWhite, PieceType type)
        : Piece(filename, x, y, isWhite, type)
    {

    }

    void Move() override;
};