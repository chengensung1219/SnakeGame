//
//  Food.cpp
//  SnakeGame
//
//  Created by Simon Sung on 2/19/25.
//

#include "Food.h"
#include "Colors.h"

Food::Food() {
    position = GetRandomPosition();
}

Vector2 Food::GetRandomPosition() {
    float x = GetRandomValue(2, 37);
    float y = GetRandomValue(2, 37);
    return Vector2{x, y};
}

void Food::Draw() {
    int x = position.x * 20 + 10;
    int y = position.y * 20 + 10;
    DrawCircle(x, y, 10, foodColor);
}
