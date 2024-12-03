#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <stack>
#include <random>
#include <iostream>

// Direction vectors (up, down, left, right)
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

#define WALL '#'
#define PATH ' '
#define START 'S'
#define END 'E'
#define VISITED '.'

struct Cell
{
    int x, y;
};

class Maze
{
private:
    int rows, cols;
    std::vector<std::vector<char>> grid;
    std::mt19937 rng;

    bool isValid(int x, int y);

public:
    Maze(int r, int c);
    void generateMaze();
    void addObstacle(int x, int y);
    bool solveMazeDFS(int x, int y);
    void display();
};

#endif // MAZE_H
