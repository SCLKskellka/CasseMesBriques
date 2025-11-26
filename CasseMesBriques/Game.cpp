#include <iostream>
#include<raylib.h>
#include <vector>
#include "Game.h"

#include "Brick.h"
#include "Racket.h"
#include "Brick.h"
#include "BrickGrid.h"
#include "Ball.h"
#include "raymath.h"

Game::Game() {
    _camera = {0};
    _camera.target = (Vector2){0, 0};
    _camera.offset = (Vector2){1600 / 2.0f, 900 / 2.0f}; // choix de la position d'origine
    _camera.rotation = 0;
    _camera.zoom = 1;
    _score = 0;
}

//A ajouter dans la racket ?
Vector2 GetRacketCollisionNormal(Rectangle racketRect, Vector2 ballCenter) {

    float sectionWidth = racketRect.width / 3.0f;
    float leftSectionEnd = racketRect.x + sectionWidth;
    float middleSectionEnd = racketRect.x + 2 * sectionWidth;

    if (ballCenter.x < leftSectionEnd) {
        return Vector2Normalize({-0.7f, -1.0f});
    }
    else if (ballCenter.x < middleSectionEnd) {
        return Vector2Normalize({0.0f, -1.0f});
    }
    else {
        return Vector2Normalize({0.7f, -1.0f});
    }

}




void Game::Init() {
    /**
     *Ouverture de la fenêtre de jeu
     **/
    InitWindow(1600,900,"CustomSnake");

}

void Game::Run() {
    Init();
    //Init
    Racket racket = Racket({0,200}, {50,10},  100, DARKGREEN);
    _camera.target = {racket.Position.x,racket.Position.y - 200};
    //BrickGrid brickGrid = BrickGrid({0,0},{800,600}, 1, 1,0);
    Brick bricktest= Brick({0,-200},{99,19},RED, 1);
    Brick bricktest1= Brick({200,-200},{99,19},RED, 1);
    Brick bricktest2= Brick({300,-200},{99,19},RED, 1);
    Brick bricktest3= Brick({100,-200},{99,19},RED, 1);
    Brick bricktest4= Brick({-100,-200},{99,19},RED, 1);
    Brick bricktest5= Brick({-200,-200},{99,19},RED, 1);
    Brick bricktest6= Brick({-300,-200},{99,19},RED, 1);
    // Brick bricktest7= Brick({0,0},{99,19},GREEN, 1);
    // Brick bricktest8= Brick({0,0},{99,19},GREEN, 1);
    // Brick bricktest9= Brick({0,0},{99,19},GREEN, 1);
    Racket racket = Racket({0,200}, {100,20},  400, DARKGREEN);
    _camera.target = racket.Position;

    Ball _ball = Ball({0, 0}, {0.0f, 1.0f}, 250);

    Rectangle topWall = {-790, -250, 1600, 10};
    Rectangle leftWall = {-800, -250, 10, 900};
    Rectangle rightWall = {790, -250, 10, 900};

    //GameLoop
    while (!WindowShouldClose()) {
        ClearBackground(RAYWHITE);
        //GetFrameTime(); // delta time qui évite la variation du temps en fonction de la puissance machine

        //Update
        racket.Mouvements();
        _ball.update(GetFrameTime());

        Vector2 ballPos = _ball.getPosition();
        Rectangle ballRect = {ballPos.x - 10, ballPos.y - 10, 20, 20};

        Rectangle racketRect = {racket.Position.x, racket.Position.y, 100, 20};

        if (CheckCollisionRecs(ballRect, racketRect)) {
            //Vector2 collisionNormal = {0.0f, -1.0f};
            //_ball.impact(collisionNormal);

            Vector2 collisionNormal = GetRacketCollisionNormal(racketRect, ballPos);
            _ball.impact(collisionNormal);
        }

        if (CheckCollisionRecs(ballRect, topWall)) {
            Vector2 collisionNormal = {0.0f, 1.0f};
            _ball.impact(collisionNormal);
        }
        else if (CheckCollisionRecs(ballRect, leftWall)) {
            Vector2 collisionNormal = {1.0f, 0.0f};
            _ball.impact(collisionNormal);
        }
        else if (CheckCollisionRecs(ballRect, rightWall)) {
            Vector2 collisionNormal = {-1.0f, 0.0f};
            _ball.impact(collisionNormal);
        }

        //Render

        BeginDrawing();
        //DrawUI
            BeginMode2D(_camera);
            //DrawGameplay

                DrawRectangleRec(topWall, BLACK);
                DrawRectangleRec(leftWall, BLACK);
                DrawRectangleRec(rightWall, BLACK);

                //Fonction de rendu
                racket.Display();
                bricktest.Display();
                bricktest1.Display();
                bricktest2.Display();
                bricktest3.Display();
                bricktest4.Display();
                bricktest5.Display();
                bricktest6.Display();
                //brickGrid.Display();

                DrawCircleV(_ball.getPosition(), 10, RED);

            EndMode2D();
        EndDrawing();
    }
    CloseWindow();//toujours penser à fermer les fenêtre , elle se détruisent pas automatiquement

}
