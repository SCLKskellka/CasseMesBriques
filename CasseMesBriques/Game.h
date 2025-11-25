//
// Created by c.barrera on 25/11/2025.
//

#pragma once
#include<raylib.h>

class Game {
public:
    Game() = default;
    ~Game() = default;
    void Run();
private:
    Camera2D _camera = {0};
    int _speed;
    int _score = 0;
    void Init();
};