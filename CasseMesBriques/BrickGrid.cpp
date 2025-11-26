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
    std::vector<Brick> tmp;
    Vector2 brickSize = BrickSizeCalculation();
    for (int i = 0; i < _rowBrickQtt; i++) {
        for (int j =0; j < _colBrickQtt; j++) {
            Brick newbrick = Brick(
    {BrickPositionCalculation(i,j,brickSize).x,
               BrickPositionCalculation(i,j,brickSize).y},
        {brickSize.x,brickSize.y},RED,3);
            tmp.push_back(newbrick);
        }
        Grid.push_back(std::vector<Brick>());
    }
}

Vector2 BrickGrid::BrickSizeCalculation() {
    Vector2 sizeBrick = {_gridSize.x/_rowBrickQtt - _padding, _gridSize.y/_colBrickQtt - _padding};
    return sizeBrick;
}

Vector2 BrickGrid::BrickPositionCalculation(int rowIndex, int colIndex, Vector2 brickSize) {
    /*
     * ( positionGrid + GridSize / qttbrick ) * ( 1 + index )
     */
    Vector2 brickposition = {
        (_gridPosition.x + _gridSize.x / _rowBrickQtt) * (1 + rowIndex),
        (_gridPosition.y + _gridSize.y / _colBrickQtt) * (1 + colIndex)
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


