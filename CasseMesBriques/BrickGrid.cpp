//
// Created by c.barrera on 26/11/2025.
//
#include <raylib.h>
#include <vector>

#include "Brick.h"
#include "BrickGrid.h"

BrickGrid::BrickGrid(Vector2 gridPosition, Vector2 gridSize, int rowBrickQtt, int colBrickQtt, int padding) {
    _gridPosition = gridPosition;
    _gridSize = gridSize;
    _rowBrickQtt = rowBrickQtt;
    _colBrickQtt = colBrickQtt;
    _padding = padding;

    Vector2 brickSize = BrickSizeCalculation();
    for (int i = 0; i < _rowBrickQtt; i++) {
        std::vector<Brick> tmp;
        for (int j =0; j < _colBrickQtt; j++) {
            Brick newbrick = Brick(
    {BrickPositionCalculation(i,j,brickSize).x,
               BrickPositionCalculation(i,j,brickSize).y},
        {brickSize.x,brickSize.y},RED,3);
            tmp.push_back(newbrick);
        }
        Grid.push_back(tmp);
    }
}

Vector2 BrickGrid::BrickSizeCalculation() {
    Vector2 sizeBrick = {_gridSize.x/_rowBrickQtt - _padding, _gridSize.y/_colBrickQtt - _padding};
    return sizeBrick;
}

Vector2 BrickGrid::BrickPositionCalculation(int rowIndex, int colIndex, Vector2 brickSize) {
    /*
     * ( positionGrid + GridSize) / qttbrick * index
     */
    Vector2 brickposition = {
        _gridSize.x  / _rowBrickQtt * rowIndex + _gridPosition.x,
        _gridSize.y / _colBrickQtt * colIndex + _gridPosition.y
    };
    return brickposition;
}

void BrickGrid::Display() {
    for (int i = 0; i < Grid.size(); i++) {
        for (int j = 0; j < Grid[i].size(); j++) {
            Grid[i][j].Display();
        }
    }
}


