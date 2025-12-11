#ifndef GAME_H
#define GAME_H
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "paddle.h"
#include "ball.h"  
#include "brick.h"
#include "GameState.h"

// Główna klasa gry zarządzająca logiką
class Game {
public:
    Game();

    void update();
    void render(sf::RenderWindow& window);

    bool isGameOver() const { return m_gameOver; }
    void reset(); // Restart gry i generowanie poziomu

    void setBallType(BallType type);
    int getScore() const { return m_score; }

    void captureState(GameState& state) const;
    bool loadState(const GameState& state);

private:
    const float WIDTH = 800.f;
    const float HEIGHT = 600.f;

    Paletka m_paletka;
    Pilka m_pilka;
    std::vector<Brick> m_bloki; // Kontener na cegły

    sf::Font m_font;
    sf::Text m_scoreText;
    sf::Text m_comboText;

    int m_score;
    int m_comboMultiplier; // Mnożnik punktów za serię
    bool m_gameOver = false;
};

#endif
