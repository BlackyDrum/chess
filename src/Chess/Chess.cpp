#include <memory>
#include <array>
#include <iostream>

#include "Chess/Chess.h"

#include "Chess/Pieces/Piece.h"
#include "Chess/Pieces/Rook.h"
#include "Chess/Pieces/Knight.h"
#include "Chess/Pieces/Bishop.h"
#include "Chess/Pieces/Queen.h"
#include "Chess/Pieces/King.h"
#include "Chess/Pieces/Pawn.h"

void InitPieces(std::array<std::unique_ptr<Piece>, 32>& pieces);

void Run()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Chess", sf::Style::Close);

    Board board;

    std::array<std::unique_ptr<Piece>, 32> pieces;

    InitPieces(pieces);

    Piece* selectedPiece = nullptr;

    std::vector<sf::CircleShape> circles;

	sf::RectangleShape selectedSquare(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
    selectedSquare.setFillColor(sf::Color(255, 255, 126, 128));
    selectedSquare.setPosition(-100, -100);

    Audio audio;

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

                if (selectedPiece)
                {
                    // check if same color piece is on the target position
                    for (const auto& piece : pieces)
                    {
                        if (piece && piece->GetPosition() == translatedPosition)
                        {
                            if (isWhiteTurn && piece->IsWhite() || !isWhiteTurn && !piece->IsWhite())
                            {
                                selectedPiece = piece.get();

                                circles.clear();

                                selectedSquare.setPosition((selectedPiece->GetPosition().x * SQUARE_SIZE), (selectedPiece->GetPosition().y * SQUARE_SIZE));

                                goto out;
                            }
                        }
                    }

                    if (selectedPiece->Move(translatedPosition, pieces))
                    {
                        isWhiteTurn = !isWhiteTurn;

                        audio.PlayMoveSound();

                        circles.clear();

                        selectedSquare.setPosition(-100, -100);

                        selectedPiece = nullptr;
                    }

                    //selectedPiece = nullptr;
                }
                else
                {
                    for (const auto& piece : pieces)
                    {
                        if (piece && piece->GetPosition() == translatedPosition)
                        {
                            if (isWhiteTurn && piece->IsWhite() || !isWhiteTurn && !piece->IsWhite())
                            {
                                selectedPiece = piece.get();

                                selectedSquare.setPosition((selectedPiece->GetPosition().x * SQUARE_SIZE), (selectedPiece->GetPosition().y * SQUARE_SIZE));

                                break;
                            }

                            circles.clear();

                            selectedPiece = nullptr;
                        }
                    }
                }

            out:
                break;
            }
        }

        if (selectedPiece)
        {
            for (const auto& move : selectedPiece->GetPossibleMoves(pieces))
            {
                float circleSize = 5.0f;

                sf::CircleShape circle(circleSize);
                circle.setFillColor(sf::Color(255, 255, 255, 128));
                circle.setOrigin(circleSize, circleSize);
                circle.setPosition((move.x * SQUARE_SIZE) + SQUARE_SIZE / 2.0f, (move.y * SQUARE_SIZE) + SQUARE_SIZE / 2.0f);

                circles.push_back(circle);
            }
        }

        window.clear();

        board.Draw(window);

		window.draw(selectedSquare);

        for (const auto& circle : circles)
        {
            window.draw(circle);
        }

        for (const auto& piece : pieces)
        {
            if (piece)
                piece->Draw(window);
        }

        window.display();
    }
}

void InitPieces(std::array<std::unique_ptr<Piece>, 32>& pieces)
{
    pieces[0] = std::make_unique<Rook>("w_rook.png", 0, 7, true);
    pieces[1] = std::make_unique<Rook>("w_rook.png", 7, 7, true);

    pieces[2] = std::make_unique<Knight>("w_knight.png", 1, 7, true);
    pieces[3] = std::make_unique<Knight>("w_knight.png", 6, 7, true);

    pieces[4] = std::make_unique<Bishop>("w_bishop.png", 2, 7, true);
    pieces[5] = std::make_unique<Bishop>("w_bishop.png", 5, 7, true);

    pieces[6] = std::make_unique<Queen>("w_queen.png", 3, 7, true);

    pieces[7] = std::make_unique<King>("w_king.png", 4, 7, true);

    for (size_t i = 8; i < 16; i++)
    {
        pieces[i] = std::make_unique<Pawn>("w_pawn.png", i - 8, 6, true);
    }

    pieces[16] = std::make_unique<Rook>("b_rook.png", 0, 0, false);
    pieces[17] = std::make_unique<Rook>("b_rook.png", 7, 0, false);

    pieces[18] = std::make_unique<Knight>("b_knight.png", 1, 0, false);
    pieces[19] = std::make_unique<Knight>("b_knight.png", 6, 0, false);

    pieces[20] = std::make_unique<Bishop>("b_bishop.png", 2, 0, false);
    pieces[21] = std::make_unique<Bishop>("b_bishop.png", 5, 0, false);

    pieces[22] = std::make_unique<Queen>("b_queen.png", 3, 0, false);

    pieces[23] = std::make_unique<King>("b_king.png", 4, 0, false);

    for (size_t i = 24; i < 32; i++)
    {
        pieces[i] = std::make_unique<Pawn>("b_pawn.png", i - 24, 1, false);
    }
}