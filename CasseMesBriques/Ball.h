//
// Created by e.prevost on 25/11/2025.
//

#ifndef CASSEMESBRIQUES_BALL_H
#define CASSEMESBRIQUES_BALL_H
#include <vector>

#include "raylib.h"


class Ball {

public:
    Ball(Vector2 _pos, Vector2 _vel, int velocity);

    Vector2 impact(Vector2 targetNormal);

    Vector2 getPosition() const;
    Vector2 getDirection() const;

    void update(float deltaTime);

private:
    Vector2 _ballPosition;
    Vector2 _ballDirection;
    int _velocity;
};


#endif //CASSEMESBRIQUES_BALL_H