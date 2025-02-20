//
//  Game.h
//  SnakeGame
//
//  Created by Simon Sung on 2/19/25.
//

#ifndef GAME_H
#define GAME_H

#include "Snake.h"
#include "Food.h"

enum GameState { WELCOME, GAME_RUNNING, GAME_OVER };

class Game {
public:
    Snake snake;
    Food food;
    
    Game();
    void Draw(GameState state);
    void Checker();
    void HandleInput(GameState state);
    void EatFood();
    void DisplayBoard(GameState state);
    bool GameOver();
    void StartGame();
};

#endif
