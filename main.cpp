#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <optional>
#include "brick.h"
#include "paddle.h"
#include "ball.h"

int main()
{
    const float WIDTH = 640.f;
    const float HEIGHT = 480.f;

    sf::RenderWindow window(sf::VideoMode((unsigned int)WIDTH, (unsigned int)HEIGHT), "Arkanoid test");
    window.setFramerateLimit(60);

    Paletka pal(320.f, 440.f, 100.f, 20.f, 8.f);
    Pilka pilka(320.f, 200.f, 4.f, 3.f, 8.f);

    std::vector<Brick> bloki;
    const int ILOSC_KOLUMN = 6;
    const int ILOSC_WIERSZY = 7;
    float ROZMIAR_BLOKU_X = (640.f - (ILOSC_KOLUMN - 1) * 2.f) / ILOSC_KOLUMN;
    float ROZMIAR_BLOKU_Y = 25.f;

    for (int y = 0; y < ILOSC_WIERSZY; y++) {
        for (int x = 0; x < ILOSC_KOLUMN; x++) {
            float posX = x * (ROZMIAR_BLOKU_X + 2.f);
            float posY = y * (ROZMIAR_BLOKU_Y + 2.f) + 50.f;

            int L = (y < 1) ? 3 : (y < 3) ? 2 : 1;

            bloki.emplace_back(sf::Vector2f(posX, posY), sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y), L);
        }
    }

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            pal.moveLeft();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            pal.moveRight();
        }

        pal.clampToBounds(WIDTH);

        pilka.move();
        pilka.collideWalls(WIDTH, HEIGHT);

        if (pilka.collidePaddle(pal)) {
            std::cout << "HIT PADDLE\n";
        }

        if (pilka.getY() - pilka.getRadius() > HEIGHT) {
            std::cout << "MISS! KONIEC GRY\n";
            window.close();
        }

        std::cout << "x=" << pilka.getX()
            << " y=" << pilka.getY()
            << " vx=" << pilka.getVx()
            << " vy=" << pilka.getVy() << "\n";
        for (auto& blok : bloki) {
            if (!blok.czyZniszczony() && pilka.getGlobalBounds().intersects(blok.getGlobalBounds())) {

                blok.trafienie();
                pilka.bounceY();

            }
        }

        for (int i = bloki.size() - 1; i >= 0; i--) {
            if (bloki[i].czyZniszczony()) {
                bloki.erase(bloki.begin() + i);
            }
        }

        window.clear(sf::Color(20, 20, 30));
        pal.draw(window);
        pilka.draw(window);
        for (auto& blok : bloki) {
            blok.draw(window);
        }
        window.display();
    }

    return 0;
}
