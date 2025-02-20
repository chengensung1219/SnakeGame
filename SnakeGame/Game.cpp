//
//  Game.cpp
//  SnakeGame
//
//  Created by Simon Sung on 2/19/25.
//

#include "Game.h"
#include "Colors.h"
#include <raylib.h>
#include <string>

using namespace std;

int squareSize = 20;
int foodCount = 0;
int score = 0;
int level = 4;

Game::Game() : snake(), food() {}

void Game::Draw(GameState state) {
    food.Draw();
    snake.Draw();
    DisplayBoard(state);
}

void Game::Checker() {
    snake.Move();
    EatFood();
    SetTargetFPS(level);
}

void Game::HandleInput(GameState state) {
    snake.HandleInput(state);
}

void Game::EatFood() {
    if (snake.body[0].x == food.position.x && snake.body[0].y == food.position.y) {
        food.position = food.GetRandomPosition();
        snake.Grow();
        score++;
        foodCount++;
        if (foodCount == 3) {
            level++;
            foodCount = 0;
        }
    }
}

void Game::DisplayBoard(GameState state) {
    
    string scoreText = "SCORE: " + to_string(score);
    string levelText = "LEVEL: " + to_string(level - 3);
    string resultText = scoreText + " / " + levelText;
    
    if (state == GAME_OVER){
        DrawText(resultText.c_str(), 245, 290, 30, blue);
    } else {
        DrawRectangle(35, 35, 730, 5, boundaryColor);
        DrawRectangle(35, 20, 730, 15, backgroundColor);
        DrawRectangle(35, 35, 5, 730, boundaryColor);
        DrawRectangle(20, 35, 15, 730, backgroundColor);
        DrawRectangle(40, 760, 725, 5, boundaryColor);
        DrawRectangle(40, 765, 725, 15, backgroundColor);
        DrawRectangle(760, 40, 5, 725, boundaryColor);
        DrawRectangle(765, 40, 15, 725, backgroundColor);
        DrawText(scoreText.c_str(), 40, 10, 20, boundaryColor);
        DrawText(levelText.c_str(), 680, 10, 20, boundaryColor);
    }
}
    
bool Game::GameOver() {
    
    return (snake.body[0].x < 2 || snake.body[0].x >= 38 || snake.body[0].y < 2 || snake.body[0].y >= 38);
}

void Game::StartGame() {
    snake = Snake();
    food = Food();
    level = 4;
    score = 0;
}

