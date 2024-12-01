#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <stack>
#include <random>
#include <string>
using namespace std;

class Maze {
public:
    Maze(int rows, int cols);
    void display() const;
    void addObstacle(int x, int y);
    bool solveMazeDFS(int startX, int startY);

private:
    enum CellType { WALL = '#', PATH = ' ', START = 'S', END = 'E', VISITED = '.' };// anum are used for better understandings and for avoiding unwanted errors that can happen in case of hard coded letters like # or S or anything 
    struct Cell { int x, y; };

    int rows, cols;
    vector<std::vector<char>> grid;
    mt19937 rng;

    void generateMaze();
    bool isValid(int x, int y) const;
};

#endif
