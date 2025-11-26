//
// Created by c.barrera on 26/11/2025.
//

#pragma once
#include <raylib.h>
#include <vector>

#include "Brick.h"

class BrickGrid {
public:
    BrickGrid(Vector2 gridPosition, Vector2 gridSize, int rowBrickQtt, int colBrickQtt, int padding);
    ~BrickGrid() = default;
    void Display();
    bool IsGridCleared();
    //Brick GetBrick(int x, int y);

    std::vector<std::vector<Brick>> Grid;
private:
    Vector2 BrickSizeCalculation();
    Vector2 BrickPositionCalculation(int rowIndex, int colIndex, Vector2 brickSize);

    Vector2 _gridPosition;
    Vector2 _gridSize;
    int _rowBrickQtt;
    int _colBrickQtt;
    int _padding;
};