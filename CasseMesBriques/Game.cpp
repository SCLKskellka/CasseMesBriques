#include <iostream>
#include <raylib.h>
#include <vector>
#include "Game.h"
#include "Brick.h"
#include "Racket.h"
#include "BrickGrid.h"
#include "Ball.h"
#include "raymath.h"
typedef enum GameScreen { MENU, GAMEPLAY, ENDING } GameScreen;

Game::Game() {
    _camera = {0};
    _camera.target = (Vector2){0, 0};
    _camera.offset = (Vector2){1600 / 2.0f, 900 / 2.0f};
    _camera.rotation = 0;
    _camera.zoom = 1;
    _score = 0;
    PlayerLife = 3;
    _ball = Ball({0, 0}, {0.0f, 1.0f}, 250);
}

void Game::Init() {
    InitWindow(_screenWidth, _screenHeight, "CustomSnake");
}

void Game::CheckLoss() {
    if (!_ballOut) {
        PlayerLife -= 1;
        _ballOut = true;
        if (PlayerLife > 0) {
            _ball = Ball({0, 0}, {0.0f, 1.0f}, 250);
            _ballOut = false;
        }
    }
}

void Game::Run() {
    // Init
    Init();
    GameScreen currentScreen = MENU;
    Racket racket = Racket({0,400}, {100,20}, 250, DARKGREEN);
    _camera.target = {racket.Position.x, racket.Position.y - 400};
    BrickGrid grid = BrickGrid({-700,-350},{1400,400},20,10,2,3);
    Rectangle topWall = {-790, -450, 1600, 10};
    Rectangle leftWall = {-800, -450, 10, 900};
    Rectangle rightWall = {790, -450, 10, 900};
    float shakeDuration = 0.5f;
    float shakeStrength = 5.0f;
    float shakeTimer = 0.0f;
    Vector2 originalCameraTarget = _camera.target;
    Rectangle playButton = { _screenWidth/2.0f-200,_screenHeight/2.0f-200, 400, 300};
    Rectangle menuButton = { _screenWidth/2.0f-200,_screenHeight/2.0f-200, 600, 300};
    int btnState = 0;
    bool btnAction = false;
    Vector2 mousePoint = { 0.0f, 0.0f };

    while (!WindowShouldClose()) {
        ClearBackground(RAYWHITE);
        switch (currentScreen) {
            case MENU: {
                ClearBackground(GRAY);
                mousePoint = GetMousePosition();
                btnAction = false;
                if (CheckCollisionPointRec(mousePoint, playButton)) {
                    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) btnState = 2;
                    else btnState = 1;
                    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) btnAction = true;
                } else btnState = 0;
                if (btnAction) {
                    PlayerLife = 3;
                    _ball = Ball({0, 0}, {0.0f, 1.0f}, 250);
                    _ballOut = false;
                    shakeTimer = 0.0f;
                    originalCameraTarget = _camera.target;
                    currentScreen = GAMEPLAY;
                }
            } break;
            case GAMEPLAY: {
                racket.Mouvements();
                if (!_ballOut) {
                    _ball.update(GetFrameTime());
                }
                Vector2 ballPos = _ball.getPosition();
                Rectangle ballRect = {ballPos.x - 10, ballPos.y - 10, 20, 20};
                Rectangle racketRect = {racket.Position.x, racket.Position.y, 100, 20};
                if (CheckCollisionRecs(ballRect, racketRect)) {
                    float sectionWidth = racketRect.width / 3.0f;
                    float leftSectionEnd = racketRect.x + sectionWidth;
                    float middleSectionEnd = racketRect.x + 2 * sectionWidth;
                    if (ballPos.x < leftSectionEnd) {
                        _ball.setDirection(Vector2Normalize({-0.7f, -1.0f}));
                    } else if (ballPos.x < middleSectionEnd) {
                        _ball.setDirection(Vector2Normalize({0.0f, -1.0f}));
                    } else {
                        _ball.setDirection(Vector2Normalize({0.7f, -1.0f}));
                    }
                }
                if (CheckCollisionRecs(ballRect, topWall)) {
                    Vector2 collisionNormal = {0.0f, 1.0f};
                    _ball.impact(collisionNormal);
                } else if (CheckCollisionRecs(ballRect, leftWall)) {
                    Vector2 collisionNormal = {1.0f, 0.0f};
                    _ball.impact(collisionNormal);
                } else if (CheckCollisionRecs(ballRect, rightWall)) {
                    Vector2 collisionNormal = {-1.0f, 0.0f};
                    _ball.impact(collisionNormal);
                }
                for (int i = 0; i < 20; i++) {
                    for (int j = 0; j < 10; j++) {
                        if (!grid.Grid[i][j].IsDead && CheckCollisionRecs(ballRect, grid.Grid[i][j].RectCollision)) {
                            Vector2 collisionNormal = {0.0f, 1.0f};
                            _ball.impact(collisionNormal);
                            grid.Grid[i][j].GetDamage(1);
                        }
                    }
                }
                if (PlayerLife <= 0) {
                    currentScreen = ENDING;
                }
                if (shakeTimer > 0.0f) {
                    shakeTimer -= GetFrameTime();
                    float shakeOffsetX = (rand() % 100 - 50) / 100.0f * shakeStrength;
                    float shakeOffsetY = (rand() % 100 - 50) / 100.0f * shakeStrength;
                    _camera.target.x = originalCameraTarget.x + shakeOffsetX;
                    _camera.target.y = originalCameraTarget.y + shakeOffsetY;
                } else {
                    _camera.target = originalCameraTarget;
                }
                if (ballPos.y > 650 && !_ballOut) {
                    CheckLoss();
                    shakeTimer = shakeDuration;
                    originalCameraTarget = _camera.target;
                }
            } break;
            case ENDING: {
                mousePoint = GetMousePosition();
                btnAction = false;
                if (CheckCollisionPointRec(mousePoint, menuButton)) {
                    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) btnState = 2;
                    else btnState = 1;
                    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) btnAction = true;
                } else btnState = 0;
                if (btnAction) {
                    grid.ResetGrid();
                    _ballOut = false;
                    shakeTimer = 0.0f;
                    currentScreen = MENU;
                }
            } break;
            default: break;
        }
        BeginDrawing();
        switch (currentScreen) {
            case MENU: {
                DrawRectangle(playButton.x, playButton.y, playButton.width, playButton.height, GREEN);
                DrawText("Play", playButton.x + 50, playButton.height/2 + playButton.y, 100, BLACK);
                DrawText("CASSE MES BRIQUES", 20, 20, 40, DARKGREEN);
            } break;
            case GAMEPLAY: {
                if (PlayerLife <= 0) {
                    DrawRectangle(menuButton.x, menuButton.y, menuButton.width, menuButton.height, GREEN);
                }
                BeginMode2D(_camera);
                DrawRectangleRec(topWall, BLACK);
                DrawRectangleRec(leftWall, BLACK);
                DrawRectangleRec(rightWall, BLACK);
                racket.Display();
                grid.Display();
                DrawCircleV(_ball.getPosition(), 10, RED);
                DrawText(TextFormat("Lives: %d", PlayerLife), -700, 400, 20, BLACK);
                if (PlayerLife <= 0) {
                    DrawText("Defeat", -700, 300, 40, BLACK);
                }
                EndMode2D();
            } break;
            case ENDING: {
                DrawRectangle(menuButton.x, menuButton.y, menuButton.width, menuButton.height, GREEN);
                DrawText("Retour menu", menuButton.x + 50, menuButton.height/2 + playButton.y, 80, BLACK);
            } break;
            default: break;
        }
        EndDrawing();
    }
    CloseWindow();
}

