#include "paddle.h"

Paletka::Paletka(float startX, float startY, float sw, float wy, float speed)
    : x(startX), y(startY), szerokosc(sw), wysokosc(wy), predkosc(speed) {
    shape.setSize(sf::Vector2f(szerokosc, wysokosc));
    shape.setOrigin(szerokosc / 2.f, wysokosc / 2.f); 
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Green);
}

void Paletka::moveLeft() {
    x -= predkosc;
    shape.setPosition(x, y);
}

void Paletka::moveRight() {
    x += predkosc;
    shape.setPosition(x, y);
}

// Zabezpieczenie przed wyjściem paletki poza ekran
void Paletka::clampToBounds(float width) {
    float half = szerokosc / 2.f;
    if (x - half < 0) x = half;
    if (x + half > width) x = width - half;
    shape.setPosition(x, y);
}

void Paletka::setPosition(float newX, float newY) {
    x = newX;
    y = newY;
    shape.setPosition(x, y);
}

sf::FloatRect Paletka::getGlobalBounds() const {
    return shape.getGlobalBounds();
}

void Paletka::draw(sf::RenderTarget& target) {
    target.draw(shape);
}
sf::FloatRect Paletka::getGlobalBounds() const {
    return shape.getGlobalBounds();
}

void Paletka::draw(sf::RenderTarget& target) {
    target.draw(shape);
}
