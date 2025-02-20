//
//  Snake.cpp
//  SnakeGame
//
//  Created by Simon Sung on 2/19/25.
//

#include "Snake.h"
#include "Colors.h"

Snake::Snake() {
    body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
    direction = {1, 0};
}

void Snake::Draw() {
    for (const auto& segment : body) {
        DrawRectangle(segment.x * 20, segment.y * 20, 20, 20, snakeColor);
    }
}

void Snake::Move() {
    body.pop_back();
    body.push_front(Vector2{body[0].x + direction.x, body[0].y + direction.y});
}

void Snake::HandleInput(int state) {
    if (state == 2) return; // GAME_OVER state
    switch (GetKeyPressed()) {
        case KEY_UP:
            if (direction.y == 0) direction = {0, -1};
            break;
        case KEY_DOWN:
            if (direction.y == 0) direction = {0, 1};
            break;
        case KEY_LEFT:
            if (direction.x == 0) direction = {-1, 0};
            break;
        case KEY_RIGHT:
            if (direction.x == 0) direction = {1, 0};
            break;
    }
}

void Snake::Grow() {
    auto x = body[body.size() - 2].x - body[body.size() - 1].x;
    auto y = body[body.size() - 2].y - body[body.size() - 1].y;
    body.push_back(Vector2{body[body.size() - 1].x - x, body[body.size() - 1].y - y});
}
