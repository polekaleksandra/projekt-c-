#ifndef BALL_H
#define BALL_H
#pragma once

#include <SFML/Graphics.hpp>
#include "paddle.h" 

// Typ wyliczeniowy dla różnych kształtów piłki
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

    // Przechowujemy definicje trzech kształtów
    sf::CircleShape circleShape;
    sf::ConvexShape starShape;
    sf::ConvexShape heartShape;

    BallType currentType; // Aktualnie wybrany kształt

public:
    Pilka(float startX, float startY, float velX, float velY, float r);

    void move();
    void bounceX();
    void bounceY();
    void collideWalls(float width, float height);
    bool collidePaddle(const Paletka& p);
    void setState(float newX, float newY, float newVx, float newVy);

    void setType(BallType type); // Zmiana kształtu

    void draw(sf::RenderTarget& target) const;
    sf::FloatRect getGlobalBounds() const;

    float getX() const { return x; }
    float getY() const { return y; }
    float getVx() const { return vx; }
    float getVy() const { return vy; }
    float getRadius() const { return radius; }
};

#endif
