#include "GameState.h"
#include "paddle.h"
#include "ball.h"
#include "brick.h"
#include <iostream>

void GameState::capture(const Paletka& paddle, const Pilka& ball, const std::vector<Brick>& bricks) {
    
    paddlePosition.x = paddle.getX();
    paddlePosition.y = paddle.getY();

    
    ballPosition.x = ball.getX();
    ballPosition.y = ball.getY();
    ballVelocity.x = ball.getVx();
    ballVelocity.y = ball.getVy();

    
    blocks.clear();
    for (const auto& brick : bricks) {
        if (!brick.czyZniszczony()) {
            sf::Vector2f position = brick.getPosition();
            blocks.emplace_back(position.x, position.y, brick.getHP());
        }
    }

    std::cout << "Stan gry zapisany: " << blocks.size() << " blokow, pilka ("
        << ballPosition.x << ", " << ballPosition.y << ")\n";
}

