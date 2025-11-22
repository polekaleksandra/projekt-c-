#ifndef BRICK_H
#define BRICK_H
#pragma once

#include <SFML/Graphics.hpp>
#include <array>

class Brick : public sf::RectangleShape {
private:
    int punktyZycia;
    bool jestZniszczony;
    static const std::array<sf::Color, 4> colorLUT;

public:
    Brick(sf::Vector2f startPo, sf::Vector2f rozmiar, int L) {
        punktyZycia = L;
        jestZniszczony = false;
        this->setPosition(startPo);
        this->setSize(rozmiar);
        this->setOutlineThickness(2.f);
        this->setOutlineColor(sf::Color::White);
        aktualizujKolor();
    }

    void aktualizujKolor() {
        if (punktyZycia >= 0 && punktyZycia < static_cast<int>(colorLUT.size())) {
            this->setFillColor(colorLUT[punktyZycia]);
        }
    }

    void trafienie() {
        if (jestZniszczony == true) return;
        punktyZycia--;
        aktualizujKolor();
        if (punktyZycia <= 0) jestZniszczony = true;
    }

    void draw(sf::RenderTarget& window) {
        if (!jestZniszczony) {
            window.draw(*this);
        }
    }

    bool czyZniszczony() const { return jestZniszczony; }
};

#endif
