#ifndef GAME_H
#define GAME_H
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "brick.h"
#include "paddle.h"
#include "ball.h"

class Game
{
public:
    Game();
    void run();

private:
    void processEvents();
    void update();
    void render();

private:
    const float WIDTH = 640.f;
    const float HEIGHT = 480.f;

    sf::RenderWindow m_window;
    Paletka m_paletka;
    Pilka m_pilka;
    std::vector<Brick> m_bloki;
};

#endif
