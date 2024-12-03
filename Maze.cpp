#include "Maze.h"
#include <algorithm>
#include <ctime>
#include <iostream>

Maze::Maze(int r, int c) : rows(r), cols(c), rng(std::mt19937(std::time(0)))
{
    grid.resize(rows, std::vector<char>(cols, WALL));
    generateMaze();
}

void Maze::generateMaze()
{
    std::stack<Cell> cellStack;
    cellStack.push({1, 1});
    grid[1][1] = PATH;

    while (!cellStack.empty())
    {
        Cell currentCell = cellStack.top();
        cellStack.pop();

        std::vector<int> possibleDirections = {0, 1, 2, 3};
        std::shuffle(possibleDirections.begin(), possibleDirections.end(), rng);

        for (int direction : possibleDirections)
        {
            int nextX = currentCell.x + dx[direction] * 2;
            int nextY = currentCell.y + dy[direction] * 2;

            if (isValid(nextX, nextY) && grid[nextX][nextY] == WALL)
            {
                grid[currentCell.x + dx[direction]][currentCell.y + dy[direction]] = PATH;
                grid[nextX][nextY] = PATH;
                cellStack.push({nextX, nextY});
            }
        }
    }

    grid[1][1] = START;
    grid[rows - 2][cols - 2] = END;
}

bool Maze::isValid(int x, int y)
{
    return (x > 0 && x < rows - 1 && y > 0 && y < cols - 1);
}

void Maze::addObstacle(int x, int y)
{
    if (isValid(x, y) && grid[x][y] == PATH)
    {
        grid[x][y] = WALL;
    }
    else
    {
        std::cout << "Invalid position or already a wall.\n";
    }
}

bool Maze::solveMazeDFS(int x, int y)
{
    if (grid[x][y] == END)
        return true;

    grid[x][y] = VISITED;

    for (int direction = 0; direction < 4; ++direction)
    {
        int newX = x + dx[direction];
        int newY = y + dy[direction];

        if (isValid(newX, newY) && (grid[newX][newY] == PATH || grid[newX][newY] == END))
        {
            if (solveMazeDFS(newX, newY))
                return true;
        }
    }

    grid[x][y] = PATH;
    return false;
}

void Maze::display()
{
    std::cout << "  ";
    for (int j = 0; j < cols; ++j)
        std::cout << j % 10 << ' ';
    std::cout << '\n';

    for (int i = 0; i < rows; ++i)
    {
        std::cout << i % 10 << ' ';
        for (int j = 0; j < cols; ++j)
            std::cout << grid[i][j] << ' ';
        std::cout << '\n';
    }
}
