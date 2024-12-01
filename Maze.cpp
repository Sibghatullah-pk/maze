#include "Maze.h"
#include <iostream>
#include <algorithm>
#include <ctime>

using namespace std;

// Direction vectors (up, down, left, right)
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

Maze::Maze(int rows, int cols) : rows(rows), cols(cols), rng(mt19937(time(0))) {
    grid.resize(rows, vector<char>(cols, WALL));
    generateMaze();
}

void Maze::generateMaze() {
    stack<Cell> cellStack;
    cellStack.push({1, 1});
    grid[1][1] = PATH;

    while (!cellStack.empty()) {
        Cell current = cellStack.top();
        cellStack.pop();

        vector<int> directions = {0, 1, 2, 3};
        shuffle(directions.begin(), directions.end(), rng);

        for (int dir : directions) {
            int nx = current.x + dx[dir] * 2;
            int ny = current.y + dy[dir] * 2;

            if (isValid(nx, ny) && grid[nx][ny] == WALL) {
                grid[current.x + dx[dir]][current.y + dy[dir]] = PATH;
                grid[nx][ny] = PATH;
                cellStack.push({nx, ny});
            }
        }
    }

    grid[1][1] = START;
    grid[rows - 2][cols - 2] = END;
}

bool Maze::isValid(int x, int y) const {
    return x > 0 && y > 0 && x < rows - 1 && y < cols - 1;
}

void Maze::addObstacle(int x, int y) {
    if (isValid(x, y) && grid[x][y] == PATH) {
        grid[x][y] = WALL;
    } else {
        cerr << "Invalid position or already a wall.\n"; // it is meant to be used to output error so better use this instead of cout 
    }
}

bool Maze::solveMazeDFS(int x, int y) {
    if (grid[x][y] == END) return true;
    if (grid[x][y] == VISITED || grid[x][y] == WALL) return false;

    grid[x][y] = VISITED;

    for (int dir = 0; dir < 4; ++dir) {
        int nx = x + dx[dir], ny = y + dy[dir];
        if (solveMazeDFS(nx, ny)) return true;
    }

    grid[x][y] = PATH;
    return false;
}

void Maze::display() const {
    for (const auto &row : grid) {
        for (char cell : row) {
            cout << cell << ' ';
        }
        cout << '\n';
    }
}
