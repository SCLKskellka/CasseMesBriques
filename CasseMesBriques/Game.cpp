//
// Created by c.barrera on 25/11/2025.
//
//
// Created by c.barrera on 25/11/2025.
//
#include <iostream>
#include<raylib.h>
#include <vector>
#include "Game.h"

void Game::Init() {
    /**
     *Ouverture de la fenêtre de jeu
     **/
    InitWindow(1600,900,"CustomSnake");
}

void Game::Run() {
    Init();
    //Init


    //GameLoop
    while (!WindowShouldClose()) {
        ClearBackground(RAYWHITE);
        //GetFrameTime(); // delta time qui évite la variation du temps en fonction de la puissance machine

        //Update


        //Render

        BeginDrawing();
        //DrawUI

            BeginMode2D(_camera);
            //DrawGameplay
                //Fonction de rendu

            EndMode2D();
        EndDrawing();
    }
    CloseWindow();//toujours penser à fermer les fenêtre , elle se détruisent pas automatiquement

}
