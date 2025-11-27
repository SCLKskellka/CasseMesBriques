//
// Created by c.barrera on 25/11/2025.
//

#pragma once
#include<raylib.h>
#include "Ball.h"

class Game {
public:
    Game();
    ~Game() = default;

    int PlayerLife;

    void Run();
    void IncreaseScore(int value);
    void CheckLoss();

private:
    void Init();
    Camera2D _camera = {0};
    int _score = 0;
    Ball _ball;
    bool _ballOut = false;

};
