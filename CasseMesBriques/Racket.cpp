//
// Created by c.barrera on 25/11/2025.
//
#include <raylib.h>
#include "Racket.h"

Racket::Racket(Vector2 position, Vector2 size, float speed, Color color) {
    Position = position;
    Size = size;
    Speed = speed;
    MyColor = color;
}

void Racket::Display() {
    DrawRectangle(Position.x, Position.y,Size.x,Size.y,MyColor);
}

void Racket::Mouvements() {
    if (IsKeyDown(KEY_RIGHT)) {
        Position.x += Speed * GetFrameTime();
    }
    else if (IsKeyDown(KEY_LEFT)) {
        Position.x -= Speed * GetFrameTime();
    }
}

