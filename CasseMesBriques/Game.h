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
    void Run();
    void IncreaseScore(int value);

private:
    void Init();
    Camera2D _camera = {0};
    int _score = 0;
    Ball _ball;

};
