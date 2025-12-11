#include "brick.h"

// Definicja kolorów dla poziomów życia 
const std::array<sf::Color, 5> Brick::colorLUT = {
    sf::Color(0, 0, 0, 0),
    sf::Color(255, 0, 0),
    sf::Color(255, 255, 0),
    sf::Color(0, 0, 255),
    sf::Color(128, 0, 128)
};

Brick::Brick(sf::Vector2f startPo, sf::Vector2f rozmiar, int L) {
    punktyZycia = L;
    jestZniszczony = false;
    this->setPosition(startPo);
    this->setSize(rozmiar);
    this->setOutlineThickness(1.f);
    this->setOutlineColor(sf::Color::Black);
    aktualizujKolor();
}

void Brick::aktualizujKolor() {
    // Ustawia kolor na podstawie HP, zabezpieczenie przed wyjściem poza tablicę
    if (punktyZycia > 0 && punktyZycia < static_cast<int>(colorLUT.size())) {
        this->setFillColor(colorLUT[punktyZycia]);
    }
    else {
        this->setFillColor(colorLUT[0]); // Niewidoczny
    }
}

void Brick::trafienie() {
    if (jestZniszczony) return;
    punktyZycia--;
    aktualizujKolor(); // Zmiana koloru po trafieniu
    if (punktyZycia <= 0)
        jestZniszczony = true;
}
