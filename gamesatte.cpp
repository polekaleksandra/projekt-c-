#include "GameState.h"
#include "paddle.h"
#include "ball.h"
#include "brick.h"
#include <iostream>
#include <fstream>
#include <sstream>

void GameState::capture(const Paletka& paddle, const Pilka& ball, const std::vector<Brick>& bricks) {
    paddlePosition.x = paddle.getX();
    paddlePosition.y = paddle.getY();

    ballPosition.x = ball.getX();
    ballPosition.y = ball.getY();
    ballVelocity.x = ball.getVx();
    ballVelocity.y = ball.getVy();

    blocks.clear();
    for (const auto& brick : bricks) {
        if (!brick.czyZniszczony()) {
            blocks.emplace_back(brick.getX(), brick.getY(), brick.getHP());
        }
    }

    std::cout << "Stan gry zapisany: " << blocks.size() << " blokow\n";
}

bool GameState::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Blad: Nie mozna otworzyc pliku " << filename << " do zapisu\n";
        return false;
    }

    file << "PADDLE " << paddlePosition.x << " " << paddlePosition.y << "\n";
    file << "BALL " << ballPosition.x << " " << ballPosition.y << " "
        << ballVelocity.x << " " << ballVelocity.y << "\n";
    file << "BLOCKS_COUNT " << blocks.size() << "\n";

    for (const auto& block : blocks) {
        file << block.x << " " << block.y << " " << block.hp << "\n";
    }

    file.close();
    std::cout << "Gra zapisana do pliku: " << filename << "\n";
    return true;
}

bool GameState::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Blad: Nie mozna otworzyc pliku " << filename << " do odczytu\n";
        return false;
    }

    std::string label;

    
    if (!(file >> label >> paddlePosition.x >> paddlePosition.y) || label != "PADDLE") {
        std::cout << "Blad: Nieprawidlowy format pliku (PADDLE)\n";
        return false;
    }

   
    if (!(file >> label >> ballPosition.x >> ballPosition.y >> ballVelocity.x >> ballVelocity.y) || label != "BALL") {
        std::cout << "Blad: Nieprawidlowy format pliku (BALL)\n";
        return false;
    }

    
    int blocksCount;
    if (!(file >> label >> blocksCount) || label != "BLOCKS_COUNT") {
        std::cout << "Blad: Nieprawidlowy format pliku (BLOCKS_COUNT)\n";
        return false;
    }

    
    blocks.clear();
    for (int i = 0; i < blocksCount; ++i) {
        float x, y;
        int hp;
        if (!(file >> x >> y >> hp)) {
            std::cout << "Blad: Nie mozna wczytac bloku " << i << "\n";
            return false;
        }
        blocks.emplace_back(x, y, hp);
    }

    file.close();
    std::cout << "Gra wczytana z pliku: " << filename << "\n";
    std::cout << "Wczytano: " << blocks.size() << " blokow\n";
    return true;
}
