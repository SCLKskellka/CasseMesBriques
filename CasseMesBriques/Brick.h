//
// Created by c.barrera on 25/11/2025.
//

#pragma once
#include<raylib.h>

class Brick {
public:
    Brick(Vector2 position, Vector2 size, Color color, int hp);
    ~Brick() = default;
    void Display();
    void GetDamage(int damage);

    Vector2 Position;
    Vector2 Size;
    Color MyColor;
    int HP;
private:
    int _maxHP;
    bool _isDead;
};
