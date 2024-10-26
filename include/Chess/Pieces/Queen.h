#pragma once

#include "Chess/Pieces/Piece.h"

class Queen : public Piece
{
public:
    Queen(const std::string& filename, size_t x, size_t y, bool isWhite)
        : Piece(filename, x, y, isWhite) {}

    bool Move(const sf::Vector2i& newPos, std::array<std::unique_ptr<Piece>, 32>& pieces) override;
    std::vector<sf::Vector2i> GetPossibleMoves(std::array<std::unique_ptr<Piece>, 32>& pieces) override;
};