#ifndef MENU_H
#define MENU_H
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "ball.h" 

class Menu {
public:
    Menu(float width, float height);
    void draw(sf::RenderWindow& window);
    void MoveUp();   // Nawigacja w górę
    void MoveDown(); // Nawigacja w dół
    int getSelectedItem() { return selectedItemIndex; }

    void changeShapeText(BallType type); // Aktualizacja tekstu w opcji wyboru kształtu

private:
    int selectedItemIndex;
    sf::Font font;
    std::vector<sf::Text> menuItems;
};

#endif
