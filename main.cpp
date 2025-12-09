#include "Game.h"
#include "Menu.h"
#include "GameState.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

enum class AppState { Menu, Playing, Scores, Exiting };

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Arkanoid");
    window.setFramerateLimit(60);

    Menu menu(800, 600);
    Game game;
    AppState currentState = AppState::Menu;

    GameState savedGameState;
    bool hasSavedState = false;

    sf::Font font;
    bool fontLoaded = false;

    if (font.loadFromFile("arial.ttf")) {
        fontLoaded = true;
    }
    else if (font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        fontLoaded = true;
    }
    else if (font.loadFromFile("")) {
        fontLoaded = true;
    }

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (currentState == AppState::Menu) {
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
                            currentState = AppState::Playing;
                            game.reset();
                            std::cout << "Nowa gra rozpoczeta\n";
                        }
                        else if (selected == 1) {  
                            GameState loadedState;
                            if (loadedState.loadFromFile("zapis.txt")) {
                                if (game.loadState(loadedState)) {
                                    currentState = AppState::Playing;
                                    std::cout << "Gra wczytana pomyslnie\n";
                                }
                                else {
                                    std::cout << "Blad podczas wczytywania stanu do gry\n";
                                }
                            }
                            else {
                                std::cout << "Nie mozna wczytac zapisanej gry\n";
                            }
                        }
                        else if (selected == 2) {  
                            currentState = AppState::Scores;
                        }
                        else if (selected == 3) {  
                            window.close();
                        }
                    }
                }
            }
            else if (currentState == AppState::Playing) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape) {
                        currentState = AppState::Menu;
                    }

                    if (event.key.code == sf::Keyboard::P) {
                        game.captureState(savedGameState);
                        hasSavedState = true;
                        std::cout << "Stan gry zapisany w pamieci! (P)\n";
                    }

                    if (event.key.code == sf::Keyboard::F5) {
                        GameState currentGameState;
                        game.captureState(currentGameState);
                        if (currentGameState.saveToFile("zapis.txt")) {
                            std::cout << "Gra zapisana do pliku! (F5)\n";
                        }
                    }

                    if (event.key.code == sf::Keyboard::L && hasSavedState) {
                        if (game.loadState(savedGameState)) {
                            std::cout << "Stan gry wczytany z pamieci! (L)\n";
                        }
                    }
                }
            }
            else if (currentState == AppState::Scores) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Enter) {
                        currentState = AppState::Menu;
                    }
                }
            }
        }

        if (currentState == AppState::Playing) {
            if (!game.isGameOver()) {
                game.update();
            }
            else {
                static sf::Clock gameOverClock;
                if (gameOverClock.getElapsedTime().asSeconds() > 2.0f) {
                    currentState = AppState::Menu;
                    gameOverClock.restart();
                }
            }
        }

        window.clear(sf::Color(20, 20, 30));

        if (currentState == AppState::Menu) {
            menu.draw(window);

            if (fontLoaded) {
                std::ifstream testFile("zapis.txt");
                bool saveFileExists = testFile.good();
                testFile.close();

                if (saveFileExists) {
                    sf::Text saveInfo;
                    saveInfo.setFont(font);
                    saveInfo.setString("Plik zapisu gry istnieje\n(Wczytaj gre z menu)");
                    saveInfo.setCharacterSize(16);
                    saveInfo.setFillColor(sf::Color::Green);
                    saveInfo.setPosition(50, 500);
                    window.draw(saveInfo);
                }

                sf::Text menuControls;
                menuControls.setFont(font);
                menuControls.setString("Sterowanie menu:\nStrzalki - wybor\nEnter - potwierdz");
                menuControls.setCharacterSize(16);
                menuControls.setFillColor(sf::Color::Cyan);
                menuControls.setPosition(50, 400);
                window.draw(menuControls);
            }
        }
        else if (currentState == AppState::Playing) {
            game.render(window);

            if (game.isGameOver()) {
                if (fontLoaded) {
                    sf::Text gameOverText;
                    gameOverText.setFont(font);
                    gameOverText.setString("KONIEC GRY!\nPowrot do menu...");
                    gameOverText.setCharacterSize(30);
                    gameOverText.setFillColor(sf::Color::Red);
                    gameOverText.setPosition(250, 250);
                    window.draw(gameOverText);
                }
            }

            if (fontLoaded) {
                sf::Text controls;
                controls.setFont(font);
                controls.setString("Sterowanie gry:\nA/D lub Strzalki - ruch paletka\nP - zapisz stan (pamiec)\nF5 - zapisz stan (plik)\nL - wczytaj stan z pamieci\nESC - powrot do menu");
                controls.setCharacterSize(16);
                controls.setFillColor(sf::Color::Yellow);
                controls.setPosition(20, 20);
                window.draw(controls);
            }
        }
        else if (currentState == AppState::Scores) {
            if (fontLoaded) {
                sf::Text title;
                title.setFont(font);
                title.setString("TABELA WYNIKOW");
                title.setCharacterSize(40);
                title.setFillColor(sf::Color::Yellow);
                title.setPosition(250, 100);
                window.draw(title);

                sf::Text scores;
                scores.setFont(font);
                scores.setString("1. Gracz 1 - 1000 pkt\n2. Gracz 2 - 800 pkt\n3. Gracz 3 - 600 pkt\n4. Gracz 4 - 400 pkt\n5. Gracz 5 - 200 pkt");
                scores.setCharacterSize(24);
                scores.setFillColor(sf::Color::White);
                scores.setPosition(280, 180);
                window.draw(scores);

                sf::Text instruction;
                instruction.setFont(font);
                instruction.setString("Nacisnij ESC lub ENTER aby wrocic do menu");
                instruction.setCharacterSize(20);
                instruction.setFillColor(sf::Color::Green);
                instruction.setPosition(200, 450);
                window.draw(instruction);
            }
        }

        window.display();
    }

    return 0;
}
