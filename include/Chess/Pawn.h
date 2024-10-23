#pragma once

#include "Chess/Piece.h"

class Pawn : public Piece
{
public:
    Pawn(const std::string& filename, size_t x, size_t y, bool isWhite, PieceType type)
        : Piece(filename, x, y, isWhite, type)
    {

    }

    void Move() override;
};