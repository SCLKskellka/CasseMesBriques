//
// Created by c.barrera on 25/11/2025.
//

#pragma once
#include <raylib.h>

class Racket {
public:
    Racket(Vector2 position, Vector2 size, float speed, Color color);
    ~Racket() = default;
    void Display();
    void Mouvements();

    Vector2 Position;
    Vector2 Size;
    float Speed;
    Color MyColor;
};