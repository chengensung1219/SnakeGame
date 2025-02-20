//
//  Snake.h
//  SnakeGame
//
//  Created by Simon Sung on 2/19/25.
//

#ifndef SNAKE_H
#define SNAKE_H

#include <deque>
#include <raylib.h>

class Snake {
public:
    std::deque<Vector2> body;
    Vector2 direction;
    
    Snake();
    void Draw();
    void Move();
    void HandleInput(int state);
    void Grow();
};

#endif
