
#ifndef BALL_H
#define BALL_H
#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "paddle.h"

class Pilka {
private:
    float x, y;
    float vx, vy;
    float radius;
    sf::CircleShape shape;

public:
    Pilka(float startX, float startY, float velX, float velY, float r)
        : x(startX), y(startY), vx(velX), vy(velY), radius(r) {
        shape.setRadius(radius);
        shape.setOrigin(radius, radius);
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color::White);
    }

    void move() {
        x += vx;
        y += vy;
        shape.setPosition(x, y);
    }

    void bounceX() {
        vx = -vx;
    }

    void bounceY() {
        vy = -vy;
    }

    void collideWalls(float width, float height) {
        if (x - radius <= 0) {
            x = radius;
            bounceX();
        }
        if (x + radius >= width) {
            x = width - radius;
            bounceX();
        }
        if (y - radius <= 0) {
            y = radius;
            bounceY();
        }
        shape.setPosition(x, y);
    }

    bool collidePaddle(const Paletka& p) {
        sf::FloatRect paddleBounds = p.getGlobalBounds();
        sf::FloatRect ballBounds = getGlobalBounds();

        if (ballBounds.intersects(paddleBounds)) {
            vy = -std::abs(vy);
            y = paddleBounds.top - radius;
            shape.setPosition(x, y);
            return true;
        }
        return false;
    }

    sf::FloatRect getGlobalBounds() const {
        return sf::FloatRect(x - radius, y - radius, 2 * radius, 2 * radius);
    }

    
    void setState(float newX, float newY, float newVx, float newVy) {
        x = newX;
        y = newY;
        vx = newVx;
        vy = newVy;
        shape.setPosition(x, y);
    }

    void draw(sf::RenderTarget& target) {
        target.draw(shape);
    }

    float getX() const { return x; }
    float getY() const { return y; }
    float getVx() const { return vx; }
    float getVy() const { return vy; }
    float getRadius() const { return radius; }
};

#endif
