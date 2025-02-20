//
//  main.cpp
//  SnakeGame
//
//  Created by Simon Sung on 2/6/25.
//

#include "Game.h"
#include "Colors.h"
#include <raylib.h>

int main() {
    InitWindow(800, 800, "Snake Game");
    SetTargetFPS(60);
    
    Game game;
    GameState state = WELCOME;
    
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(backgroundColor);
        
        if (game.GameOver()) state = GAME_OVER;

        if (state == WELCOME) {
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

    CloseWindow();
    return 0;
}
