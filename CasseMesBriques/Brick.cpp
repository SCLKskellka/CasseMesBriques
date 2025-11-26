//
// Created by c.barrera on 25/11/2025.
//

#include<raylib.h>
#include "Brick.h"

Brick::Brick(Vector2 position, Vector2 size, Color color, int hp) {
    Position = position;
    Size = size;
    MyColor = color;
    HP = hp;
}

void Brick::Display() {
    DrawRectangle(Position.x, Position.y,Size.x,Size.y,MyColor);
}

