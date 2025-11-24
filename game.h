#ifndef GAME_H
#define GAME_H
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "brick.h"
#include "paddle.h"
#include "ball.h"

class Game {
public:
    Game();
    void update();
    void render(sf::RenderWindow& window);
    bool isGameOver() const { return m_gameOver; }
    void reset();

private:
    const float WIDTH = 800.f;
    const float HEIGHT = 600.f;
    Paletka m_paletka;
    Pilka m_pilka;
    std::vector<Brick> m_bloki;
    bool m_gameOver = false;
};

#endif
