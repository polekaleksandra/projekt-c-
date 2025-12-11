#include "Menu.h"
#include <iostream>
#include <string>

Menu::Menu(float width, float height) {
    // Ładowanie czcionki
    if (!font.loadFromFile("arial.ttf")) {
        if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {}
    }

    menuItems.resize(5);
    std::string labels[] = {
        "Nowa gra", "Ksztalt: KULA", "Wczytaj gre", "Wyniki", "Wyjscie"
    };

    // Konfiguracja wyglądu przycisków
    for (int i = 0; i < 5; i++) {
        menuItems[i].setFont(font);
        menuItems[i].setString(labels[i]);
        menuItems[i].setCharacterSize(30);
        menuItems[i].setFillColor(sf::Color::White);
        menuItems[i].setPosition(sf::Vector2f(width / 2 - 80, height / 6 * (i + 1)));
    }

    selectedItemIndex = 0;
    menuItems[0].setFillColor(sf::Color::Red); // Podświetlenie pierwszego elementu
}

void Menu::draw(sf::RenderWindow& window) {
    for (const auto& item : menuItems) {
        window.draw(item);
    }
}

void Menu::changeShapeText(BallType type) {
    switch (type) {
    case BallType::Circle: menuItems[1].setString("Ksztalt: KULA"); break;
    case BallType::Star:   menuItems[1].setString("Ksztalt: GWIAZDA"); break;
    case BallType::Heart:  menuItems[1].setString("Ksztalt: SERCE"); break;
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
    if (selectedItemIndex + 1 < static_cast<int>(menuItems.size())) {
        menuItems[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}
