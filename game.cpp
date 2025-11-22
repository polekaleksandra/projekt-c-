#include "Game.h"
#include <iostream>
#pragma once

Game::Game()
    : m_window(sf::VideoMode((unsigned int)WIDTH, (unsigned int)HEIGHT), "Arkanoid test")
    , m_paletka(320.f, 440.f, 100.f, 20.f, 8.f)
    , m_pilka(320.f, 200.f, 4.f, 3.f, 8.f) {

    m_window.setFramerateLimit(60);

    const int ILOSC_KOLUMN = 6;
    const int ILOSC_WIERSZY = 7;
    float ROZMIAR_BLOKU_X = (640.f - (ILOSC_KOLUMN - 1) * 2.f) / ILOSC_KOLUMN;
    float ROZMIAR_BLOKU_Y = 25.f;

    for (int y = 0; y < ILOSC_WIERSZY; y++) {
        for (int x = 0; x < ILOSC_KOLUMN; x++) {
            float posX = x * (ROZMIAR_BLOKU_X + 2.f);
            float posY = y * (ROZMIAR_BLOKU_Y + 2.f) + 50.f;
            int L = (y < 1) ? 3 : (y < 3) ? 2 : 1;
            m_bloki.emplace_back(sf::Vector2f(posX, posY), sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y), L);
        }
    }
}

void Game::run() {
    while (m_window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            m_window.close();
    }
}

void Game::update() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        m_paletka.moveLeft();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        m_paletka.moveRight();
    }
    m_paletka.clampToBounds(WIDTH);
    m_pilka.move();
    m_pilka.collideWalls(WIDTH, HEIGHT);

    if (m_pilka.collidePaddle(m_paletka)) {
        std::cout << "HIT PADDLE\n";
    }

    if (m_pilka.getY() - m_pilka.getRadius() > HEIGHT) {
        std::cout << "MISS! KONIEC GRY\n";
        m_window.close();
    }

    std::cout << "x=" << m_pilka.getX() << " y=" << m_pilka.getY() << " vx=" << m_pilka.getVx() << " vy=" << m_pilka.getVy() << "\n";

    for (auto& blok : m_bloki) {
        if (!blok.czyZniszczony() && m_pilka.getGlobalBounds().intersects(blok.getGlobalBounds())) {
            blok.trafienie();
            m_pilka.bounceY();
        }
    }

    
    for (int i = static_cast<int>(m_bloki.size()) - 1; i >= 0; i--) {
        if (m_bloki[i].czyZniszczony()) {
            m_bloki.erase(m_bloki.begin() + i);
        }
    }
}

void Game::render() {
    m_window.clear(sf::Color(20, 20, 30));
    m_paletka.draw(m_window);
    m_pilka.draw(m_window);
    for (auto& blok : m_bloki) {
        blok.draw(m_window);
    }
    m_window.display();
}
