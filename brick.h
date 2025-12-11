#ifndef BRICK_H
#define BRICK_H
#pragma once

#include <SFML/Graphics.hpp>
#include <array>

// Klasa dziedziczy po sf::RectangleShape
class Brick : public sf::RectangleShape {
private:
    int punktyZycia;
    bool jestZniszczony;
    static const std::array<sf::Color, 5> colorLUT;

public:
    Brick(sf::Vector2f startPo, sf::Vector2f rozmiar, int L);

    void aktualizujKolor(); // Zmienia kolor w zależności od HP
    void trafienie();       // Obsługa uderzenia piłki

    bool czyZniszczony() const { return jestZniszczony; }
    int getHP() const { return punktyZycia; }
    float getX() const { return getPosition().x; }
    float getY() const { return getPosition().y; }
};

#endif
