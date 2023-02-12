#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

const int windowWith = 768, windowHeight = 768;
const int fields = 8;
const int tileSize = windowWith / fields;


class Chess {
private:
    sf::Texture t_board;
    sf::Sprite m_board;

    sf::Texture t_blackRook;
    sf::Texture t_blackKnight;
    sf::Texture t_blackBishop;
    sf::Texture t_blackQueen;
    sf::Texture t_blackKing;
    sf::Texture t_blackPawn;

    sf::Texture t_whiteRook;
    sf::Texture t_whiteKnight;
    sf::Texture t_whiteBishop;
    sf::Texture t_whiteQueen;
    sf::Texture t_whiteKing;
    sf::Texture t_whitePawn;

    std::vector<sf::Sprite> m_pieces;

    std::vector<sf::CircleShape> m_circles;

    sf::SoundBuffer b_pieceMove;
    sf::Sound s_pieceMove;
    sf::SoundBuffer b_capture;
    sf::Sound s_capture;

    /*
    * Initialize starting position
    * Black Pieces:
    *       rook      ->  -10 and -11
    *       knight    ->  -20 and -21
    *       bishop    ->  -30 and -31
    *       queen     ->  -40
    *       king      ->  -50
    *       pawn      ->  -60 - -67
    * 
    * White Pieces:
    *       rook      ->   10 and 11
    *       knight    ->   20 and 21
    *       bishop    ->   30 and 31
    *       queen     ->   40
    *       king      ->   50
    *       pawn      ->   60 - 67
    * 
    * Empty field     ->   0
    * 
    */
    int a_board[fields][fields] = {
        {-10,-20,-30,-40,-50,-31,-21,-11},
        {-60,-61,-62,-63,-64,-65,-66,-67},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {60,61,62,63,64,65,66,67},
        {10,20,30,40,50,31,21,11}
    };
    bool b_board[fields][fields] = { false };
    bool m_circleBoard[fields][fields] = { false };
    int m_canTakeBoard[fields][fields] = { 0 };

    bool m_whiteTurn;
    bool m_pieceClicked;
    int m_currentPieceClicked;
    sf::Vector2i m_currentPiecePosition;

public:
    Chess();
    bool loadAssets();
    void drawBoard();
    void move(sf::RenderWindow&);
    void deletePieces(int, int);
    void setCircle();
    void drawCircle(sf::RenderWindow&);
    void deleteCircle();
    void setPieceTransparency();

    sf::Sprite getBoard() const { return m_board; }
    std::vector<sf::Sprite> getPieces() const { return m_pieces; }
    std::vector<sf::CircleShape> getCircle() const { return m_circles; }
    
};

Chess::Chess() {
    m_whiteTurn = true;
    m_pieceClicked = false;

    for (int i = 0; i < fields * fields; i++) {
        sf::CircleShape c;
        c.setFillColor(sf::Color(255, 255, 255, 128));
        c.setPosition(-100, -100);
        c.setRadius(0);
        m_circles.push_back(c);
    }

   
}
void Chess::setPieceTransparency() {
    for (int i = 0; i < fields; i++) {
        for (int j = 0; j < fields; j++) {
                if (m_canTakeBoard[i][j] == -60)
                    m_pieces[8].setColor(sf::Color(255, 255, 255, 128));
                if (m_canTakeBoard[i][j] == -61)
                    m_pieces[9].setColor(sf::Color(255, 255, 255, 128));
                if (m_canTakeBoard[i][j] == -62)
                    m_pieces[10].setColor(sf::Color(255, 255, 255, 128));
                if (m_canTakeBoard[i][j] == -63)
                    m_pieces[11].setColor(sf::Color(255, 255, 255, 128));
                if (m_canTakeBoard[i][j] == -64)
                    m_pieces[12].setColor(sf::Color(255, 255, 255, 128));
                if (m_canTakeBoard[i][j] == -65)
                    m_pieces[13].setColor(sf::Color(255, 255, 255, 128));
                if (m_canTakeBoard[i][j] == -66)
                    m_pieces[14].setColor(sf::Color(255, 255, 255, 128));
                if (m_canTakeBoard[i][j] == -67)
                    m_pieces[15].setColor(sf::Color(255, 255, 255, 128));

                if (m_canTakeBoard[i][j] == -10)
                    m_pieces[0].setColor(sf::Color(255, 255, 255, 128));
                if (m_canTakeBoard[i][j] == -20)
                    m_pieces[1].setColor(sf::Color(255, 255, 255, 128));
                if (m_canTakeBoard[i][j] == -30)
                    m_pieces[2].setColor(sf::Color(255, 255, 255, 128));
                if (m_canTakeBoard[i][j] == -40)
                    m_pieces[3].setColor(sf::Color(255, 255, 255, 128));
                if (m_canTakeBoard[i][j] == -50)
                    m_pieces[4].setColor(sf::Color(255, 255, 255, 128));
                if (m_canTakeBoard[i][j] == -31)
                    m_pieces[5].setColor(sf::Color(255, 255, 255, 128));
                if (m_canTakeBoard[i][j] == -21)
                    m_pieces[6].setColor(sf::Color(255, 255, 255, 128));
                if (m_canTakeBoard[i][j] == -11)
                    m_pieces[7].setColor(sf::Color(255, 255, 255, 128));



                if (m_canTakeBoard[i][j] == 60)
                    m_pieces[24].setColor(sf::Color(255, 255, 255, 128));
                if (m_canTakeBoard[i][j] == 61)
                    m_pieces[25].setColor(sf::Color(255, 255, 255, 128));
                if (m_canTakeBoard[i][j] == 62)
                    m_pieces[26].setColor(sf::Color(255, 255, 255, 128));
                if (m_canTakeBoard[i][j] == 63)
                    m_pieces[27].setColor(sf::Color(255, 255, 255, 128));
                if (m_canTakeBoard[i][j] == 64)
                    m_pieces[28].setColor(sf::Color(255, 255, 255, 128));
                if (m_canTakeBoard[i][j] == 65)
                    m_pieces[29].setColor(sf::Color(255, 255, 255, 128));
                if (m_canTakeBoard[i][j] == 66)
                    m_pieces[30].setColor(sf::Color(255, 255, 255, 128));
                if (m_canTakeBoard[i][j] == 67)
                    m_pieces[31].setColor(sf::Color(255, 255, 255, 128));

                if (m_canTakeBoard[i][j] == 10)
                    m_pieces[16].setColor(sf::Color(255, 255, 255, 128));
                if (m_canTakeBoard[i][j] == 20)
                    m_pieces[17].setColor(sf::Color(255, 255, 255, 128));
                if (m_canTakeBoard[i][j] == 30)
                    m_pieces[18].setColor(sf::Color(255, 255, 255, 128));
                if (m_canTakeBoard[i][j] == 40)
                    m_pieces[19].setColor(sf::Color(255, 255, 255, 128));
                if (m_canTakeBoard[i][j] == 50)
                    m_pieces[20].setColor(sf::Color(255, 255, 255, 128));
                if (m_canTakeBoard[i][j] == 31)
                    m_pieces[21].setColor(sf::Color(255, 255, 255, 128));
                if (m_canTakeBoard[i][j] == 21)
                    m_pieces[22].setColor(sf::Color(255, 255, 255, 128));
                if (m_canTakeBoard[i][j] == 11)
                    m_pieces[23].setColor(sf::Color(255, 255, 255, 128));

        }
        
    }

    if (m_whiteTurn) {
            m_pieces[24].setColor(sf::Color(255, 255, 255, 255));
            m_pieces[25].setColor(sf::Color(255, 255, 255, 255));
            m_pieces[26].setColor(sf::Color(255, 255, 255, 255));
            m_pieces[27].setColor(sf::Color(255, 255, 255, 255));
            m_pieces[28].setColor(sf::Color(255, 255, 255, 255));
            m_pieces[29].setColor(sf::Color(255, 255, 255, 255));
            m_pieces[30].setColor(sf::Color(255, 255, 255, 255));
            m_pieces[31].setColor(sf::Color(255, 255, 255, 255));

            m_pieces[16].setColor(sf::Color(255, 255, 255, 255));
            m_pieces[17].setColor(sf::Color(255, 255, 255, 255));
            m_pieces[18].setColor(sf::Color(255, 255, 255, 255));
            m_pieces[19].setColor(sf::Color(255, 255, 255, 255));
            m_pieces[20].setColor(sf::Color(255, 255, 255, 255));
            m_pieces[21].setColor(sf::Color(255, 255, 255, 255));
            m_pieces[22].setColor(sf::Color(255, 255, 255, 255));
            m_pieces[23].setColor(sf::Color(255, 255, 255, 255));
    }
    else {
            m_pieces[8].setColor(sf::Color(255, 255, 255, 255));
            m_pieces[9].setColor(sf::Color(255, 255, 255, 255));
            m_pieces[10].setColor(sf::Color(255, 255, 255, 255));
            m_pieces[11].setColor(sf::Color(255, 255, 255, 255));
            m_pieces[12].setColor(sf::Color(255, 255, 255, 255));
            m_pieces[13].setColor(sf::Color(255, 255, 255, 255));
            m_pieces[14].setColor(sf::Color(255, 255, 255, 255));
            m_pieces[15].setColor(sf::Color(255, 255, 255, 255));

            m_pieces[0].setColor(sf::Color(255, 255, 255, 255));
            m_pieces[1].setColor(sf::Color(255, 255, 255, 255));
            m_pieces[2].setColor(sf::Color(255, 255, 255, 255));
            m_pieces[3].setColor(sf::Color(255, 255, 255, 255));
            m_pieces[4].setColor(sf::Color(255, 255, 255, 255));
            m_pieces[5].setColor(sf::Color(255, 255, 255, 255));
            m_pieces[6].setColor(sf::Color(255, 255, 255, 255));
            m_pieces[7].setColor(sf::Color(255, 255, 255, 255));
    }

}
void Chess::drawCircle(sf::RenderWindow& window) {
    int counter = 0;
    for (int i = 0; i < fields; i++) {
        for (int j = 0; j < fields; j++) {
            if (m_circleBoard[i][j] && m_canTakeBoard[i][j] == 0) {
                m_circles[counter].setPosition(j * tileSize + 40, i * tileSize +  40);
                m_circles[counter].setRadius(5);
                counter++;
          
            }
            
        }
    }

}
void Chess::deleteCircle() {
    for (int i = 0; i < fields; i++) {
        for (int j = 0; j < fields; j++) {
            m_circleBoard[i][j] = false;
           
        }
    }
    for (int i = 0; i < m_circles.size(); i++) {
        m_circles[i].setRadius(0);
    }
}
void Chess::setCircle() {
    if (m_pieceClicked) {
        if (m_whiteTurn && m_currentPieceClicked < 0) {
            return;
        }
        if (!m_whiteTurn && m_currentPieceClicked > 0) {
            return;
        }

        if (m_currentPieceClicked >= 60 && m_currentPieceClicked <= 67) {
            if (m_currentPiecePosition.x == 6) {
                if (a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y] == 0)
                    m_circleBoard[m_currentPiecePosition.x - 1][m_currentPiecePosition.y] = true;
                if (a_board[m_currentPiecePosition.x - 2][m_currentPiecePosition.y] == 0)
                    m_circleBoard[m_currentPiecePosition.x - 2][m_currentPiecePosition.y] = true;
                if (m_currentPiecePosition.x > 0 && m_currentPiecePosition.y > 0 && a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 1] < 0) {
                    m_circleBoard[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 1] = true;
                    m_canTakeBoard[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 1] = a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 1];
                }                 
                if (m_currentPiecePosition.x > 0 && m_currentPiecePosition.y < 7 && a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 1] < 0) {
                    m_circleBoard[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 1] = true;
                    m_canTakeBoard[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 1] = a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 1];
                }
                    

            }
            else {
                if (m_currentPiecePosition.x > 0 && a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y] == 0)
                    m_circleBoard[m_currentPiecePosition.x - 1][m_currentPiecePosition.y] = true;
                if (m_currentPiecePosition.x > 0 && m_currentPiecePosition.y > 0 && a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 1] < 0) {
                    m_circleBoard[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 1] = true;
                    m_canTakeBoard[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 1] = a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 1];
                }
                if (m_currentPiecePosition.x > 0 && m_currentPiecePosition.y < 7 && a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 1] < 0) {
                    m_circleBoard[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 1] = true;
                    m_canTakeBoard[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 1] = a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 1];
                }

            }
        }
        else if (m_currentPieceClicked == 10 || m_currentPieceClicked == 11) {
            for (int i = m_currentPiecePosition.x; i >= 0; i--) {
                if (i == m_currentPiecePosition.x)
                    continue;
                if (a_board[i][m_currentPiecePosition.y] > 0)
                    break;
                if (a_board[i][m_currentPiecePosition.y] < 0) {
                    m_circleBoard[i][m_currentPiecePosition.y] = true;
                    m_canTakeBoard[i][m_currentPiecePosition.y] = a_board[i][m_currentPiecePosition.y];
                    break;
                }
                m_circleBoard[i][m_currentPiecePosition.y] = true;
            }
            for (int i = m_currentPiecePosition.x; i < 8; i++) {
                if (i == m_currentPiecePosition.x)
                    continue;
                if (a_board[i][m_currentPiecePosition.y] > 0)
                    break;
                if (a_board[i][m_currentPiecePosition.y] < 0) {
                    m_circleBoard[i][m_currentPiecePosition.y] = true;
                    m_canTakeBoard[i][m_currentPiecePosition.y] = a_board[i][m_currentPiecePosition.y];
                    break;
                }
                m_circleBoard[i][m_currentPiecePosition.y] = true;
            }
            for (int i = m_currentPiecePosition.y; i < 8; i++) {
                if (i == m_currentPiecePosition.y)
                    continue;
                if (a_board[m_currentPiecePosition.x][i] > 0)
                    break;
                if (a_board[m_currentPiecePosition.x][i] < 0) {
                    m_circleBoard[m_currentPiecePosition.x][i] = true;
                    m_canTakeBoard[m_currentPiecePosition.x][i] = a_board[m_currentPiecePosition.x][i];
                    break;
                }
                m_circleBoard[m_currentPiecePosition.x][i] = true;
            }
            for (int i = m_currentPiecePosition.y; i >= 0; i--) {
                if (i == m_currentPiecePosition.y)
                    continue;
                if (a_board[m_currentPiecePosition.x][i] > 0)
                    break;
                if (a_board[m_currentPiecePosition.x][i] < 0) {
                    m_circleBoard[m_currentPiecePosition.x][i] = true;
                    m_canTakeBoard[m_currentPiecePosition.x][i] = a_board[m_currentPiecePosition.x][i];
                    break;
                }
                m_circleBoard[m_currentPiecePosition.x][i] = true;
            }

        }
        else if (m_currentPieceClicked == 20 || m_currentPieceClicked == 21) {
            if (m_currentPiecePosition.x - 2 >= 0) {
                if (m_currentPiecePosition.y - 1 >= 0 && (a_board[m_currentPiecePosition.x - 2][m_currentPiecePosition.y - 1] < 0 || a_board[m_currentPiecePosition.x - 2][m_currentPiecePosition.y - 1] == 0)) {
                    m_circleBoard[m_currentPiecePosition.x - 2][m_currentPiecePosition.y - 1] = true;
                    if (a_board[m_currentPiecePosition.x - 2][m_currentPiecePosition.y - 1] < 0)
                        m_canTakeBoard[m_currentPiecePosition.x - 2][m_currentPiecePosition.y - 1] = a_board[m_currentPiecePosition.x - 2][m_currentPiecePosition.y - 1];
                }
                if (m_currentPiecePosition.y + 1 <= 7 && (a_board[m_currentPiecePosition.x - 2][m_currentPiecePosition.y + 1] < 0 || a_board[m_currentPiecePosition.x - 2][m_currentPiecePosition.y + 1] == 0)) {
                    m_circleBoard[m_currentPiecePosition.x - 2][m_currentPiecePosition.y + 1] = true;
                    if (a_board[m_currentPiecePosition.x - 2][m_currentPiecePosition.y + 1] < 0)
                        m_canTakeBoard[m_currentPiecePosition.x - 2][m_currentPiecePosition.y + 1] = a_board[m_currentPiecePosition.x - 2][m_currentPiecePosition.y + 1];
                }
            }
            if (m_currentPiecePosition.x + 2 <= 7) {
                if (m_currentPiecePosition.y - 1 >= 0 && (a_board[m_currentPiecePosition.x + 2][m_currentPiecePosition.y - 1] < 0 || a_board[m_currentPiecePosition.x + 2][m_currentPiecePosition.y - 1] == 0)) {
                    m_circleBoard[m_currentPiecePosition.x + 2][m_currentPiecePosition.y - 1] = true;
                    if (a_board[m_currentPiecePosition.x + 2][m_currentPiecePosition.y - 1] < 0)
                        m_canTakeBoard[m_currentPiecePosition.x + 2][m_currentPiecePosition.y - 1] = a_board[m_currentPiecePosition.x + 2][m_currentPiecePosition.y - 1];
                }
                if (m_currentPiecePosition.y + 1 <= 7 && (a_board[m_currentPiecePosition.x + 2][m_currentPiecePosition.y + 1] < 0 || a_board[m_currentPiecePosition.x + 2][m_currentPiecePosition.y + 1] == 0)) {
                    m_circleBoard[m_currentPiecePosition.x + 2][m_currentPiecePosition.y + 1] = true;
                    if (a_board[m_currentPiecePosition.x + 2][m_currentPiecePosition.y + 1] < 0)
                        m_canTakeBoard[m_currentPiecePosition.x + 2][m_currentPiecePosition.y + 1] = a_board[m_currentPiecePosition.x + 2][m_currentPiecePosition.y + 1];
                }
            }
            if (m_currentPiecePosition.y + 2 <= 7) {
                if (m_currentPiecePosition.x - 1 >= 0 && (a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 2] < 0 || a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 2] == 0)) {
                    m_circleBoard[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 2] = true;
                    if (a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 2] < 0)
                        m_canTakeBoard[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 2] = a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 2];
                }
                if (m_currentPiecePosition.x + 1 <= 7 && (a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 2] < 0 || a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 2] == 0)) {
                    m_circleBoard[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 2] = true;
                    if (a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 2] < 0)
                        m_canTakeBoard[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 2] = a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 2];
                }
            }
            if (m_currentPiecePosition.y - 2 >= 0) {
                if (m_currentPiecePosition.x - 1 >= 0 && (a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 2] < 0 || a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 2] == 0)) {
                    m_circleBoard[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 2] = true;
                    if (a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 2] < 0)
                        m_canTakeBoard[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 2] = a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 2];
                }
                if (m_currentPiecePosition.x + 1 <= 7 && (a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 2] < 0 || a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 2] == 0)) {
                    m_circleBoard[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 2] = true;
                    if (a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 2] < 0)
                        m_canTakeBoard[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 2] = a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 2];
                }
            }

        }
        else if (m_currentPieceClicked == 30 || m_currentPieceClicked == 31) {
            for (int i = m_currentPiecePosition.x, j = m_currentPiecePosition.y; i >= 0 && j >= 0; i--, j--) {
                if (i == m_currentPiecePosition.x && j == m_currentPiecePosition.y)
                    continue;
                if (a_board[i][j] > 0)
                    break;
                if (a_board[i][j] < 0) {
                    m_circleBoard[i][j] = true;
                    m_canTakeBoard[i][j] = a_board[i][j];
                    break;
                }
                m_circleBoard[i][j] = true;
            }
            for (int i = m_currentPiecePosition.x, j = m_currentPiecePosition.y; i >= 0 && j <= 7; i--, j++) {
                if (i == m_currentPiecePosition.x && j == m_currentPiecePosition.y)
                    continue;
                if (a_board[i][j] > 0)
                    break;
                if (a_board[i][j] < 0) {
                    m_circleBoard[i][j] = true;
                    m_canTakeBoard[i][j] = a_board[i][j];
                    break;
                }
                m_circleBoard[i][j] = true;
            }
            for (int i = m_currentPiecePosition.x, j = m_currentPiecePosition.y; i <= 7 && j >= 0; i++, j--) {
                if (i == m_currentPiecePosition.x && j == m_currentPiecePosition.y)
                    continue;
                if (a_board[i][j] > 0)
                    break;
                if (a_board[i][j] < 0) {
                    m_circleBoard[i][j] = true;
                    m_canTakeBoard[i][j] = a_board[i][j];
                    break;
                }
                m_circleBoard[i][j] = true;
            }
            for (int i = m_currentPiecePosition.x, j = m_currentPiecePosition.y; i <= 7 && j <= 7; i++, j++) {
                if (i == m_currentPiecePosition.x && j == m_currentPiecePosition.y)
                    continue;
                if (a_board[i][j] > 0)
                    break;
                if (a_board[i][j] < 0) {
                    m_circleBoard[i][j] = true;
                    m_canTakeBoard[i][j] = a_board[i][j];
                    break;
                }
                m_circleBoard[i][j] = true;
            }
        }
        else if (m_currentPieceClicked == 40) {
            for (int i = m_currentPiecePosition.x, j = m_currentPiecePosition.y; i >= 0 && j >= 0; i--, j--) {
                if (i == m_currentPiecePosition.x && j == m_currentPiecePosition.y)
                    continue;
                if (a_board[i][j] > 0)
                    break;
                if (a_board[i][j] < 0) {
                    m_circleBoard[i][j] = true;
                    m_canTakeBoard[i][j] = a_board[i][j];
                    break;
                }
                m_circleBoard[i][j] = true;
            }
            for (int i = m_currentPiecePosition.x, j = m_currentPiecePosition.y; i >= 0 && j <= 7; i--, j++) {
                if (i == m_currentPiecePosition.x && j == m_currentPiecePosition.y)
                    continue;
                if (a_board[i][j] > 0)
                    break;
                if (a_board[i][j] < 0) {
                    m_circleBoard[i][j] = true;
                    m_canTakeBoard[i][j] = a_board[i][j];
                    break;
                }
                m_circleBoard[i][j] = true;
            }
            for (int i = m_currentPiecePosition.x, j = m_currentPiecePosition.y; i <= 7 && j >= 0; i++, j--) {
                if (i == m_currentPiecePosition.x && j == m_currentPiecePosition.y)
                    continue;
                if (a_board[i][j] > 0)
                    break;
                if (a_board[i][j] < 0) {
                    m_circleBoard[i][j] = true;
                    m_canTakeBoard[i][j] = a_board[i][j];
                    break;
                }
                m_circleBoard[i][j] = true;
            }
            for (int i = m_currentPiecePosition.x, j = m_currentPiecePosition.y; i <= 7 && j <= 7; i++, j++) {
                if (i == m_currentPiecePosition.x && j == m_currentPiecePosition.y)
                    continue;
                if (a_board[i][j] > 0)
                    break;
                if (a_board[i][j] < 0) {
                    m_circleBoard[i][j] = true;
                    m_canTakeBoard[i][j] = a_board[i][j];
                    break;
                }
                m_circleBoard[i][j] = true;
            }


            for (int i = m_currentPiecePosition.x; i >= 0; i--) {
                if (i == m_currentPiecePosition.x)
                    continue;
                if (a_board[i][m_currentPiecePosition.y] > 0)
                    break;
                if (a_board[i][m_currentPiecePosition.y] < 0) {
                    m_circleBoard[i][m_currentPiecePosition.y] = true;
                    m_canTakeBoard[i][m_currentPiecePosition.y] = a_board[i][m_currentPiecePosition.y];
                    break;
                }
                m_circleBoard[i][m_currentPiecePosition.y] = true;
            }
            for (int i = m_currentPiecePosition.x; i < 8; i++) {
                if (i == m_currentPiecePosition.x)
                    continue;
                if (a_board[i][m_currentPiecePosition.y] > 0)
                    break;
                if (a_board[i][m_currentPiecePosition.y] < 0) {
                    m_circleBoard[i][m_currentPiecePosition.y] = true;
                    m_canTakeBoard[i][m_currentPiecePosition.y] = a_board[i][m_currentPiecePosition.y];
                    break;
                }
                m_circleBoard[i][m_currentPiecePosition.y] = true;
            }
            for (int i = m_currentPiecePosition.y; i < 8; i++) {
                if (i == m_currentPiecePosition.y)
                    continue;
                if (a_board[m_currentPiecePosition.x][i] > 0)
                    break;
                if (a_board[m_currentPiecePosition.x][i] < 0) {
                    m_circleBoard[m_currentPiecePosition.x][i] = true;
                    m_canTakeBoard[m_currentPiecePosition.x][i] = a_board[m_currentPiecePosition.x][i];
                    break;
                }
                m_circleBoard[m_currentPiecePosition.x][i] = true;
            }
            for (int i = m_currentPiecePosition.y; i >= 0; i--) {
                if (i == m_currentPiecePosition.y)
                    continue;
                if (a_board[m_currentPiecePosition.x][i] > 0)
                    break;
                if (a_board[m_currentPiecePosition.x][i] < 0) {
                    m_circleBoard[m_currentPiecePosition.x][i] = true;
                    m_canTakeBoard[m_currentPiecePosition.x][i] = a_board[m_currentPiecePosition.x][i];
                    break;
                }
                m_circleBoard[m_currentPiecePosition.x][i] = true;
            }
        }
        else if (m_currentPieceClicked == 50) {
            if (m_currentPiecePosition.x - 1 >= 0) {
                if (a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y] < 0 || a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y] == 0) {
                    m_circleBoard[m_currentPiecePosition.x - 1][m_currentPiecePosition.y] = true;
                    if (a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y] < 0)
                        m_canTakeBoard[m_currentPiecePosition.x - 1][m_currentPiecePosition.y] = a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y];
                }
                    
                if (m_currentPiecePosition.y - 1 >= 0) {
                    if (a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 1] < 0 || a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 1] == 0)
                        m_circleBoard[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 1] = true;
                    if (a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 1] < 0)
                        m_canTakeBoard[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 1] = a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 1];
                }
                if (m_currentPiecePosition.y + 1 <= 7) {
                    if (a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 1] < 0 || a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 1] == 0)
                        m_circleBoard[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 1] = true;
                    if (a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 1] < 0)
                        m_canTakeBoard[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 1] = a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 1];
                }
            }
            if (m_currentPiecePosition.x + 1 <= 7) {
                if (a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y] < 0 || a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y] == 0) {
                    m_circleBoard[m_currentPiecePosition.x + 1][m_currentPiecePosition.y] = true;
                    if (a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y] < 0)
                        m_canTakeBoard[m_currentPiecePosition.x + 1][m_currentPiecePosition.y] = a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y];
                }
                    
                if (m_currentPiecePosition.y - 1 >= 0) {
                    if (a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 1] < 0 || a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 1] == 0)
                        m_circleBoard[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 1] = true;
                    if (a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 1] < 0)
                        m_canTakeBoard[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 1] = a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 1];
                }
                if (m_currentPiecePosition.y + 1 <= 7) {
                    if (a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 1] < 0 || a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 1] == 0)
                        m_circleBoard[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 1] = true;
                    if (a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 1] < 0)
                        m_canTakeBoard[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 1] = a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 1];
                }
            }

            if (m_currentPiecePosition.y - 1 >= 0) {
                if (a_board[m_currentPiecePosition.x][m_currentPiecePosition.y - 1] < 0 || a_board[m_currentPiecePosition.x][m_currentPiecePosition.y - 1] == 0)
                    m_circleBoard[m_currentPiecePosition.x][m_currentPiecePosition.y - 1] = true;
                if (a_board[m_currentPiecePosition.x][m_currentPiecePosition.y - 1] < 0)
                    m_canTakeBoard[m_currentPiecePosition.x][m_currentPiecePosition.y - 1] = a_board[m_currentPiecePosition.x][m_currentPiecePosition.y - 1];
            }
            if (m_currentPiecePosition.y + 1 <= 7) {
                if (a_board[m_currentPiecePosition.x][m_currentPiecePosition.y + 1] < 0 || a_board[m_currentPiecePosition.x][m_currentPiecePosition.y + 1] == 0)
                    m_circleBoard[m_currentPiecePosition.x][m_currentPiecePosition.y + 1] = true;
                if (a_board[m_currentPiecePosition.x][m_currentPiecePosition.y + 1] < 0)
                    m_canTakeBoard[m_currentPiecePosition.x][m_currentPiecePosition.y + 1] = a_board[m_currentPiecePosition.x][m_currentPiecePosition.y + 1];
            }
        }
        if (m_currentPieceClicked <= -60 && m_currentPieceClicked >= -67) {
            if (m_currentPiecePosition.x == 1) {
                if (a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y] == 0)
                    m_circleBoard[m_currentPiecePosition.x + 1][m_currentPiecePosition.y] = true;
                if (a_board[m_currentPiecePosition.x + 2][m_currentPiecePosition.y] == 0)
                    m_circleBoard[m_currentPiecePosition.x + 2][m_currentPiecePosition.y] = true;
                if (m_currentPiecePosition.x < 7 && m_currentPiecePosition.y > 0 && a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 1] > 0) {
                    m_circleBoard[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 1] = true;
                    if (a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 1] > 0)
                        m_canTakeBoard[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 1] = a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 1];
                }
                    
                if (m_currentPiecePosition.x < 7 && m_currentPiecePosition.y < 8 && a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 1] > 0) {
                    m_circleBoard[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 1] = true;
                    if (a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 1] > 0)
                        m_canTakeBoard[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 1] = a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 1];
                }
                    

            }
            else {
                if (m_currentPiecePosition.x + 1 < 8 && a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y] == 0)
                    m_circleBoard[m_currentPiecePosition.x + 1][m_currentPiecePosition.y] = true;
                if (m_currentPiecePosition.x < 7 && m_currentPiecePosition.y > 0 && a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 1] > 0) {
                    m_circleBoard[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 1] = true;
                    if (a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 1] > 0)
                        m_canTakeBoard[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 1] = a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 1];
                }
                    
                if (m_currentPiecePosition.x < 7 && m_currentPiecePosition.y < 7 && a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 1] > 0) {
                    m_circleBoard[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 1] = true;
                    if (a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 1] > 0)
                        m_canTakeBoard[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 1] = a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 1];
                }
                    
            }
        }
        else if (m_currentPieceClicked == -10 || m_currentPieceClicked == -11) {
            for (int i = m_currentPiecePosition.x; i >= 0; i--) {
                if (i == m_currentPiecePosition.x)
                    continue;
                if (a_board[i][m_currentPiecePosition.y] < 0)
                    break;
                if (a_board[i][m_currentPiecePosition.y] > 0) {
                    m_circleBoard[i][m_currentPiecePosition.y] = true;
                    m_canTakeBoard[i][m_currentPiecePosition.y] = a_board[i][m_currentPiecePosition.y];
                    break;
                }
                m_circleBoard[i][m_currentPiecePosition.y] = true;
            }
            for (int i = m_currentPiecePosition.x; i < 8; i++) {
                if (i == m_currentPiecePosition.x)
                    continue;
                if (a_board[i][m_currentPiecePosition.y] < 0)
                    break;
                if (a_board[i][m_currentPiecePosition.y] > 0) {
                    m_circleBoard[i][m_currentPiecePosition.y] = true;
                    m_canTakeBoard[i][m_currentPiecePosition.y] = a_board[i][m_currentPiecePosition.y];
                    break;
                }
                m_circleBoard[i][m_currentPiecePosition.y] = true;
            }
            for (int i = m_currentPiecePosition.y; i < 8; i++) {
                if (i == m_currentPiecePosition.y)
                    continue;
                if (a_board[m_currentPiecePosition.x][i] < 0)
                    break;
                if (a_board[m_currentPiecePosition.x][i] > 0) {
                    m_circleBoard[m_currentPiecePosition.x][i] = true;
                    m_canTakeBoard[m_currentPiecePosition.x][i] = a_board[m_currentPiecePosition.x][i];
                    break;
                }
                m_circleBoard[m_currentPiecePosition.x][i] = true;
            }
            for (int i = m_currentPiecePosition.y; i >= 0; i--) {
                if (i == m_currentPiecePosition.y)
                    continue;
                if (a_board[m_currentPiecePosition.x][i] < 0)
                    break;
                if (a_board[m_currentPiecePosition.x][i] > 0) {
                    m_circleBoard[m_currentPiecePosition.x][i] = true;
                    m_canTakeBoard[m_currentPiecePosition.x][i] = a_board[m_currentPiecePosition.x][i];
                    break;
                }
                m_circleBoard[m_currentPiecePosition.x][i] = true;
            }


        }
        else if (m_currentPieceClicked == -20 || m_currentPieceClicked == -21) {
            if (m_currentPiecePosition.x - 2 >= 0) {
                if (m_currentPiecePosition.y - 1 >= 0 && (a_board[m_currentPiecePosition.x - 2][m_currentPiecePosition.y - 1] > 0 || a_board[m_currentPiecePosition.x - 2][m_currentPiecePosition.y - 1] == 0)) {
                    m_circleBoard[m_currentPiecePosition.x - 2][m_currentPiecePosition.y - 1] = true;
                    if (a_board[m_currentPiecePosition.x - 2][m_currentPiecePosition.y - 1] > 0)
                        m_canTakeBoard[m_currentPiecePosition.x - 2][m_currentPiecePosition.y - 1] = a_board[m_currentPiecePosition.x - 2][m_currentPiecePosition.y - 1];
                }
                if (m_currentPiecePosition.y + 1 <= 7 && (a_board[m_currentPiecePosition.x - 2][m_currentPiecePosition.y + 1] > 0 || a_board[m_currentPiecePosition.x - 2][m_currentPiecePosition.y + 1] == 0)) {
                    m_circleBoard[m_currentPiecePosition.x - 2][m_currentPiecePosition.y + 1] = true;
                    if (a_board[m_currentPiecePosition.x - 2][m_currentPiecePosition.y + 1] > 0)
                        m_canTakeBoard[m_currentPiecePosition.x - 2][m_currentPiecePosition.y + 1] = a_board[m_currentPiecePosition.x - 2][m_currentPiecePosition.y + 1];
                }
            }
            if (m_currentPiecePosition.x + 2 <= 7) {
                if (m_currentPiecePosition.y - 1 >= 0 && (a_board[m_currentPiecePosition.x + 2][m_currentPiecePosition.y - 1] > 0 || a_board[m_currentPiecePosition.x + 2][m_currentPiecePosition.y - 1] == 0)) {
                    m_circleBoard[m_currentPiecePosition.x + 2][m_currentPiecePosition.y - 1] = true;
                    if (a_board[m_currentPiecePosition.x + 2][m_currentPiecePosition.y - 1] > 0)
                        m_canTakeBoard[m_currentPiecePosition.x + 2][m_currentPiecePosition.y - 1] = a_board[m_currentPiecePosition.x + 2][m_currentPiecePosition.y - 1];
                }
                if (m_currentPiecePosition.y + 1 <= 7 && (a_board[m_currentPiecePosition.x + 2][m_currentPiecePosition.y + 1] > 0 || a_board[m_currentPiecePosition.x + 2][m_currentPiecePosition.y + 1] == 0)) {
                    m_circleBoard[m_currentPiecePosition.x + 2][m_currentPiecePosition.y + 1] = true;
                    if (a_board[m_currentPiecePosition.x + 2][m_currentPiecePosition.y + 1] > 0)
                        m_canTakeBoard[m_currentPiecePosition.x + 2][m_currentPiecePosition.y + 1] = a_board[m_currentPiecePosition.x + 2][m_currentPiecePosition.y + 1];
                }
            }
            if (m_currentPiecePosition.y + 2 <= 7) {
                if (m_currentPiecePosition.x - 1 >= 0 && (a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 2] > 0 || a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 2] == 0)) {
                    m_circleBoard[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 2] = true;
                    if (a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 2] > 0)
                        m_canTakeBoard[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 2] = a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 2];
                }
                if (m_currentPiecePosition.x + 1 <= 7 && (a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 2] > 0 || a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 2] == 0)) {
                    m_circleBoard[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 2] = true;
                    if (a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 2] > 0)
                        m_canTakeBoard[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 2] = a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 2];
                }
            }
            if (m_currentPiecePosition.y - 2 >= 0) {
                if (m_currentPiecePosition.x - 1 >= 0 && (a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 2] > 0 || a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 2] == 0)) {
                    m_circleBoard[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 2] = true;
                    if (a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 2] > 0)
                        m_canTakeBoard[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 2] = a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 2];
                }
                if (m_currentPiecePosition.x + 1 <= 7 && (a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 2] > 0 || a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 2] == 0)) {
                    m_circleBoard[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 2] = true;
                    if (a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 2] > 0)
                        m_canTakeBoard[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 2] = a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 2];
                }
            }


        }
        else if (m_currentPieceClicked == -30 || m_currentPieceClicked == -31) {
            for (int i = m_currentPiecePosition.x, j = m_currentPiecePosition.y; i >= 0 && j >= 0; i--, j--) {
                if (i == m_currentPiecePosition.x && j == m_currentPiecePosition.y)
                    continue;
                if (a_board[i][j] < 0)
                    break;
                if (a_board[i][j] > 0) {
                    m_circleBoard[i][j] = true;
                    m_canTakeBoard[i][j] = a_board[i][j];
                    break;
                }
                m_circleBoard[i][j] = true;
            }
            for (int i = m_currentPiecePosition.x, j = m_currentPiecePosition.y; i >= 0 && j <= 7; i--, j++) {
                if (i == m_currentPiecePosition.x && j == m_currentPiecePosition.y)
                    continue;
                if (a_board[i][j] < 0)
                    break;
                if (a_board[i][j] > 0) {
                    m_circleBoard[i][j] = true;
                    m_canTakeBoard[i][j] = a_board[i][j];
                    break;
                }
                m_circleBoard[i][j] = true;
            }
            for (int i = m_currentPiecePosition.x, j = m_currentPiecePosition.y; i <= 7 && j >= 0; i++, j--) {
                if (i == m_currentPiecePosition.x && j == m_currentPiecePosition.y)
                    continue;
                if (a_board[i][j] < 0)
                    break;
                if (a_board[i][j] > 0) {
                    m_circleBoard[i][j] = true;
                    m_canTakeBoard[i][j] = a_board[i][j];
                    break;
                }
                m_circleBoard[i][j] = true;
            }
            for (int i = m_currentPiecePosition.x, j = m_currentPiecePosition.y; i <= 7 && j <= 7; i++, j++) {
                if (i == m_currentPiecePosition.x && j == m_currentPiecePosition.y)
                    continue;
                if (a_board[i][j] < 0)
                    break;
                if (a_board[i][j] > 0) {
                    m_circleBoard[i][j] = true;
                    m_canTakeBoard[i][j] = a_board[i][j];
                    break;
                }
                m_circleBoard[i][j] = true;
            }

        }
        else if (m_currentPieceClicked == -40) {
            for (int i = m_currentPiecePosition.x; i >= 0; i--) {
                if (i == m_currentPiecePosition.x)
                    continue;
                if (a_board[i][m_currentPiecePosition.y] < 0)
                    break;
                if (a_board[i][m_currentPiecePosition.y] > 0) {
                    m_circleBoard[i][m_currentPiecePosition.y] = true;
                    m_canTakeBoard[i][m_currentPiecePosition.y] = a_board[i][m_currentPiecePosition.y];
                    break;
                }
                m_circleBoard[i][m_currentPiecePosition.y] = true;
            }
            for (int i = m_currentPiecePosition.x; i < 8; i++) {
                if (i == m_currentPiecePosition.x)
                    continue;
                if (a_board[i][m_currentPiecePosition.y] < 0)
                    break;
                if (a_board[i][m_currentPiecePosition.y] > 0) {
                    m_circleBoard[i][m_currentPiecePosition.y] = true;
                    m_canTakeBoard[i][m_currentPiecePosition.y] = a_board[i][m_currentPiecePosition.y];
                    break;
                }
                m_circleBoard[i][m_currentPiecePosition.y] = true;
            }
            for (int i = m_currentPiecePosition.y; i < 8; i++) {
                if (i == m_currentPiecePosition.y)
                    continue;
                if (a_board[m_currentPiecePosition.x][i] < 0)
                    break;
                if (a_board[m_currentPiecePosition.x][i] > 0) {
                    m_circleBoard[m_currentPiecePosition.x][i] = true;
                    m_canTakeBoard[m_currentPiecePosition.x][i] = a_board[m_currentPiecePosition.x][i];
                    break;
                }
                m_circleBoard[m_currentPiecePosition.x][i] = true;
            }
            for (int i = m_currentPiecePosition.y; i >= 0; i--) {
                if (i == m_currentPiecePosition.y)
                    continue;
                if (a_board[m_currentPiecePosition.x][i] < 0)
                    break;
                if (a_board[m_currentPiecePosition.x][i] > 0) {
                    m_circleBoard[m_currentPiecePosition.x][i] = true;
                    m_canTakeBoard[m_currentPiecePosition.x][i] = a_board[m_currentPiecePosition.x][i];
                    break;
                }
                m_circleBoard[m_currentPiecePosition.x][i] = true;
            }
            for (int i = m_currentPiecePosition.x, j = m_currentPiecePosition.y; i >= 0 && j >= 0; i--, j--) {
                if (i == m_currentPiecePosition.x && j == m_currentPiecePosition.y)
                    continue;
                if (a_board[i][j] < 0)
                    break;
                if (a_board[i][j] > 0) {
                    m_circleBoard[i][j] = true;
                    m_canTakeBoard[i][j] = a_board[i][j];
                    break;
                }
                m_circleBoard[i][j] = true;
            }
            for (int i = m_currentPiecePosition.x, j = m_currentPiecePosition.y; i >= 0 && j <= 7; i--, j++) {
                if (i == m_currentPiecePosition.x && j == m_currentPiecePosition.y)
                    continue;
                if (a_board[i][j] < 0)
                    break;
                if (a_board[i][j] > 0) {
                    m_circleBoard[i][j] = true;
                    m_canTakeBoard[i][j] = a_board[i][j];
                    break;
                }
                m_circleBoard[i][j] = true;
            }
            for (int i = m_currentPiecePosition.x, j = m_currentPiecePosition.y; i <= 7 && j >= 0; i++, j--) {
                if (i == m_currentPiecePosition.x && j == m_currentPiecePosition.y)
                    continue;
                if (a_board[i][j] < 0)
                    break;
                if (a_board[i][j] > 0) {
                    m_circleBoard[i][j] = true;
                    m_canTakeBoard[i][j] = a_board[i][j];
                    break;
                }
                m_circleBoard[i][j] = true;
            }
            for (int i = m_currentPiecePosition.x, j = m_currentPiecePosition.y; i <= 7 && j <= 7; i++, j++) {
                if (i == m_currentPiecePosition.x && j == m_currentPiecePosition.y)
                    continue;
                if (a_board[i][j] < 0)
                    break;
                if (a_board[i][j] > 0) {
                    m_circleBoard[i][j] = true;
                    m_canTakeBoard[i][j] = a_board[i][j];
                    break;
                }
                m_circleBoard[i][j] = true;
            }
        }
        else if (m_currentPieceClicked == -50) {
            if (m_currentPiecePosition.x - 1 >= 0) {
                if (a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y] > 0 || a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y] == 0) {
                    m_circleBoard[m_currentPiecePosition.x - 1][m_currentPiecePosition.y] = true;
                    if (a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y] > 0)
                        m_canTakeBoard[m_currentPiecePosition.x - 1][m_currentPiecePosition.y] = a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y];
                }

                if (m_currentPiecePosition.y - 1 >= 0) {
                    if (a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 1] > 0 || a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 1] == 0)
                        m_circleBoard[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 1] = true;
                    if (a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 1] > 0)
                        m_canTakeBoard[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 1] = a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 1];
                }
                if (m_currentPiecePosition.y + 1 <= 7) {
                    if (a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 1] > 0 || a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 1] == 0)
                        m_circleBoard[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 1] = true;
                    if (a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 1] > 0)
                        m_canTakeBoard[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 1] = a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 1];
                }
            }
            if (m_currentPiecePosition.x + 1 <= 7) {
                if (a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y] > 0 || a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y] == 0) {
                    m_circleBoard[m_currentPiecePosition.x + 1][m_currentPiecePosition.y] = true;
                    if (a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y] > 0)
                        m_canTakeBoard[m_currentPiecePosition.x + 1][m_currentPiecePosition.y] = a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y];
                }

                if (m_currentPiecePosition.y - 1 >= 0) {
                    if (a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 1] > 0 || a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 1] == 0)
                        m_circleBoard[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 1] = true;
                    if (a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 1] > 0)
                        m_canTakeBoard[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 1] = a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 1];
                }
                if (m_currentPiecePosition.y + 1 <= 7) {
                    if (a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 1] > 0 || a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 1] == 0)
                        m_circleBoard[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 1] = true;
                    if (a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 1] > 0)
                        m_canTakeBoard[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 1] = a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 1];
                }
            }

            if (m_currentPiecePosition.y - 1 >= 0) {
                if (a_board[m_currentPiecePosition.x][m_currentPiecePosition.y - 1] > 0 || a_board[m_currentPiecePosition.x][m_currentPiecePosition.y - 1] == 0)
                    m_circleBoard[m_currentPiecePosition.x][m_currentPiecePosition.y - 1] = true;
                if (a_board[m_currentPiecePosition.x][m_currentPiecePosition.y - 1] > 0)
                    m_canTakeBoard[m_currentPiecePosition.x][m_currentPiecePosition.y - 1] = a_board[m_currentPiecePosition.x][m_currentPiecePosition.y - 1];
            }
            if (m_currentPiecePosition.y + 1 <= 7) {
                if (a_board[m_currentPiecePosition.x][m_currentPiecePosition.y + 1] > 0 || a_board[m_currentPiecePosition.x][m_currentPiecePosition.y + 1] == 0)
                    m_circleBoard[m_currentPiecePosition.x][m_currentPiecePosition.y + 1] = true;
                if (a_board[m_currentPiecePosition.x][m_currentPiecePosition.y + 1] > 0)
                    m_canTakeBoard[m_currentPiecePosition.x][m_currentPiecePosition.y + 1] = a_board[m_currentPiecePosition.x][m_currentPiecePosition.y + 1];
            }
        }
    }
}
bool Chess::loadAssets() {
    // load board
    if (!t_board.loadFromFile("assets/_composite.png")) {
        std::cout << "Error opening board!" << std::endl;
        return false;
    }
    m_board.setTexture(t_board);

    // load pieces
    if (!t_blackRook.loadFromFile("assets/b_rook_png_128px.png") || !t_blackKnight.loadFromFile("assets/b_knight_png_128px.png") || !t_blackBishop.loadFromFile("assets/b_bishop_png_128px.png") ||
        !t_blackQueen.loadFromFile("assets/b_queen_png_128px.png") || !t_blackKing.loadFromFile("assets/b_king_png_128px.png") || !t_blackPawn.loadFromFile("assets/b_pawn_png_128px.png") || 
        !t_whiteRook.loadFromFile("assets/w_rook_png_128px.png") || !t_whiteKnight.loadFromFile("assets/w_knight_png_128px.png") || !t_whiteBishop.loadFromFile("assets/w_bishop_png_128px.png") ||
        !t_whiteQueen.loadFromFile("assets/w_queen_png_128px.png") || !t_whiteKing.loadFromFile("assets/w_king_png_128px.png") || !t_whitePawn.loadFromFile("assets/w_pawn_png_128px.png")) {
        std::cout << "Error opening pieces!" << std::endl;
        return false;
    }

    if (!b_pieceMove.loadFromFile("sounds/move-self.wav") || !b_capture.loadFromFile("sounds/capture.wav")) {
        std::cout << "Error opening sound files!" << std::endl;
        return false;
    }
    s_pieceMove.setBuffer(b_pieceMove);
    s_capture.setBuffer(b_capture);

    /*
    * m_pieces[0] -> black rook
    * m_pieces[1] -> black knight
    * m_pieces[2] -> black bishop
    * m_pieces[3] -> black queen
    * m_pieces[4] -> black king
    * m_pieces[5] -> black bishop
    * m_pieces[6] -> black knight
    * m_pieces[7] -> black rook
    * m_pieces[8] - m_pieces[15] -> black pawn
    * 
    * m_pieces[16] -> white rook
    * m_pieces[17] -> white knight
    * m_pieces[18] -> white bishop
    * m_pieces[19] -> white queen
    * m_pieces[20] -> white king
    * m_pieces[21] -> white bishop
    * m_pieces[22] -> white knight
    * m_pieces[23] -> white rook
    * m_pieces[24] - m_pieces[31] -> white pawn
    */

    sf::Sprite blackRook;
    blackRook.setTexture(t_blackRook);
    m_pieces.push_back(blackRook);

    sf::Sprite blackKnight;
    blackKnight.setTexture(t_blackKnight);
    m_pieces.push_back(blackKnight);

    sf::Sprite blackBishop;
    blackBishop.setTexture(t_blackBishop);
    m_pieces.push_back(blackBishop);

    sf::Sprite blackQueen;
    blackQueen.setTexture(t_blackQueen);
    m_pieces.push_back(blackQueen);

    sf::Sprite blackKing;
    blackKing.setTexture(t_blackKing);
    m_pieces.push_back(blackKing);

    sf::Sprite blackBishop2;
    blackBishop2.setTexture(t_blackBishop);
    m_pieces.push_back(blackBishop2);

    sf::Sprite blackKnight2;
    blackKnight2.setTexture(t_blackKnight);
    m_pieces.push_back(blackKnight2);

    sf::Sprite blackRook2;
    blackRook2.setTexture(t_blackRook);
    m_pieces.push_back(blackRook2);


    for (int i = 0; i < fields; i++) {
        sf::Sprite blackPawn;
        blackPawn.setTexture(t_blackPawn);
        m_pieces.push_back(blackPawn);
    }


    sf::Sprite whiteRook;
    whiteRook.setTexture(t_whiteRook);
    m_pieces.push_back(whiteRook);

    sf::Sprite whiteKnight;
    whiteKnight.setTexture(t_whiteKnight);
    m_pieces.push_back(whiteKnight);

    sf::Sprite whiteBishop;
    whiteBishop.setTexture(t_whiteBishop);
    m_pieces.push_back(whiteBishop);

    sf::Sprite whiteQueen;
    whiteQueen.setTexture(t_whiteQueen);
    m_pieces.push_back(whiteQueen);

    sf::Sprite whiteKing;
    whiteKing.setTexture(t_whiteKing);
    m_pieces.push_back(whiteKing);

    sf::Sprite whiteBishop2;
    whiteBishop2.setTexture(t_whiteBishop);
    m_pieces.push_back(whiteBishop2);

    sf::Sprite whiteKnight2;
    whiteKnight2.setTexture(t_whiteKnight);
    m_pieces.push_back(whiteKnight2);

    sf::Sprite whiteRook2;
    whiteRook2.setTexture(t_whiteRook);
    m_pieces.push_back(whiteRook2);


    for (int i = 0; i < fields; i++) {
        sf::Sprite whitePawn;
        whitePawn.setTexture(t_whitePawn);
        m_pieces.push_back(whitePawn);
    }
    
    for (auto& p : m_pieces) {
        p.setScale(0.5, 0.5);
    }

    return true;
}
void Chess::drawBoard() {
   /*
    * Initialize starting position
    * Black Pieces:
    *       rook      ->  -10 and -11
    *       knight    ->  -20 and -21
    *       bishop    ->  -30 and -31
    *       queen     ->  -40
    *       king      ->  -50
    *       pawn      ->  -60 - -67
    * 
    * White Pieces:
    *       rook      ->   10 and 11
    *       knight    ->   20 and 21
    *       bishop    ->   30 and 31
    *       queen     ->   40
    *       king      ->   50
    *       pawn      ->   60 - 67
    * 
    * Empty field     ->   0
    * 
    */

    /*
    * m_pieces[0] -> black rook
    * m_pieces[1] -> black knight
    * m_pieces[2] -> black bishop
    * m_pieces[3] -> black queen
    * m_pieces[4] -> black king
    * m_pieces[5] -> black bishop
    * m_pieces[6] -> black knight
    * m_pieces[7] -> black rook
    * m_pieces[8] - m_pieces[15] -> black pawn
    *
    * m_pieces[16] -> white rook
    * m_pieces[17] -> white knight
    * m_pieces[18] -> white bishop
    * m_pieces[19] -> white queen
    * m_pieces[20] -> white king
    * m_pieces[21] -> white bishop
    * m_pieces[22] -> white knight
    * m_pieces[23] -> white rook
    * m_pieces[24] - m_pieces[31] -> white pawn
    */

    int offset = 16;

    for (int i = 0; i < fields; i++) {
        for (int j = 0; j < fields; j++) {
            if (a_board[i][j] == -10)
                m_pieces[0].setPosition(tileSize * j + offset, tileSize * i + offset);
            if (a_board[i][j] == -20)
                m_pieces[1].setPosition(tileSize * j + offset, tileSize * i + offset);
            if (a_board[i][j] == -30)
                m_pieces[2].setPosition(tileSize * j + offset, tileSize * i + offset);
            if (a_board[i][j] == -40)
                m_pieces[3].setPosition(tileSize * j + offset, tileSize * i + offset);
            if (a_board[i][j] == -50)
                m_pieces[4].setPosition(tileSize * j + offset, tileSize * i + offset);
            if (a_board[i][j] == -31)
                m_pieces[5].setPosition(tileSize * j + offset, tileSize * i + offset);
            if (a_board[i][j] == -21)
                m_pieces[6].setPosition(tileSize * j + offset, tileSize * i + offset);
            if (a_board[i][j] == -11)
                m_pieces[7].setPosition(tileSize * j + offset, tileSize * i + offset);
            if (a_board[i][j] == -60)
                m_pieces[8].setPosition(tileSize * j + offset, tileSize * i + offset);
            if (a_board[i][j] == -61)
                m_pieces[9].setPosition(tileSize * j + offset, tileSize * i + offset);
            if (a_board[i][j] == -62)
                m_pieces[10].setPosition(tileSize * j + offset, tileSize * i + offset);
            if (a_board[i][j] == -63)
                m_pieces[11].setPosition(tileSize * j + offset, tileSize * i + offset);
            if (a_board[i][j] == -64)
                m_pieces[12].setPosition(tileSize * j + offset, tileSize * i + offset);
            if (a_board[i][j] == -65)
                m_pieces[13].setPosition(tileSize * j + offset, tileSize * i + offset);
            if (a_board[i][j] == -66)
                m_pieces[14].setPosition(tileSize * j + offset, tileSize * i + offset);
            if (a_board[i][j] == -67)
                m_pieces[15].setPosition(tileSize * j + offset, tileSize * i + offset);

            if (a_board[i][j] == 10)
                m_pieces[16].setPosition(tileSize * j + offset, tileSize * i + offset);
            if (a_board[i][j] == 20)
                m_pieces[17].setPosition(tileSize * j + offset, tileSize * i + offset);
            if (a_board[i][j] == 30)
                m_pieces[18].setPosition(tileSize * j + offset, tileSize * i + offset);
            if (a_board[i][j] == 40)
                m_pieces[19].setPosition(tileSize * j + offset, tileSize * i + offset);
            if (a_board[i][j] == 50)
                m_pieces[20].setPosition(tileSize * j + offset, tileSize * i + offset);
            if (a_board[i][j] == 31)
                m_pieces[21].setPosition(tileSize * j + offset, tileSize * i + offset);
            if (a_board[i][j] == 21)
                m_pieces[22].setPosition(tileSize * j + offset, tileSize * i + offset);
            if (a_board[i][j] == 11)
                m_pieces[23].setPosition(tileSize * j + offset, tileSize * i + offset);
            if (a_board[i][j] == 60)
                m_pieces[24].setPosition(tileSize * j + offset, tileSize * i + offset);
            if (a_board[i][j] == 61)
                m_pieces[25].setPosition(tileSize * j + offset, tileSize * i + offset);
            if (a_board[i][j] == 62)
                m_pieces[26].setPosition(tileSize * j + offset, tileSize * i + offset);
            if (a_board[i][j] == 63)
                m_pieces[27].setPosition(tileSize * j + offset, tileSize * i + offset);
            if (a_board[i][j] == 64)
                m_pieces[28].setPosition(tileSize * j + offset, tileSize * i + offset);
            if (a_board[i][j] == 65)
                m_pieces[29].setPosition(tileSize * j + offset, tileSize * i + offset);
            if (a_board[i][j] == 66)
                m_pieces[30].setPosition(tileSize * j + offset, tileSize * i + offset);
            if (a_board[i][j] == 67)
                m_pieces[31].setPosition(tileSize * j + offset, tileSize * i + offset);

        }
    }

}
void Chess::move(sf::RenderWindow& window) {

    int row = sf::Mouse::getPosition(window).y / tileSize;
    int col = sf::Mouse::getPosition(window).x / tileSize;


    if (!m_pieceClicked) {
        m_pieceClicked = true;
        m_currentPieceClicked = a_board[row][col];
        m_currentPiecePosition.x = row;
        m_currentPiecePosition.y = col;

        return;
    }

    if (m_whiteTurn && m_pieceClicked) {
        if (a_board[row][col] > 0) {

            m_currentPieceClicked = a_board[row][col];
            m_currentPiecePosition.x = row;
            m_currentPiecePosition.y = col;
            for (int i = 0; i < m_pieces.size(); i++) {
                m_pieces[i].setColor(sf::Color(255, 255, 255, 255));
            }
            for (int i = 0; i < fields; i++) {
                for (int j = 0; j < fields; j++) {
                    m_canTakeBoard[i][j] = 0;
                }

            }

            return;
        }
        
        m_pieceClicked = false;

        for (int i = 0; i < fields; i++) {
            for (int j = 0; j < fields; j++) {
                m_circleBoard[i][j] = false;
                m_canTakeBoard[i][j] = 0;
            }

        }
        for (int i = 0; i < m_pieces.size(); i++) {
            m_pieces[i].setColor(sf::Color(255, 255, 255, 255));
        }
        

        if (m_currentPieceClicked >= 60 && m_currentPieceClicked <= 67) {
            if (m_currentPiecePosition.x == 6) {
                if (a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y] == 0)
                    b_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y] = true;
                if (a_board[m_currentPiecePosition.x - 2][m_currentPiecePosition.y] == 0)
                    b_board[m_currentPiecePosition.x - 2][m_currentPiecePosition.y] = true;
                if (m_currentPiecePosition.x > 0 && m_currentPiecePosition.y > 0 && a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 1] < 0)
                    b_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 1] = true;
                if (m_currentPiecePosition.x > 0 && m_currentPiecePosition.y < 7 && a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 1] < 0)
                    b_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 1] = true;

                if (b_board[row][col]) {
                    deletePieces(row, col);
                    a_board[row][col] = m_currentPieceClicked;
                    a_board[m_currentPiecePosition.x][m_currentPiecePosition.y] = 0;
                    m_whiteTurn = false;
                    s_pieceMove.play();
                }

            }
            else {
                if (m_currentPiecePosition.x > 0 && a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y] == 0)
                    b_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y] = true;
                if (m_currentPiecePosition.x > 0 && m_currentPiecePosition.y > 0 && a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 1] < 0)
                    b_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 1] = true;
                if (m_currentPiecePosition.x > 0 && m_currentPiecePosition.y < 7 && a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 1] < 0)
                    b_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 1] = true;

                if (b_board[row][col]) {
                    deletePieces(row, col);
                    a_board[row][col] = m_currentPieceClicked;
                    a_board[m_currentPiecePosition.x][m_currentPiecePosition.y] = 0;
                    m_whiteTurn = false;
                    s_pieceMove.play();
                }
            }
        }
        else if (m_currentPieceClicked == 10 || m_currentPieceClicked == 11) {
            for (int i = m_currentPiecePosition.x; i >= 0; i--) {
                if (i == m_currentPiecePosition.x)
                    continue;
                if (a_board[i][m_currentPiecePosition.y] > 0)
                    break;
                if (a_board[i][m_currentPiecePosition.y] < 0) {
                    b_board[i][m_currentPiecePosition.y] = true;
                    break;
                }
                b_board[i][m_currentPiecePosition.y] = true;
            }
            for (int i = m_currentPiecePosition.x; i < 8; i++) {
                if (i == m_currentPiecePosition.x)
                    continue;
                if (a_board[i][m_currentPiecePosition.y] > 0)
                    break;
                if (a_board[i][m_currentPiecePosition.y] < 0) {
                    b_board[i][m_currentPiecePosition.y] = true;
                    break;
                }
                b_board[i][m_currentPiecePosition.y] = true;
            }
            for (int i = m_currentPiecePosition.y; i < 8; i++) {
                if (i == m_currentPiecePosition.y)
                    continue;
                if (a_board[m_currentPiecePosition.x][i] > 0)
                    break;
                if (a_board[m_currentPiecePosition.x][i] < 0) {
                    b_board[m_currentPiecePosition.x][i] = true;
                    break;
                }
                b_board[m_currentPiecePosition.x][i] = true;
            }
            for (int i = m_currentPiecePosition.y; i >= 0; i--) {
                if (i == m_currentPiecePosition.y)
                    continue;
                if (a_board[m_currentPiecePosition.x][i] > 0)
                    break;
                if (a_board[m_currentPiecePosition.x][i] < 0) {
                    b_board[m_currentPiecePosition.x][i] = true;
                    break;
                }
                b_board[m_currentPiecePosition.x][i] = true;
            }

            if (b_board[row][col]) {
                deletePieces(row, col);
                a_board[row][col] = m_currentPieceClicked;
                a_board[m_currentPiecePosition.x][m_currentPiecePosition.y] = 0;
                m_whiteTurn = false;
                s_pieceMove.play();
            }

        }
        else if (m_currentPieceClicked == 20 || m_currentPieceClicked == 21) {
            if (m_currentPiecePosition.x - 2 >= 0) {
                if (m_currentPiecePosition.y - 1 >= 0 && (a_board[m_currentPiecePosition.x - 2][m_currentPiecePosition.y - 1] < 0 || a_board[m_currentPiecePosition.x - 2][m_currentPiecePosition.y - 1] == 0)) {
                    b_board[m_currentPiecePosition.x - 2][m_currentPiecePosition.y - 1] = true;
                }
                if (m_currentPiecePosition.y + 1 <= 7 && (a_board[m_currentPiecePosition.x - 2][m_currentPiecePosition.y + 1] < 0 || a_board[m_currentPiecePosition.x - 2][m_currentPiecePosition.y + 1] == 0)) {
                    b_board[m_currentPiecePosition.x - 2][m_currentPiecePosition.y + 1] = true;
                }
            }
            if (m_currentPiecePosition.x + 2 <= 7) {
                if (m_currentPiecePosition.y - 1 >= 0 && (a_board[m_currentPiecePosition.x + 2][m_currentPiecePosition.y - 1] < 0 || a_board[m_currentPiecePosition.x + 2][m_currentPiecePosition.y - 1] == 0)) {
                    b_board[m_currentPiecePosition.x + 2][m_currentPiecePosition.y - 1] = true;
                }
                if (m_currentPiecePosition.y + 1 <= 7 && (a_board[m_currentPiecePosition.x + 2][m_currentPiecePosition.y + 1] < 0 || a_board[m_currentPiecePosition.x + 2][m_currentPiecePosition.y + 1] == 0)) {
                    b_board[m_currentPiecePosition.x + 2][m_currentPiecePosition.y + 1] = true;
                }
            }
            if (m_currentPiecePosition.y + 2 <= 7) {
                if (m_currentPiecePosition.x - 1 >= 0 && (a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 2] < 0 || a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 2] == 0)) {
                    b_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 2] = true;
                }
                if (m_currentPiecePosition.x + 1 <= 7 && (a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 2] < 0 || a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 2] == 0)) {
                    b_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 2] = true;
                }
            }
            if (m_currentPiecePosition.y - 2 >= 0) {
                if (m_currentPiecePosition.x - 1 >= 0 && (a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 2] < 0 || a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 2] == 0)) {
                    b_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 2] = true;
                }
                if (m_currentPiecePosition.x + 1 <= 7 && (a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 2] < 0 || a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 2] == 0)) {
                    b_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 2] = true;
                }
            }


            if (b_board[row][col]) {
                deletePieces(row, col);
                a_board[row][col] = m_currentPieceClicked;
                a_board[m_currentPiecePosition.x][m_currentPiecePosition.y] = 0;
                m_whiteTurn = false;
                s_pieceMove.play();
            }
        }
        else if (m_currentPieceClicked == 30 || m_currentPieceClicked == 31) {
            for (int i = m_currentPiecePosition.x, j = m_currentPiecePosition.y; i >= 0 && j >= 0; i--, j--) {
                if (i == m_currentPiecePosition.x && j == m_currentPiecePosition.y)
                    continue;
                if (a_board[i][j] > 0)
                    break;
                if (a_board[i][j] < 0) {
                    b_board[i][j] = true;
                    break;
                }
                b_board[i][j] = true;
            }
            for (int i = m_currentPiecePosition.x, j = m_currentPiecePosition.y; i >= 0 && j <= 7; i--, j++) {
                if (i == m_currentPiecePosition.x && j == m_currentPiecePosition.y)
                    continue;
                if (a_board[i][j] > 0)
                    break;
                if (a_board[i][j] < 0) {
                    b_board[i][j] = true;
                    break;
                }
                b_board[i][j] = true;
            }
            for (int i = m_currentPiecePosition.x, j = m_currentPiecePosition.y; i <= 7 && j >= 0; i++, j--) {
                if (i == m_currentPiecePosition.x && j == m_currentPiecePosition.y)
                    continue;
                if (a_board[i][j] > 0)
                    break;
                if (a_board[i][j] < 0) {
                    b_board[i][j] = true;
                    break;
                }
                b_board[i][j] = true;
            }
            for (int i = m_currentPiecePosition.x, j = m_currentPiecePosition.y; i <= 7 && j <= 7; i++, j++) {
                if (i == m_currentPiecePosition.x && j == m_currentPiecePosition.y)
                    continue;
                if (a_board[i][j] > 0)
                    break;
                if (a_board[i][j] < 0) {
                    b_board[i][j] = true;
                    break;
                }
                b_board[i][j] = true;
            }

            if (b_board[row][col]) {
                deletePieces(row, col);
                a_board[row][col] = m_currentPieceClicked;
                a_board[m_currentPiecePosition.x][m_currentPiecePosition.y] = 0;
                m_whiteTurn = false;
                s_pieceMove.play();
            }
        }
        else if (m_currentPieceClicked == 40) {
            for (int i = m_currentPiecePosition.x, j = m_currentPiecePosition.y; i >= 0 && j >= 0; i--, j--) {
                if (i == m_currentPiecePosition.x && j == m_currentPiecePosition.y)
                    continue;
                if (a_board[i][j] > 0)
                    break;
                if (a_board[i][j] < 0) {
                    b_board[i][j] = true;
                    break;
                }
                b_board[i][j] = true;
            }
            for (int i = m_currentPiecePosition.x, j = m_currentPiecePosition.y; i >= 0 && j <= 7; i--, j++) {
                if (i == m_currentPiecePosition.x && j == m_currentPiecePosition.y)
                    continue;
                if (a_board[i][j] > 0)
                    break;
                if (a_board[i][j] < 0) {
                    b_board[i][j] = true;
                    break;
                }
                b_board[i][j] = true;
            }
            for (int i = m_currentPiecePosition.x, j = m_currentPiecePosition.y; i <= 7 && j >= 0; i++, j--) {
                if (i == m_currentPiecePosition.x && j == m_currentPiecePosition.y)
                    continue;
                if (a_board[i][j] > 0)
                    break;
                if (a_board[i][j] < 0) {
                    b_board[i][j] = true;
                    break;
                }
                b_board[i][j] = true;
            }
            for (int i = m_currentPiecePosition.x, j = m_currentPiecePosition.y; i <= 7 && j <= 7; i++, j++) {
                if (i == m_currentPiecePosition.x && j == m_currentPiecePosition.y)
                    continue;
                if (a_board[i][j] > 0)
                    break;
                if (a_board[i][j] < 0) {
                    b_board[i][j] = true;
                    break;
                }
                b_board[i][j] = true;
            }
            for (int i = m_currentPiecePosition.x; i >= 0; i--) {
                if (i == m_currentPiecePosition.x)
                    continue;
                if (a_board[i][m_currentPiecePosition.y] > 0)
                    break;
                if (a_board[i][m_currentPiecePosition.y] < 0) {
                    b_board[i][m_currentPiecePosition.y] = true;
                    break;
                }
                b_board[i][m_currentPiecePosition.y] = true;
            }
            for (int i = m_currentPiecePosition.x; i < 8; i++) {
                if (i == m_currentPiecePosition.x)
                    continue;
                if (a_board[i][m_currentPiecePosition.y] > 0)
                    break;
                if (a_board[i][m_currentPiecePosition.y] < 0) {
                    b_board[i][m_currentPiecePosition.y] = true;
                    break;
                }
                b_board[i][m_currentPiecePosition.y] = true;
            }
            for (int i = m_currentPiecePosition.y; i < 8; i++) {
                if (i == m_currentPiecePosition.y)
                    continue;
                if (a_board[m_currentPiecePosition.x][i] > 0)
                    break;
                if (a_board[m_currentPiecePosition.x][i] < 0) {
                    b_board[m_currentPiecePosition.x][i] = true;
                    break;
                }
                b_board[m_currentPiecePosition.x][i] = true;
            }
            for (int i = m_currentPiecePosition.y; i >= 0; i--) {
                if (i == m_currentPiecePosition.y)
                    continue;
                if (a_board[m_currentPiecePosition.x][i] > 0)
                    break;
                if (a_board[m_currentPiecePosition.x][i] < 0) {
                    b_board[m_currentPiecePosition.x][i] = true;
                    break;
                }
                b_board[m_currentPiecePosition.x][i] = true;
            }


            if (b_board[row][col]) {
                deletePieces(row, col);
                a_board[row][col] = m_currentPieceClicked;
                a_board[m_currentPiecePosition.x][m_currentPiecePosition.y] = 0;
                m_whiteTurn = false;
                s_pieceMove.play();
            }
        }
        else if (m_currentPieceClicked == 50) {
            if (m_currentPiecePosition.x - 1 >= 0) {
                if (a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y] < 0 || a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y] == 0)
                    b_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y] = true;
                if (m_currentPiecePosition.y - 1 >= 0) {
                    if (a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 1] < 0 || a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 1] == 0)
                        b_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 1] = true;
                }
                if (m_currentPiecePosition.y + 1 <= 7) {
                    if (a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 1] < 0 || a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 1] == 0)
                        b_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 1] = true;
                }
            }
            if (m_currentPiecePosition.x + 1 <= 7) {
                if (a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y] < 0 || a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y] == 0)
                    b_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y] = true;
                if (m_currentPiecePosition.y - 1 >= 0) {
                    if (a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 1] < 0 || a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 1] == 0)
                        b_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 1] = true;
                }
                if (m_currentPiecePosition.y + 1 <= 7) {
                    if (a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 1] < 0 || a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 1] == 0)
                        b_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 1] = true;
                }
            }

            if (m_currentPiecePosition.y - 1 >= 0) {
                if (a_board[m_currentPiecePosition.x][m_currentPiecePosition.y - 1] < 0 || a_board[m_currentPiecePosition.x][m_currentPiecePosition.y - 1] == 0)
                    b_board[m_currentPiecePosition.x][m_currentPiecePosition.y - 1] = true;
            }
            if (m_currentPiecePosition.y + 1 <= 7) {
                if (a_board[m_currentPiecePosition.x][m_currentPiecePosition.y + 1] < 0 || a_board[m_currentPiecePosition.x][m_currentPiecePosition.y + 1] == 0)
                    b_board[m_currentPiecePosition.x][m_currentPiecePosition.y + 1] = true;
            }

            if (b_board[row][col]) {
                deletePieces(row, col);
                a_board[row][col] = m_currentPieceClicked;
                a_board[m_currentPiecePosition.x][m_currentPiecePosition.y] = 0;
                m_whiteTurn = false;
                s_pieceMove.play();
            }
        }
    }
    else if (!m_whiteTurn && m_pieceClicked) {
        if (a_board[row][col] < 0) {
            m_currentPieceClicked = a_board[row][col];
            m_currentPiecePosition.x = row;
            m_currentPiecePosition.y = col;
            for (int i = 0; i < m_pieces.size(); i++) {
                m_pieces[i].setColor(sf::Color(255, 255, 255, 255));
            }
            for (int i = 0; i < fields; i++) {
                for (int j = 0; j < fields; j++) {
                    m_canTakeBoard[i][j] = 0;
                }

            }
            return;
        }
        m_pieceClicked = false;

        for (int i = 0; i < m_pieces.size(); i++) {
            m_pieces[i].setColor(sf::Color(255, 255, 255, 255));
        }

        if (m_currentPieceClicked <= -60 && m_currentPieceClicked >= -67) {
            if (m_currentPiecePosition.x == 1) {
                if (a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y] == 0)
                    b_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y] = true;
                if (a_board[m_currentPiecePosition.x + 2][m_currentPiecePosition.y] == 0)
                    b_board[m_currentPiecePosition.x + 2][m_currentPiecePosition.y] = true;
                if (m_currentPiecePosition.x < 7 && m_currentPiecePosition.y > 0 && a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 1] > 0)
                    b_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 1] = true;
                if (m_currentPiecePosition.x < 7 && m_currentPiecePosition.y < 8 && a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 1] > 0)
                    b_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 1] = true;

                if (b_board[row][col]) {
                    deletePieces(row, col);
                    a_board[row][col] = m_currentPieceClicked;
                    a_board[m_currentPiecePosition.x][m_currentPiecePosition.y] = 0;
                    m_whiteTurn = true;
                    s_pieceMove.play();
                }

            }
            else {
                if (m_currentPiecePosition.x + 1 < 8 && a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y] == 0)
                    b_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y] = true;
                if (m_currentPiecePosition.x < 7 && m_currentPiecePosition.y > 0 && a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 1] > 0)
                    b_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 1] = true;
                if (m_currentPiecePosition.x < 7 && m_currentPiecePosition.y < 7 && a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 1] > 0)
                    b_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 1] = true;

                if (b_board[row][col]) {
                    deletePieces(row, col);
                    a_board[row][col] = m_currentPieceClicked;
                    a_board[m_currentPiecePosition.x][m_currentPiecePosition.y] = 0;
                    m_whiteTurn = true;
                    s_pieceMove.play();
                }
            }
        }
        else if (m_currentPieceClicked == -10 || m_currentPieceClicked == -11) {
            for (int i = m_currentPiecePosition.x; i >= 0; i--) {
                if (i == m_currentPiecePosition.x)
                    continue;
                if (a_board[i][m_currentPiecePosition.y] < 0)
                    break;
                if (a_board[i][m_currentPiecePosition.y] > 0) {
                    b_board[i][m_currentPiecePosition.y] = true;
                    break;
                }
                b_board[i][m_currentPiecePosition.y] = true;
            }
            for (int i = m_currentPiecePosition.x; i < 8; i++) {
                if (i == m_currentPiecePosition.x)
                    continue;
                if (a_board[i][m_currentPiecePosition.y] < 0)
                    break;
                if (a_board[i][m_currentPiecePosition.y] > 0) {
                    b_board[i][m_currentPiecePosition.y] = true;
                    break;
                }
                b_board[i][m_currentPiecePosition.y] = true;
            }
            for (int i = m_currentPiecePosition.y; i < 8; i++) {
                if (i == m_currentPiecePosition.y)
                    continue;
                if (a_board[m_currentPiecePosition.x][i] < 0)
                    break;
                if (a_board[m_currentPiecePosition.x][i] > 0) {
                    b_board[m_currentPiecePosition.x][i] = true;
                    break;
                }
                b_board[m_currentPiecePosition.x][i] = true;
            }
            for (int i = m_currentPiecePosition.y; i >= 0; i--) {
                if (i == m_currentPiecePosition.y)
                    continue;
                if (a_board[m_currentPiecePosition.x][i] < 0)
                    break;
                if (a_board[m_currentPiecePosition.x][i] > 0) {
                    b_board[m_currentPiecePosition.x][i] = true;
                    break;
                }
                b_board[m_currentPiecePosition.x][i] = true;
            }

            if (b_board[row][col]) {
                deletePieces(row, col);
                a_board[row][col] = m_currentPieceClicked;
                a_board[m_currentPiecePosition.x][m_currentPiecePosition.y] = 0;
                m_whiteTurn = true;
                s_pieceMove.play();
            }

        }
        else if (m_currentPieceClicked == -20 || m_currentPieceClicked == -21) {
            if (m_currentPiecePosition.x - 2 >= 0) {
                if (m_currentPiecePosition.y - 1 >= 0 && (a_board[m_currentPiecePosition.x - 2][m_currentPiecePosition.y - 1] > 0 || a_board[m_currentPiecePosition.x - 2][m_currentPiecePosition.y - 1] == 0)) {
                    b_board[m_currentPiecePosition.x - 2][m_currentPiecePosition.y - 1] = true;
                }
                if (m_currentPiecePosition.y + 1 <= 7 && (a_board[m_currentPiecePosition.x - 2][m_currentPiecePosition.y + 1] > 0 || a_board[m_currentPiecePosition.x - 2][m_currentPiecePosition.y + 1] == 0)) {
                    b_board[m_currentPiecePosition.x - 2][m_currentPiecePosition.y + 1] = true;
                }
            }
            if (m_currentPiecePosition.x + 2 <= 7) {
                if (m_currentPiecePosition.y - 1 >= 0 && (a_board[m_currentPiecePosition.x + 2][m_currentPiecePosition.y - 1] > 0 || a_board[m_currentPiecePosition.x + 2][m_currentPiecePosition.y - 1] == 0)) {
                    b_board[m_currentPiecePosition.x + 2][m_currentPiecePosition.y - 1] = true;
                }
                if (m_currentPiecePosition.y + 1 <= 7 && (a_board[m_currentPiecePosition.x + 2][m_currentPiecePosition.y + 1] > 0 || a_board[m_currentPiecePosition.x + 2][m_currentPiecePosition.y + 1] == 0)) {
                    b_board[m_currentPiecePosition.x + 2][m_currentPiecePosition.y + 1] = true;
                }
            }
            if (m_currentPiecePosition.y + 2 <= 7) {
                if (m_currentPiecePosition.x - 1 >= 0 && (a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 2] > 0 || a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 2] == 0)) {
                    b_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 2] = true;
                }
                if (m_currentPiecePosition.x + 1 <= 7 && (a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 2] > 0 || a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 2] == 0)) {
                    b_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 2] = true;
                }
            }
            if (m_currentPiecePosition.y - 2 >= 0) {
                if (m_currentPiecePosition.x - 1 >= 0 && (a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 2] > 0 || a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 2] == 0)) {
                    b_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 2] = true;
                }
                if (m_currentPiecePosition.x + 1 <= 7 && (a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 2] > 0 || a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 2] == 0)) {
                    b_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 2] = true;
                }
            }


            if (b_board[row][col]) {
                deletePieces(row, col);
                a_board[row][col] = m_currentPieceClicked;
                a_board[m_currentPiecePosition.x][m_currentPiecePosition.y] = 0;
                m_whiteTurn = true;
                s_pieceMove.play();
            }
        }
        else if (m_currentPieceClicked == -30 || m_currentPieceClicked == -31) {
            for (int i = m_currentPiecePosition.x, j = m_currentPiecePosition.y; i >= 0 && j >= 0; i--, j--) {
                if (i == m_currentPiecePosition.x && j == m_currentPiecePosition.y)
                    continue;
                if (a_board[i][j] < 0)
                    break;
                if (a_board[i][j] > 0) {
                    b_board[i][j] = true;
                    break;
                }
                b_board[i][j] = true;
            }
            for (int i = m_currentPiecePosition.x, j = m_currentPiecePosition.y; i >= 0 && j <= 7; i--, j++) {
                if (i == m_currentPiecePosition.x && j == m_currentPiecePosition.y)
                    continue;
                if (a_board[i][j] < 0)
                    break;
                if (a_board[i][j] > 0) {
                    b_board[i][j] = true;
                    break;
                }
                b_board[i][j] = true;
            }
            for (int i = m_currentPiecePosition.x, j = m_currentPiecePosition.y; i <= 7 && j >= 0; i++, j--) {
                if (i == m_currentPiecePosition.x && j == m_currentPiecePosition.y)
                    continue;
                if (a_board[i][j] < 0)
                    break;
                if (a_board[i][j] > 0) {
                    b_board[i][j] = true;
                    break;
                }
                b_board[i][j] = true;
            }
            for (int i = m_currentPiecePosition.x, j = m_currentPiecePosition.y; i <= 7 && j <= 7; i++, j++) {
                if (i == m_currentPiecePosition.x && j == m_currentPiecePosition.y)
                    continue;
                if (a_board[i][j] < 0)
                    break;
                if (a_board[i][j] > 0) {
                    b_board[i][j] = true;
                    break;
                }
                b_board[i][j] = true;
            }

            if (b_board[row][col]) {
                deletePieces(row, col);
                a_board[row][col] = m_currentPieceClicked;
                a_board[m_currentPiecePosition.x][m_currentPiecePosition.y] = 0;
                m_whiteTurn = true;
                s_pieceMove.play();
            }
        }
        else if (m_currentPieceClicked == -40) {
            for (int i = m_currentPiecePosition.x; i >= 0; i--) {
                if (i == m_currentPiecePosition.x)
                    continue;
                if (a_board[i][m_currentPiecePosition.y] < 0)
                    break;
                if (a_board[i][m_currentPiecePosition.y] > 0) {
                    b_board[i][m_currentPiecePosition.y] = true;
                    break;
                }
                b_board[i][m_currentPiecePosition.y] = true;
            }
            for (int i = m_currentPiecePosition.x; i < 8; i++) {
                if (i == m_currentPiecePosition.x)
                    continue;
                if (a_board[i][m_currentPiecePosition.y] < 0)
                    break;
                if (a_board[i][m_currentPiecePosition.y] > 0) {
                    b_board[i][m_currentPiecePosition.y] = true;
                    break;
                }
                b_board[i][m_currentPiecePosition.y] = true;
            }
            for (int i = m_currentPiecePosition.y; i < 8; i++) {
                if (i == m_currentPiecePosition.y)
                    continue;
                if (a_board[m_currentPiecePosition.x][i] < 0)
                    break;
                if (a_board[m_currentPiecePosition.x][i] > 0) {
                    b_board[m_currentPiecePosition.x][i] = true;
                    break;
                }
                b_board[m_currentPiecePosition.x][i] = true;
            }
            for (int i = m_currentPiecePosition.y; i >= 0; i--) {
                if (i == m_currentPiecePosition.y)
                    continue;
                if (a_board[m_currentPiecePosition.x][i] < 0)
                    break;
                if (a_board[m_currentPiecePosition.x][i] > 0) {
                    b_board[m_currentPiecePosition.x][i] = true;
                    break;
                }
                b_board[m_currentPiecePosition.x][i] = true;
            }
            for (int i = m_currentPiecePosition.x, j = m_currentPiecePosition.y; i >= 0 && j >= 0; i--, j--) {
                if (i == m_currentPiecePosition.x && j == m_currentPiecePosition.y)
                    continue;
                if (a_board[i][j] < 0)
                    break;
                if (a_board[i][j] > 0) {
                    b_board[i][j] = true;
                    break;
                }
                b_board[i][j] = true;
            }
            for (int i = m_currentPiecePosition.x, j = m_currentPiecePosition.y; i >= 0 && j <= 7; i--, j++) {
                if (i == m_currentPiecePosition.x && j == m_currentPiecePosition.y)
                    continue;
                if (a_board[i][j] < 0)
                    break;
                if (a_board[i][j] > 0) {
                    b_board[i][j] = true;
                    break;
                }
                b_board[i][j] = true;
            }
            for (int i = m_currentPiecePosition.x, j = m_currentPiecePosition.y; i <= 7 && j >= 0; i++, j--) {
                if (i == m_currentPiecePosition.x && j == m_currentPiecePosition.y)
                    continue;
                if (a_board[i][j] < 0)
                    break;
                if (a_board[i][j] > 0) {
                    b_board[i][j] = true;
                    break;
                }
                b_board[i][j] = true;
            }
            for (int i = m_currentPiecePosition.x, j = m_currentPiecePosition.y; i <= 7 && j <= 7; i++, j++) {
                if (i == m_currentPiecePosition.x && j == m_currentPiecePosition.y)
                    continue;
                if (a_board[i][j] < 0)
                    break;
                if (a_board[i][j] > 0) {
                    b_board[i][j] = true;
                    break;
                }
                b_board[i][j] = true;
            }

            if (b_board[row][col]) {
                deletePieces(row, col);
                a_board[row][col] = m_currentPieceClicked;
                a_board[m_currentPiecePosition.x][m_currentPiecePosition.y] = 0;
                m_whiteTurn = true;
                s_pieceMove.play();
            }
        }
        else if (m_currentPieceClicked == -50) {
            if (m_currentPiecePosition.x - 1 >= 0) {
                if (a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y] > 0 || a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y] == 0)
                    b_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y] = true;
                if (m_currentPiecePosition.y - 1 >= 0) {
                    if (a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 1] > 0 || a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 1] == 0)
                        b_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y - 1] = true;
                }
                if (m_currentPiecePosition.y + 1 <= 7) {
                    if (a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 1] > 0 || a_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 1] == 0)
                        b_board[m_currentPiecePosition.x - 1][m_currentPiecePosition.y + 1] = true;
                }
            }
            if (m_currentPiecePosition.x + 1 <= 7) {
                if (a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y] > 0 || a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y] == 0)
                    b_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y] = true;
                if (m_currentPiecePosition.y - 1 >= 0) {
                    if (a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 1] > 0 || a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 1] == 0)
                        b_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y - 1] = true;
                }
                if (m_currentPiecePosition.y + 1 <= 7) {
                    if (a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 1] > 0 || a_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 1] == 0)
                        b_board[m_currentPiecePosition.x + 1][m_currentPiecePosition.y + 1] = true;
                }
            }

            if (m_currentPiecePosition.y - 1 >= 0) {
                if (a_board[m_currentPiecePosition.x][m_currentPiecePosition.y - 1] > 0 || a_board[m_currentPiecePosition.x][m_currentPiecePosition.y - 1] == 0)
                    b_board[m_currentPiecePosition.x][m_currentPiecePosition.y - 1] = true;
            }
            if (m_currentPiecePosition.y + 1 <= 7) {
                if (a_board[m_currentPiecePosition.x][m_currentPiecePosition.y + 1] > 0 || a_board[m_currentPiecePosition.x][m_currentPiecePosition.y + 1] == 0)
                    b_board[m_currentPiecePosition.x][m_currentPiecePosition.y + 1] = true;
            }

            if (b_board[row][col]) {
                deletePieces(row, col);
                a_board[row][col] = m_currentPieceClicked;
                a_board[m_currentPiecePosition.x][m_currentPiecePosition.y] = 0;
                m_whiteTurn = true;
                s_pieceMove.play();
            }
        }
    }

    for (int i = 0; i < fields; i++) {
        for (int j = 0; j < fields; j++) {
            b_board[i][j] = false;
        }
    }
    

}
void Chess::deletePieces(int row, int col) {
    if (a_board[row][col] == -60) {
        m_pieces[8].setScale(0, 0);
        s_capture.play();
    }
    if (a_board[row][col] == -61) {
        m_pieces[9].setScale(0, 0);
        s_capture.play();
    }
    if (a_board[row][col] == -62) {
        m_pieces[10].setScale(0, 0);
        s_capture.play();
    }
    if (a_board[row][col] == -63) {
        m_pieces[11].setScale(0, 0);
        s_capture.play();
    }
    if (a_board[row][col] == -64) {
        m_pieces[12].setScale(0, 0);
        s_capture.play();
    }
    if (a_board[row][col] == -65) {
        m_pieces[13].setScale(0, 0);
        s_capture.play();
    }
    if (a_board[row][col] == -66) {
        m_pieces[14].setScale(0, 0);
        s_capture.play();
    }
    if (a_board[row][col] == -67) {
        m_pieces[15].setScale(0, 0);
        s_capture.play();
    }

    if (a_board[row][col] == -10) {
        m_pieces[0].setScale(0, 0);
        s_capture.play();
    }
    if (a_board[row][col] == -20) {
        m_pieces[1].setScale(0, 0);
        s_capture.play();
    }
    if (a_board[row][col] == -30) {
        m_pieces[2].setScale(0, 0);
        s_capture.play();
    }
    if (a_board[row][col] == -40) {
        m_pieces[3].setScale(0, 0);
        s_capture.play();
    }
    if (a_board[row][col] == -50) {
        m_pieces[4].setScale(0, 0);
        s_capture.play();
    }
    if (a_board[row][col] == -31) {
        m_pieces[5].setScale(0, 0);
        s_capture.play();
    }
    if (a_board[row][col] == -21) {
        m_pieces[6].setScale(0, 0);
        s_capture.play();
    }
    if (a_board[row][col] == -11) {
        m_pieces[7].setScale(0, 0);
        s_capture.play();
    }

    if (a_board[row][col] == 10) {
        m_pieces[16].setScale(0, 0);
        s_capture.play();
    }
    if (a_board[row][col] == 20) {
        m_pieces[17].setScale(0, 0);
        s_capture.play();
    }
    if (a_board[row][col] == 30) {
        m_pieces[18].setScale(0, 0);
        s_capture.play();
    }
    if (a_board[row][col] == 40) {
        m_pieces[19].setScale(0, 0);
        s_capture.play();
    }
    if (a_board[row][col] == 50) {
        m_pieces[20].setScale(0, 0);
        s_capture.play();
    }
    if (a_board[row][col] == 31) {
        m_pieces[21].setScale(0, 0);
        s_capture.play();
    }
    if (a_board[row][col] == 21) {
        m_pieces[22].setScale(0, 0);
        s_capture.play();
    }
    if (a_board[row][col] == 11) {
        m_pieces[23].setScale(0, 0);
        s_capture.play();
    }


    if (a_board[row][col] == 60) {
        m_pieces[24].setScale(0, 0);
        s_capture.play();
    }
    if (a_board[row][col] == 61) {
        m_pieces[25].setScale(0, 0);
        s_capture.play();
    }
    if (a_board[row][col] == 62) {
        m_pieces[26].setScale(0, 0);
        s_capture.play();
    }
    if (a_board[row][col] == 63) {
        m_pieces[27].setScale(0, 0);
        s_capture.play();
    }
    if (a_board[row][col] == 64) {
        m_pieces[28].setScale(0, 0);
        s_capture.play();
    }
    if (a_board[row][col] == 65) {
        m_pieces[29].setScale(0, 0);
        s_capture.play();
    }
    if (a_board[row][col] == 66) {
        m_pieces[30].setScale(0, 0);
        s_capture.play();
    }
    if (a_board[row][col] == 67) {
        m_pieces[31].setScale(0, 0);
        s_capture.play();
    }

    
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(windowWith, windowHeight), "Chess!",sf::Style::Close);
    window.setFramerateLimit(60);

    Chess game{};
    if (!game.loadAssets()) {
        return -1;
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {

                game.move(window);
            }
        }
        game.setCircle();
        game.setPieceTransparency();
        game.drawBoard();
        game.drawCircle(window);
        window.clear();
        window.draw(game.getBoard());

        for (auto& c : game.getCircle())
            window.draw(c);
        for (auto& p : game.getPieces())
            window.draw(p);

        
        window.display();
        game.deleteCircle();
    }

    return 0;
}
