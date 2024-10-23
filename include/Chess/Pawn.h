#pragma once

#include "Chess/Piece.h"

class Pawn : public Piece
{
public:
    Pawn(const std::string& filename, size_t x, size_t y, bool isWhite)
        : Piece(filename, x, y, isWhite)
    {

    }

    bool Move(const sf::Vector2i& newPos, std::array<std::unique_ptr<Piece>, 32>& pieces) override;
private:
	bool IsPathBlocked(const sf::Vector2i& start, const sf::Vector2i& end, const std::array<std::unique_ptr<Piece>, 32>& pieces);
};