//
//  Food.h
//  SnakeGame
//
//  Created by Simon Sung on 2/19/25.
//

#ifndef FOOD_H
#define FOOD_H

#include <raylib.h>

class Food {
public:
    Vector2 position;
    Food();
    void Draw();
    Vector2 GetRandomPosition();
};

#endif
