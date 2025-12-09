#ifndef BRICK_H
#define BRICK_H
#pragma once

#include <SFML/Graphics.hpp>

class Brick : public sf::RectangleShape {
private:
    int punktyZycia;
    bool jestZniszczony;

public:
   
    Brick(sf::Vector2f startPo, sf::Vector2f rozmiar, int L);

    void aktualizujKolor();
    void trafienie();

    bool czyZniszczony() const { return jestZniszczony; }
    int getHP() const { return punktyZycia; }
    float getX() const { return getPosition().x; }
    float getY() const { return getPosition().y; }

    sf::FloatRect getGlobalBounds() const {
        return sf::RectangleShape::getGlobalBounds();
    }
};

#endif
