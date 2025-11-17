#include <SFML/Graphics.hpp> 
#include <array>
class Brick :public sf::RectangleShape {
private:
	int punktyZycia;
	bool jestZniszczony;
	static const std::array<sf::Color, 4> colorLUT;
public:
	Brick(sf::Vector2f startPo, sf::Vector2f rozmiar, int L);
	void aktualizujKolor();
	void trafienie();
	void draw(sf::RenderTarget& window);
	bool czyZniszczony() const { return jestZniszczony; } 
};

const std::array<sf::Color, 4> Brick::colorLUT = {
	sf::Color::Transparent,
	sf::Color::Red,          
	sf::Color::Yellow,
	sf::Color::Blue,
};

Brick::Brick(sf::Vector2f startPo, sf::Vector2f rozmiar, int L) {
	punktyZycia = L;
	jestZniszczony = false;
	this->setPosition(startPo); 
	this->setSize(rozmiar);     
	this->setOutlineThickness(2.f); 
	this->setOutlineColor(sf::Color::White);
	aktualizujKolor(); 
};

void Brick::trafienie() {
	if (jestZniszczony == true)
		return;
	punktyZycia--;
	aktualizujKolor();
	if (punktyZycia <= 0)
		jestZniszczony = true;
}

void Brick::aktualizujKolor() {
	if (punktyZycia >= 0 && punktyZycia < static_cast<int>(colorLUT.size())) 
		this->setFillColor(colorLUT[punktyZycia]);
}

void Brick::draw(sf::RenderTarget& window) {
	if (!jestZniszczony) { 
		window.draw(*this);
	}
}
