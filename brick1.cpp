#include "brick.h"
#include <array>


const std::array<sf::Color, 4> colorLUT = {
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
    this->setOutlineThickness(2.f);
    this->setOutlineColor(sf::Color::White);
    aktualizujKolor();
}

void Brick::aktualizujKolor() {
    if (punktyZycia >= 0 && punktyZycia < static_cast<int>(colorLUT.size())) {
        this->setFillColor(colorLUT[punktyZycia]);
    }
    else {
        this->setFillColor(sf::Color::White);
    }
}

void Brick::trafienie() {
    if (jestZniszczony == true)
        return;
    punktyZycia--;
    aktualizujKolor();
    if (punktyZycia <= 0)
        jestZniszczony = true;
}
