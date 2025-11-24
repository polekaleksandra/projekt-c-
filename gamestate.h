#ifndef GAMESTATE_H
#define GAMESTATE_H
#pragma once

#include <SFML/System.hpp>
#include <vector>
#include "BlockData.h"


class Paletka;
class Pilka;
class Brick;

class GameState {
public:
    GameState() = default;

    
    void capture(const Paletka& paddle, const Pilka& ball, const std::vector<Brick>& bricks);

    
    const sf::Vector2f& getPaddlePosition() const { return paddlePosition; }
    const sf::Vector2f& getBallPosition() const { return ballPosition; }
    const sf::Vector2f& getBallVelocity() const { return ballVelocity; }
    const std::vector<BlockData>& getBlocks() const { return blocks; }

private:
    sf::Vector2f paddlePosition;
    sf::Vector2f ballPosition;
    sf::Vector2f ballVelocity;
    std::vector<BlockData> blocks;
};

#endif
