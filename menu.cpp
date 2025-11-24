#include "Menu.h"
#include <iostream>

Menu::Menu(float width, float height) {
    
    if (!font.loadFromFile("arial.ttf")) {
        
        if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
            
            std::cout << "Uzywam domyslnej czcionki SFML\n";
            font.loadFromFile(""); 
        }
    }

    menuItems.resize(3);

    menuItems[0].setFont(font);
    menuItems[0].setFillColor(sf::Color::Red);
    menuItems[0].setString("Nowa gra");
    menuItems[0].setCharacterSize(30);
    menuItems[0].setPosition(sf::Vector2f(width / 2 - 80, height / 4 * 1));

    menuItems[1].setFont(font);
    menuItems[1].setFillColor(sf::Color::White);
    menuItems[1].setString("Wyniki");
    menuItems[1].setCharacterSize(30);
    menuItems[1].setPosition(sf::Vector2f(width / 2 - 50, height / 4 * 2));

    menuItems[2].setFont(font);
    menuItems[2].setFillColor(sf::Color::White);
    menuItems[2].setString("Wyjscie");
    menuItems[2].setCharacterSize(30);
    menuItems[2].setPosition(sf::Vector2f(width / 2 - 50, height / 4 * 3));

    selectedItemIndex = 0;
}

void Menu::draw(sf::RenderWindow& window) {
    for (const auto& item : menuItems) {
        window.draw(item);
    }
}

void Menu::MoveUp() {
    if (selectedItemIndex - 1 >= 0) {
        menuItems[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void Menu::MoveDown() {
    if (selectedItemIndex + 1 < menuItems.size()) {
        menuItems[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}
