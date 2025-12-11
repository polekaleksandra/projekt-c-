#include "Game.h"
#include <iostream>
#include <string>
#include <cstdlib> 

Game::Game()
    : m_paletka(400.f, 550.f, 100.f, 20.f, 8.f)
    , m_pilka(400.f, 300.f, 4.f, 3.f, 8.f)
    , m_score(0)
    , m_comboMultiplier(0) {

    // Ładowanie czcionki
    if (!m_font.loadFromFile("arial.ttf")) {
        if (!m_font.loadFromFile("C:/Windows/Fonts/arial.ttf")) { }
    }

    m_scoreText.setFont(m_font);
    m_scoreText.setCharacterSize(24);
    m_scoreText.setFillColor(sf::Color::White);
    m_scoreText.setPosition(10.f, 10.f);
    m_scoreText.setString("Punkty: 0");

    m_comboText.setFont(m_font);
    m_comboText.setCharacterSize(20);
    m_comboText.setFillColor(sf::Color::Yellow);
    m_comboText.setPosition(10.f, 40.f);

    reset();
}

void Game::setBallType(BallType type) {
    m_pilka.setType(type);
}

void Game::update() {
    if (m_gameOver) return;

    // Sterowanie paletką
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        m_paletka.moveLeft();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        m_paletka.moveRight();

    m_paletka.clampToBounds(WIDTH);
    m_pilka.move();
    m_pilka.collideWalls(WIDTH, HEIGHT);

    // Reset Combo przy dotknięciu paletki
    if (m_pilka.collidePaddle(m_paletka)) {
        m_comboMultiplier = 0;
    }

    if (m_pilka.getY() > HEIGHT - 50) {
        m_gameOver = true;
    }

    // Kolizja z blokami i naliczanie punktów
    for (auto& blok : m_bloki) {
        if (!blok.czyZniszczony() && m_pilka.getGlobalBounds().intersects(blok.getGlobalBounds())) {
            blok.trafienie();
            m_pilka.bounceY();

            m_comboMultiplier++; // Zwiększenie serii
            int punktyZaBlok = 10 * m_comboMultiplier;
            m_score += punktyZaBlok;

            m_scoreText.setString("Punkty: " + std::to_string(m_score));
            m_comboText.setString("COMBO x" + std::to_string(m_comboMultiplier) + "!");
        }
    }

    // Usuwanie zniszczonych bloków (iteracja od tyłu)
    for (int i = static_cast<int>(m_bloki.size()) - 1; i >= 0; i--) {
        if (m_bloki[i].czyZniszczony()) {
            m_bloki.erase(m_bloki.begin() + i);
        }
    }
}

void Game::render(sf::RenderWindow & window) {
    m_paletka.draw(window);
    if (!m_gameOver) m_pilka.draw(window);

    for (auto& blok : m_bloki) {
        window.draw(blok);
    }

    window.draw(m_scoreText);
    if (m_comboMultiplier > 1) { // Wyświetlanie combo tylko przy serii > 1
        window.draw(m_comboText);
    }
}

void Game::reset() {
    m_gameOver = false;
    m_score = 0;
    m_comboMultiplier = 0;
    m_scoreText.setString("Punkty: 0");

    // Losowanie kierunku startowego piłki
    float velX = (rand() % 2 == 0) ? 4.0f : -4.0f;
    m_pilka = Pilka(400.f, 300.f, velX, 3.f, 8.f);
    m_paletka = Paletka(400.f, 550.f, 100.f, 20.f, 8.f);

    m_bloki.clear();
    const int ILOSC_KOLUMN = 8;
    const int ILOSC_WIERSZY = 8;
    float ROZMIAR_BLOKU_X = (800.f - (ILOSC_KOLUMN - 1) * 2.f) / ILOSC_KOLUMN;
    float ROZMIAR_BLOKU_Y = 25.f;

    // Generowanie planszy z różnym HP dla rzędów
    for (int y = 0; y < ILOSC_WIERSZY; y++) {
        for (int x = 0; x < ILOSC_KOLUMN; x++) {
            float posX = x * (ROZMIAR_BLOKU_X + 2.f);
            float posY = y * (ROZMIAR_BLOKU_Y + 2.f) + 50.f;
            int L = (y == 0) ? 4 : (y == 1) ? 3 : (y < 4) ? 2 : 1;
            m_bloki.emplace_back(sf::Vector2f(posX, posY), sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y), L);
        }
    }
}

void Game::captureState(GameState & state) const {
    state.capture(m_paletka, m_pilka, m_bloki);
}

bool Game::loadState(const GameState & state) {
    try {
        sf::Vector2f paddlePos = state.getPaddlePosition();
        m_paletka.setPosition(paddlePos.x, paddlePos.y);

        sf::Vector2f ballPos = state.getBallPosition();
        sf::Vector2f ballVel = state.getBallVelocity();
        m_pilka.setState(ballPos.x, ballPos.y, ballVel.x, ballVel.y);

        m_bloki.clear();
        const auto& blocks = state.getBlocks();
        float bw = (800.f - (8 - 1) * 2.f) / 8;

        for (const auto& block : blocks) {
            m_bloki.emplace_back(sf::Vector2f(block.x, block.y), sf::Vector2f(bw, 25.f), block.hp);
        }
        m_gameOver = false;
        return true;
    }
    catch (...) { return false; }
}
