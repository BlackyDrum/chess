#include <memory>
#include <array>
#include <iostream>

#include "Chess/Chess.h"

#include "Chess/Piece.h"
#include "Chess/Rook.h"
#include "Chess/Knight.h"
#include "Chess/Bishop.h"
#include "Chess/Queen.h"
#include "Chess/King.h"
#include "Chess/Pawn.h"

void InitPieces(std::array<std::unique_ptr<Piece>, 32>& pieces);

void Run()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Chess", sf::Style::Close);

    Board board;

    std::array<std::unique_ptr<Piece>, 32> pieces;

    InitPieces(pieces);

    sf::Vector2i selectedPiecePosition(-1, -1);

    bool isWhiteTurn = true;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                sf::Vector2i translatedPosition(mousePosition.x / SQUARE_SIZE, mousePosition.y / SQUARE_SIZE);

                if (selectedPiecePosition != sf::Vector2i(-1, -1))
                {
                    for (const auto& piece : pieces)
                    {
                        if (piece->GetPosition() == translatedPosition)
                        {
                            selectedPiecePosition = translatedPosition;

                            goto out;
                        }
                    }

                    for (const auto& piece : pieces)
                    {
                        if (piece->GetPosition() == selectedPiecePosition)
                        {
                            piece->Move(translatedPosition);

                            break;
                        }
                    }

                    selectedPiecePosition = sf::Vector2i(-1, -1);
                }

                for (const auto& piece : pieces)
                {
                    if (piece->GetPosition() == translatedPosition)
                    {
                        selectedPiecePosition = translatedPosition;

                        break;
                    }
                }

            out:
                break;

            }
        }

        window.clear();



        board.Draw(window);

        for (const auto& piece : pieces)
        {
            piece->Draw(window);
        }

        window.display();
    }
}

void InitPieces(std::array<std::unique_ptr<Piece>, 32>& pieces)
{
    pieces[0] = std::make_unique<Rook>("w_rook.png", 0, 7, true, ROOK);
    pieces[1] = std::make_unique<Rook>("w_rook.png", 7, 7, true, ROOK);

    pieces[2] = std::make_unique<Knight>("w_knight.png", 1, 7, true, KNIGHT);
    pieces[3] = std::make_unique<Knight>("w_knight.png", 6, 7, true, KNIGHT);

    pieces[4] = std::make_unique<Bishop>("w_bishop.png", 2, 7, true, BISHOP);
    pieces[5] = std::make_unique<Bishop>("w_bishop.png", 5, 7, true, BISHOP);

    pieces[6] = std::make_unique<Queen>("w_queen.png", 3, 7, true, QUEEN);

    pieces[7] = std::make_unique<King>("w_king.png", 4, 7, true, KING);

    for (size_t i = 8; i < 16; i++)
    {
        pieces[i] = std::make_unique<Pawn>("w_pawn.png", i - 8, 6, true, PAWN);
    }

    pieces[16] = std::make_unique<Rook>("b_rook.png", 0, 0, false, ROOK);
    pieces[17] = std::make_unique<Rook>("b_rook.png", 7, 0, false, ROOK);

    pieces[18] = std::make_unique<Knight>("b_knight.png", 1, 0, false, KNIGHT);
    pieces[19] = std::make_unique<Knight>("b_knight.png", 6, 0, false, KNIGHT);

    pieces[20] = std::make_unique<Bishop>("b_bishop.png", 2, 0, false, BISHOP);
    pieces[21] = std::make_unique<Bishop>("b_bishop.png", 5, 0, false, BISHOP);

    pieces[22] = std::make_unique<Queen>("b_queen.png", 3, 0, false, QUEEN);

    pieces[23] = std::make_unique<King>("b_king.png", 4, 0, false, KING);

    for (size_t i = 24; i < 32; i++)
    {
        pieces[i] = std::make_unique<Pawn>("b_pawn.png", i - 24, 1, false, PAWN);
    }
}