#pragma once

#include "Chess/Piece.h"

class Queen : public Piece
{
public:
    Queen(const std::string& filename, size_t x, size_t y, bool isWhite, PieceType type)
        : Piece(filename, x, y, isWhite, type)
    {

    }

    void Move() override;
};