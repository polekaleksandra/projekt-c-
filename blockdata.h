#ifndef BLOCKDATA_H
#define BLOCKDATA_H
#pragma once

struct BlockData {
    float x, y;
    int hp;

    BlockData(float posX, float posY, int health)
        : x(posX), y(posY), hp(health) {
    }

    
    BlockData() : x(0), y(0), hp(0) {}
};

#endif
