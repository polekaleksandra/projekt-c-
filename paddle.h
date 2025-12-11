#ifndef PADDLE_H
#define PADDLE_H
#pragma once

#include <SFML/Graphics.hpp>

class Paletka {
private:
    float x, y;
    float szerokosc, wysokosc;
    float predkosc;
    sf::RectangleShape shape;

public:
    Paletka(float startX, float startY, float sw, float wy, float speed);

    // Metody sterowania i ograniczenia ruchu do ekranu
    void moveLeft();
    void moveRight();
    void clampToBounds(float width);
    void setPosition(float newX, float newY);

    void draw(sf::RenderTarget& target);
    sf::FloatRect getGlobalBounds() const; // Potrzebne do kolizji

    float getX() const { return x; }
    float getY() const { return y; }
    float getSzerokosc() const { return szerokosc; }
    float getWysokosc() const { return wysokosc; }
};

#endif
