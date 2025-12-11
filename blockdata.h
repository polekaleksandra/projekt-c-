#ifndef BLOCKDATA_H
#define BLOCKDATA_H
#pragma once

// Prosta struktura danych używana tylko do zapisu stanu gry (pozycja i HP bloku)
struct BlockData {
    float x, y;
    int hp;

    BlockData(float posX, float posY, int health)
        : x(posX), y(posY), hp(health) {
    }

    BlockData() : x(0), y(0), hp(0) {}
};

#endif
