#include "brick.h"

const std::array<sf::Color, 4> Brick::colorLUT = {
    sf::Color(0, 0, 0, 0),       
    sf::Color(255, 0, 0),        
    sf::Color(255, 255, 0),      
    sf::Color(0, 0, 255)         
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
    if (punktyZycia > 0 && punktyZycia < static_cast<int>(colorLUT.size())) {
        this->setFillColor(colorLUT[punktyZycia]);
    }
    else {
        this->setFillColor(colorLUT[0]); 
    }
}

void Brick::trafienie() {
    if (jestZniszczony) return;
    punktyZycia--;
    aktualizujKolor();
    if (punktyZycia <= 0)
        jestZniszczony = true;
}
