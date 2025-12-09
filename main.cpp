#include "Game.h"
#include "Menu.h"
#include "GameState.h"
#include "ball.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream> 
#include <string>  

enum class AppState { Menu, Playing, Scores, Exiting };

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Arkanoid - Projekt");
    window.setFramerateLimit(60);

    sf::VertexArray background(sf::Quads, 4);
    background[0].position = sf::Vector2f(0, 0);
    background[1].position = sf::Vector2f(800, 0);
    background[2].position = sf::Vector2f(800, 600);
    background[3].position = sf::Vector2f(0, 600);
    background[0].color = sf::Color(30, 0, 60);
    background[1].color = sf::Color(30, 0, 60);
    background[2].color = sf::Color(0, 0, 10);
    background[3].color = sf::Color(0, 0, 10);

    Menu menu(800, 600);
    Game game;
    AppState currentState = AppState::Menu;
    GameState savedGameState;
    bool hasSavedState = false;

    int currentShapeIndex = 0;

    int highScore = 0;
    int lastScore = 0;

    std::ifstream inputFile("highscore.txt");
    if (inputFile.is_open()) {
        inputFile >> highScore;
        inputFile.close();
    }
    

    sf::Font font;
    bool fontLoaded = false;
    if (font.loadFromFile("arial.ttf") || font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        fontLoaded = true;
    }

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            if (currentState == AppState::Menu) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Up) menu.MoveUp();
                    if (event.key.code == sf::Keyboard::Down) menu.MoveDown();

                    if (event.key.code == sf::Keyboard::Enter) {
                        int selected = menu.getSelectedItem();

                        if (selected == 0) { 
                            currentState = AppState::Playing;
                            game.reset();
                            game.setBallType(static_cast<BallType>(currentShapeIndex));
                        }
                        else if (selected == 1) { 
                            currentShapeIndex = (currentShapeIndex + 1) % 3;
                            menu.changeShapeText(static_cast<BallType>(currentShapeIndex));
                        }
                        else if (selected == 2) { 
                            GameState loadedState;
                            if (loadedState.loadFromFile("zapis.txt")) {
                                if (game.loadState(loadedState)) {
                                    currentState = AppState::Playing;
                                }
                            }
                        }
                        else if (selected == 3) { currentState = AppState::Scores; } 
                        else if (selected == 4) { window.close(); } 
                    }
                }
            }
            else if (currentState == AppState::Playing) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape) currentState = AppState::Menu;

                    if (event.key.code == sf::Keyboard::P) {
                        game.captureState(savedGameState);
                        hasSavedState = true;
                        std::cout << "Zapisano w pamieci (P)\n";
                    }
                    if (event.key.code == sf::Keyboard::F5) {
                        GameState gs;
                        game.captureState(gs);
                        gs.saveToFile("zapis.txt");
                        std::cout << "Zapisano do pliku (F5)\n";
                    }
                    if (event.key.code == sf::Keyboard::L && hasSavedState) {
                        game.loadState(savedGameState);
                    }
                }
            }
            else if (currentState == AppState::Scores) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Enter)
                        currentState = AppState::Menu;
                }
            }
        }

        if (currentState == AppState::Playing) {
            if (!game.isGameOver()) {
                game.update();
            }
            else {
                
                static sf::Clock clock;
                if (clock.getElapsedTime().asSeconds() > 2.0f) {
                    
                    lastScore = game.getScore();

                    if (lastScore > highScore) {
                        highScore = lastScore;
                        
                        std::ofstream outputFile("highscore.txt");
                        if (outputFile.is_open()) {
                            outputFile << highScore;
                            outputFile.close();
                        }
                    }

                    currentState = AppState::Menu;
                    clock.restart();
                }
            }
        }

        window.clear();
        window.draw(background);

        if (currentState == AppState::Menu) {
            menu.draw(window);

            
            if (fontLoaded) {
                sf::Text best;
                best.setFont(font);
                best.setString("Rekord: " + std::to_string(highScore));
                best.setCharacterSize(18);
                best.setFillColor(sf::Color::Yellow);
                best.setPosition(650, 10);
                window.draw(best);

                sf::Text help;
                help.setFont(font);
                help.setString("Strzalki - nawigacja | Enter - wybor/zmiana");
                help.setCharacterSize(14);
                help.setFillColor(sf::Color::Cyan);
                help.setPosition(10, 570);
                window.draw(help);
            }
        }
        else if (currentState == AppState::Playing) {
            game.render(window);

            if (game.isGameOver() && fontLoaded) {
                sf::Text over;
                over.setFont(font);
                over.setString("GAME OVER");
                over.setCharacterSize(50);
                over.setFillColor(sf::Color::Red);
                sf::FloatRect textRect = over.getLocalBounds();
                over.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
                over.setPosition(400, 300);
                window.draw(over);
            }
        }
        else if (currentState == AppState::Scores) {
           
            if (fontLoaded) {
                sf::Text title;
                title.setFont(font);
                title.setString("TABELA WYNIKOW");
                title.setCharacterSize(40);
                title.setFillColor(sf::Color::Magenta);
             
                sf::FloatRect tr = title.getLocalBounds();
                title.setOrigin(tr.width / 2, tr.height / 2);
                title.setPosition(400, 100);
                window.draw(title);

                std::string scoreStr = "";
                scoreStr += "NAJLEPSZY WYNIK:  " + std::to_string(highScore) + "\n\n";
                scoreStr += "OSTATNI WYNIK:    " + std::to_string(lastScore) + "\n";

                sf::Text scoresText;
                scoresText.setFont(font);
                scoresText.setString(scoreStr);
                scoresText.setCharacterSize(30);
                scoresText.setFillColor(sf::Color::White);

                sf::FloatRect sr = scoresText.getLocalBounds();
                scoresText.setOrigin(sr.width / 2, sr.height / 2);
                scoresText.setPosition(400, 300);
                window.draw(scoresText);

                sf::Text info;
                info.setFont(font);
                info.setString("Nacisnij ESC aby wrocic");
                info.setCharacterSize(20);
                info.setFillColor(sf::Color::Green);
                info.setPosition(280, 500);
                window.draw(info);
            }
        }

        window.display();
    }
    return 0;
}
