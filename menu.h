#ifndef MENU_H
#define MENU_H
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Menu {
public:
    Menu(float width, float height);
    void draw(sf::RenderWindow& window);
    void MoveUp();
    void MoveDown();
    int getSelectedItem() { return selectedItemIndex; }

private:
    int selectedItemIndex;
    sf::Font font;
    std::vector<sf::Text> menuItems;
};

#endif
