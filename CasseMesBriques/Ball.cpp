//
// Created by e.prevost on 25/11/2025.
//

#include "Ball.h"
#include "raymath.h"

Ball::Ball(Vector2 position, Vector2 direction, int velocity)
    : _ballPosition(position), _ballDirection(direction), _velocity(velocity) {}

Vector2 Ball::impact(Vector2 collisionNormal) {
    Vector2 targetNormal = Vector2Normalize(collisionNormal);

    float dotProduct = _ballDirection.x * targetNormal.x + _ballDirection.y * targetNormal.y;
    _ballDirection = {
        _ballDirection.x - 2.0f * dotProduct * targetNormal.x,
        _ballDirection.y - 2.0f * dotProduct * targetNormal.y
    };

    return _ballDirection;
}

Vector2 Ball::getPosition() const {
    return _ballPosition;
}

Vector2 Ball::getDirection() const {
    return _ballDirection;
}

void Ball::update(float deltaTime) {
    _ballPosition.x += _ballDirection.x * _velocity * deltaTime;
    _ballPosition.y += _ballDirection.y * _velocity * deltaTime;
}
