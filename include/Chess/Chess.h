#pragma once

#include <SFML/Graphics.hpp>

#include "Chess/Board.h"

const size_t WINDOW_SIZE = 768;
const size_t SQUARE_SIZE = WINDOW_SIZE / 8;

void Run();

enum PieceType
{
    PAWN = 0,
    ROOK,
    KNIGHT,
    BISHOP,
    QUEEN,
    KING,
};