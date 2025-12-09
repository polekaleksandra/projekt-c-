#ifndef BALL_H
#define BALL_H
#pragma once

#include <SFML/Graphics.hpp>
#include "paddle.h" 

enum class BallType {
    Circle,
    Star,
    Heart
};

class Pilka {
private:
    float x, y;
    float vx, vy;
    float radius;

    sf::CircleShape circleShape;
    sf::ConvexShape starShape;
    sf::ConvexShape heartShape;

    BallType currentType;

public:
    Pilka(float startX, float startY, float velX, float velY, float r);

    void move();
    void bounceX();
    void bounceY();
    void collideWalls(float width, float height);
    bool collidePaddle(const Paletka& p);
    void setState(float newX, float newY, float newVx, float newVy);

    void setType(BallType type);

    void draw(sf::RenderTarget& target) const;
    sf::FloatRect getGlobalBounds() const;

    float getX() const { return x; }
    float getY() const { return y; }
    float getVx() const { return vx; }
    float getVy() const { return vy; }
    float getRadius() const { return radius; }
};

#endif
