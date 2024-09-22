#include "Chess/Chess.h"

void Run()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Chess", sf::Style::Close);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        window.display();
    }
}