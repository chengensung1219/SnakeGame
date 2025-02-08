//
//  main.cpp
//  SnakeGame
//
//  Created by Simon Sung on 2/6/25.
//

#include <iostream>
#include <raylib.h>
#include <deque>

using namespace std;

Color backgroundColor = {255, 255, 255, 255};
Color foodColor = {255, 179, 27, 255};
Color snakeColor = {112, 168, 206, 255};
Color boundaryColor = {57, 57, 57, 255};
Color welcomeColor = {13, 1, 6, 255};
Color blue = {1, 30, 255, 255};

int squareSize = 20;
int squareCount = 40;
typedef enum { WELCOME, GAME_RUNNING, GAME_OVER } GameState;
int level = 4;
int foodCount = 0;
int score = 0;


class Food{
public:
    Vector2 position = GetRandomPosition();
    
    void Draw(){
        int x = position.x * squareSize + 10;
        int y = position.y * squareSize + 10;
        DrawCircle(x, y, 10, foodColor);
    }
    
    Vector2 GetRandomPosition(){
        float x = GetRandomValue(2, squareCount - 3);
        float y = GetRandomValue(2, squareCount - 3);
        
        return Vector2{x, y};
    }
};

class Snake {
public:
    deque<Vector2> body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
    Vector2 direction = {1, 0};
    
    void Draw(){
        for (int i = 0; i < body.size(); i++){
            DrawRectangle(body[i].x * squareSize, body[i].y * squareSize, squareSize, squareSize, snakeColor);
        }
    }
    
    void Move(){
        body.pop_back();
        body.push_front(Vector2{body[0].x + direction.x, body[0].y + direction.y});
    }
    
    void HandleInput(GameState state) {
        if (state == GAME_OVER) return;
        switch (GetKeyPressed()) {
            case KEY_UP:
                if (direction.y == 0) {
                    direction = {0, -1};  // Move up
                }
                break;
            case KEY_DOWN:
                if (direction.y == 0) {
                    direction = {0, 1};   // Move down
                }
                break;
            case KEY_LEFT:
                if (direction.x == 0) {
                    direction = {-1, 0};  // Move left
                }
                break;
            case KEY_RIGHT:
                if (direction.x == 0) {
                    direction = {1, 0};   // Move right
                }
                break;
        }
    }
    void Grow(){
        
        auto x = (body[body.size() - 2].x) - (body[body.size() - 1].x);
        auto y = (body[body.size() - 2].y) - (body[body.size() - 1].y);
        body.push_back(Vector2{body[body.size() - 1].x - x, body[body.size() - 1].y - y});

    }
};

class Game{
public:
    Snake snake = Snake();
    Food food = Food();

    
    void Draw(GameState state){
        food.Draw();
        snake.Draw();
        DisplayBoard(state);
    }
    
    void Checker(){
        snake.Move();
        EatFood();
        SetTargetFPS(level);
    }
    
    void HandleInput(GameState state){
        
        snake.HandleInput(state);
    }
    
    void EatFood(){
        if (snake.body[0].x == food.position.x && snake.body[0].y == food.position.y){
            
            food.position = food.GetRandomPosition();
            snake.Grow();
            score += 1;
            foodCount += 1;
            if (foodCount == 3){
                level += 1;
                foodCount = 0;
            }
        }
    }
    
    void DisplayBoard(GameState state){
        
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

    
    bool GameOver(){
        Rectangle snakeHead = {snake.body[0].x * squareSize, snake.body[0].y * squareSize, (float)squareSize, (float)squareSize};
        Rectangle boundryTop = {35, 35, 730, 10};
        Rectangle boundryLeft = {35, 35, 5, 730};
        Rectangle boundryBottom = {40, 760, 725, 5};
        Rectangle boundryRight = {760, 40, 5, 725};
        
        if (CheckCollisionRecs(snakeHead, boundryTop) ||
            CheckCollisionRecs(snakeHead, boundryLeft) ||
            CheckCollisionRecs(snakeHead, boundryBottom) ||
            CheckCollisionRecs(snakeHead, boundryRight)){
            return true;
        }

            // Check if the snake collides with itself
            for (int i = 1; i < snake.body.size(); i++) {
                if (snake.body[0].x == snake.body[i].x && snake.body[0].y == snake.body[i].y) {
                    return true;
                }
            }

            return false;
    }
    
    void StartGame(){
        snake.body.clear();
        snake.body.push_back({6, 9});
        snake.body.push_back({5, 9});
        snake.body.push_back({4, 9});
        
        snake.direction = {1, 0};
        
        food.position = food.GetRandomPosition();
        
        level = 4;
        score = 0;
        
        
    }
    
    
};


int main() {
    // Initialize window
    InitWindow(squareSize * squareCount, squareSize * squareCount, "Snake Game");

    // Set target FPS
    SetTargetFPS(60);

    Game game = Game();
    
    GameState state = WELCOME;
    
    // Main game loop
    while (!WindowShouldClose()) {
        // Start drawing
        
        BeginDrawing();
        ClearBackground(backgroundColor);
        
        if (game.GameOver()) {
                state = GAME_OVER;
        }
        
        if (state == WELCOME){
            
            DrawText("Snake Game", 255, 345, 50, welcomeColor);
            DrawText("Press SPACE to start", 230, 405, 30, welcomeColor);
            
            if (IsKeyPressed(KEY_SPACE)) {
                game.StartGame();
                state = GAME_RUNNING;
            }
            
        } else if (state == GAME_RUNNING) {
            
            game.HandleInput(state);
            game.Checker();
            game.Draw(state);
            
        } else {
            DrawText("GAME OVER", 205, 345, 65, RED);
            DrawText("Press", 245, 425, 30, BLACK);
            DrawText("R", 360, 425, 30, RED);
            DrawText("to Restart", 405, 425, 30, BLACK);
            game.DisplayBoard(state);
            SetTargetFPS(60);

            if (IsKeyPressed(KEY_R)) {
                game.StartGame();
                state = GAME_RUNNING;
            }
        }
        EndDrawing();
    }

    // Close window
    CloseWindow();

    return 0;
}
