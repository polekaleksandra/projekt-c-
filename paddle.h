#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics.hpp>

class Paletka {
private:
    float x;
    float y;
    float szerokosc;
    float wysokosc;
    float predkosc;
    sf::RectangleShape shape;

public:
    Paletka(float startX, float startY, float sw, float wy, float speed)
        : x(startX), y(startY), szerokosc(sw), wysokosc(wy), predkosc(speed)
    {
        shape.setSize(sf::Vector2f(szerokosc, wysokosc));
        shape.setOrigin(szerokosc / 2.f, wysokosc / 2.f);
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color::Green);
    }

    void moveLeft() {
        x -= predkosc;
        shape.setPosition(x, y);
    }

    void moveRight() {
        x += predkosc;
        shape.setPosition(x, y);
    }

    void clampToBounds(float width) {
        float half = szerokosc / 2.f;
        if (x - half < 0) x = half;
        if (x + half > width) x = width - half;
        shape.setPosition(x, y);
    }

    void draw(sf::RenderTarget& target) {
        target.draw(shape);
    }

    float getX() const { return x; }
    float getY() const { return y; }
    float getSzerokosc() const { return szerokosc; }
    float getWysokosc() const { return wysokosc; }
};

#endif
