#include "Game.h"
#include <iostream>
#pragma once

Game::Game()
    : m_paletka(400.f, 550.f, 100.f, 20.f, 8.f)
    , m_pilka(400.f, 300.f, 4.f, 3.f, 8.f) {

    const int ILOSC_KOLUMN = 8;
    const int ILOSC_WIERSZY = 7;
    float ROZMIAR_BLOKU_X = (800.f - (ILOSC_KOLUMN - 1) * 2.f) / ILOSC_KOLUMN;
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

void Game::update() {
    if (m_gameOver) return;

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
        
    }

    
    if (m_pilka.getY() > HEIGHT - 50) {
        m_gameOver = true;
        std::cout << "KONIEC GRY - pilka spadla!\n";
    }

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

void Game::render(sf::RenderWindow& window) {
    m_paletka.draw(window);

   
    if (!m_gameOver) {
        m_pilka.draw(window);
    }

    for (auto& blok : m_bloki) {
        blok.draw(window);
    }
}

void Game::reset() {
    m_gameOver = false;
    m_pilka = Pilka(400.f, 300.f, 4.f, 3.f, 8.f);
    m_paletka = Paletka(400.f, 550.f, 100.f, 20.f, 8.f);

    m_bloki.clear();
    const int ILOSC_KOLUMN = 8;
    const int ILOSC_WIERSZY = 7;
    float ROZMIAR_BLOKU_X = (800.f - (ILOSC_KOLUMN - 1) * 2.f) / ILOSC_KOLUMN;
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
