#include<raylib.h>
#include "Brick.h"

#include <iostream>
#include <ostream>

Brick::Brick(Vector2 position, Vector2 size, Color color, int hp) {
    Position = position;
    Size = size;
    MyColor = color;
    HP = hp;
    _maxHP = hp;
    _isDead = false;
    GenerateCollisionRect();
}

void Brick::Display() {
    if (!_isDead) {
        DrawRectangle(Position.x, Position.y,Size.x,Size.y,MyColor);
    }
}

void Brick::GetDamage(int damage) {
    if (HP != 0 )
        HP -= damage;
    if(HP <= _maxHP/3*2)
        MyColor = ORANGE;
    if(HP <= _maxHP/3)
        MyColor = YELLOW;
    if (HP <=0) {
        HP = 0;
        _isDead = true;
    }
}
void Brick::GenerateCollisionRect() {
    RectCollision = {Position.x,Position.y,Size.x,Size.y};
}

