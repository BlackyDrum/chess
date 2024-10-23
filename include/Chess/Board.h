#pragma once

#include <SFML/Graphics.hpp>

class Board
{
public:
    Board();

    void Draw(sf::RenderWindow& window);
private:
    sf::Texture m_BoardTexture;
    sf::Sprite m_BoardSprite;
private:
    void LoadAssets();
};