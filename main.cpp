#include "Game.h"
#include "Menu.h"
#include <SFML/Graphics.hpp>
#include <iostream>

enum class GameState { Menu, Playing, Scores, Exiting };

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Arkanoid");
    window.setFramerateLimit(60);

    Menu menu(800, 600);
    Game game;
    GameState currentState = GameState::Menu;

    
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
            
            if (!font.loadFromFile("")) {
                std::cout << "Nie udalo sie zaladowac czcionki\n";
            }
        }
    }

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (currentState == GameState::Menu) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Up) {
                        menu.MoveUp();
                    }
                    if (event.key.code == sf::Keyboard::Down) {
                        menu.MoveDown();
                    }
                    if (event.key.code == sf::Keyboard::Enter) {
                        int selected = menu.getSelectedItem();
                        if (selected == 0) {
                            currentState = GameState::Playing;
                            game.reset();
                        }
                        else if (selected == 1) {
                            currentState = GameState::Scores;
                        }
                        else if (selected == 2) {
                            window.close();
                        }
                    }
                }
            }
            else if (currentState == GameState::Playing) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape) {
                        currentState = GameState::Menu;
                    }
                }
            }
            else if (currentState == GameState::Scores) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Enter) {
                        currentState = GameState::Menu;
                    }
                }
            }
        }

        if (currentState == GameState::Playing) {
            if (!game.isGameOver()) {
                game.update();
            }
            else {
             
                static sf::Clock gameOverClock;
                if (gameOverClock.getElapsedTime().asSeconds() > 2.0f) {
                    currentState = GameState::Menu;
                    gameOverClock.restart();
                }
            }
        }

        window.clear(sf::Color(20, 20, 30));

        if (currentState == GameState::Menu) {
            menu.draw(window);
        }
        else if (currentState == GameState::Playing) {
            game.render(window);

            
            if (game.isGameOver()) {
                sf::Text gameOverText;
                gameOverText.setFont(font);
                gameOverText.setString("KONIEC GRY!\nPowrot do menu...");
                gameOverText.setCharacterSize(30);
                gameOverText.setFillColor(sf::Color::Red);
                gameOverText.setPosition(250, 250);
                window.draw(gameOverText);
            }
        }
        else if (currentState == GameState::Scores) {
           
            sf::Text title;
            title.setFont(font);
            title.setString("TABELA WYNIKOW");
            title.setCharacterSize(40);
            title.setFillColor(sf::Color::Yellow);
            title.setPosition(250, 100);
            window.draw(title);

            sf::Text scores;
            scores.setFont(font);
            scores.setString("1. Gracz 1 - 1000 pkt\n\n2. Gracz 2 - 800 pkt\n\n3. Gracz 3 - 600 pkt");
            scores.setCharacterSize(24);
            scores.setFillColor(sf::Color::White);
            scores.setPosition(300, 200);
            window.draw(scores);

            sf::Text instruction;
            instruction.setFont(font);
            instruction.setString("Nacisnij ESC lub ENTER aby wrocic");
            instruction.setCharacterSize(20);
            instruction.setFillColor(sf::Color::Green);
            instruction.setPosition(250, 450);
            window.draw(instruction);
        }

        window.display();
    }

    return 0;
}
