#include <iostream>
#include<raylib.h>
#include <vector>
#include "Game.h"

#include "Brick.h"
#include "Racket.h"
#include "Brick.h"

Game::Game() {
    _camera = {0};
    _camera.target = (Vector2){0,0};
    _camera.offset = (Vector2){1600/2.0f, 900/2.0f}; // choix de la position d'origine
    _camera.rotation = 0;
    _camera.zoom = 1;
    _score = 0;
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

    //GameLoop
    while (!WindowShouldClose()) {
        ClearBackground(RAYWHITE);
        //GetFrameTime(); // delta time qui évite la variation du temps en fonction de la puissance machine

        //Update
        racket.Mouvements();

        //Render

        BeginDrawing();
        //DrawUI
            BeginMode2D(_camera);
            //DrawGameplay
                //Fonction de rendu
                racket.Display();
                brick.Display();
            EndMode2D();
        EndDrawing();
    }
    CloseWindow();//toujours penser à fermer les fenêtre , elle se détruisent pas automatiquement

}
