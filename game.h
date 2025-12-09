#ifndef GAME_H
#define GAME_H
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "paddle.h"
#include "ball.h"
#include "brick.h"  
#include "GameState.h"

class Game {
public:
    Game();
    void update();
    void render(sf::RenderWindow& window);
    bool isGameOver() const { return m_gameOver; }
    void reset();
    void captureState(GameState& state) const;
    bool loadState(const GameState& state);

private:
    const float WIDTH = 800.f;
    const float HEIGHT = 600.f;
    Paletka m_paletka;
    Pilka m_pilka;
    std::vector<Brick> m_bloki;
    bool m_gameOver = false;
    const float BRICK_WIDTH = (800.f - (8 - 1) * 2.f) / 8;
    const float BRICK_HEIGHT = 25.f;
};

#endif
