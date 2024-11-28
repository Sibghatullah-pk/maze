#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <random>
#include <algorithm>
#include <ctime>

using namespace std;
#define WALL '#'
#define PATH ' '
#define START 'S'
#define END 'E'
#define VISITED '.'

// Direction vectors (up, down, left, right)
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

struct Cell {
    int x, y;
};

class Maze {
private:
    int rows, cols;
    vector<vector<char>> grid;
    mt19937 rng;

public:
  Maze(int r, int c) {
    rows = r;
    cols = c;
    rng = mt19937(time(0)); // Initialize the RNG with the current time

    // Resize the grid to the given dimensions and fill it with walls
    grid.resize(rows);
    for (int i = 0; i < rows; ++i) {
        grid[i].resize(cols, WALL);
    }

    generateMaze(); // Generate the maze after the grid is set up
}

void generateMaze() {
    stack<Cell> cellStack;
    cellStack.push({1, 1}); // Start at the initial point (1, 1)
    grid[1][1] = PATH; // Mark the start position as a path

    while (!cellStack.empty()) {
        // Get the current cell
        Cell currentCell = cellStack.top();
        cellStack.pop();

        // Shuffle the possible directions (up, down, left, right)
        vector<int> possibleDirections = {0, 1, 2, 3};
        shuffle(possibleDirections.begin(), possibleDirections.end(), rng);

        for (int direction : possibleDirections) {
            int nextX = currentCell.x + dx[direction] * 2;
            int nextY = currentCell.y + dy[direction] * 2;

            // Check if the next cell is within bounds and is still a wall
            if (isValid(nextX, nextY) && grid[nextX][nextY] == WALL) {
                // Create a path by removing the wall between current and next cell
                grid[currentCell.x + dx[direction]][currentCell.y + dy[direction]] = PATH;
                grid[nextX][nextY] = PATH;

                // Push the next cell onto the stack
                cellStack.push({nextX, nextY});
            }
        }
    }

    // Mark start and end points
    grid[1][1] = START;
    grid[rows - 2][cols - 2] = END;
}

   bool isValid(int x, int y) {
    if (x <= 0 || x >= rows - 1) return false;  // Check if x is outside the valid range
    if (y <= 0 || y >= cols - 1) return false;  // Check if y is outside the valid range
    return true;  // If both conditions are valid, return true
}


    void addObstacle(int x, int y) {
        if (isValid(x, y) && grid[x][y] == PATH) {
            grid[x][y] = WALL;
        } else {
            cout << "Invalid position or already a wall.\n";
        }
    }
bool solveMaze() {
    queue<Cell> pathQueue;  // Queue to explore the maze
    pathQueue.push({1, 1});  // Start from the initial position

    vector<vector<bool>> visitedCells(rows, vector<bool>(cols, false));  // Track visited cells
    vector<vector<Cell>> parentCell(rows, vector<Cell>(cols, {-1, -1}));  // Store the parent of each cell

    visitedCells[1][1] = true;  // Mark the start cell as visited

    while (!pathQueue.empty()) {
        Cell currentCell = pathQueue.front();  // Get the current cell from the queue
        pathQueue.pop();  // Remove it from the queue

        if (grid[currentCell.x][currentCell.y] == END) {
            // If we reach the END, trace the path back to the start
            Cell backtrackCell = currentCell;
            while (parentCell[backtrackCell.x][backtrackCell.y].x != -1) {
                grid[backtrackCell.x][backtrackCell.y] = VISITED;  // Mark the visited path
                backtrackCell = parentCell[backtrackCell.x][backtrackCell.y];  // Move to the parent
            }
            grid[1][1] = START;  // Ensure the start position is marked correctly
            return true;  // Return true when the path is found
        }

        // Explore neighboring cells (up, down, left, right)
        for (int direction = 0; direction < 4; ++direction) {
            int newX = currentCell.x + dx[direction];
            int newY = currentCell.y + dy[direction];

            // Check if the neighboring cell is valid, unvisited, and is either a PATH or the END
            if (isValid(newX, newY) && !visitedCells[newX][newY] && (grid[newX][newY] == PATH || grid[newX][newY] == END)) {
                visitedCells[newX][newY] = true;  // Mark the cell as visited
                parentCell[newX][newY] = currentCell;  // Set the parent for backtracking
                pathQueue.push({newX, newY});  // Add the new cell to the queue for further exploration
            }
        }
    }

    return false;  // If no solution is found, return false
}

   void display() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << grid[i][j] << ' ';
        }
        cout << '\n';
    }
}

};

int main() {
    int rows = 21;
    int cols = 21;
    Maze maze(rows, cols);

    cout << "Generated Maze:\n";
    maze.display();

    char choice;
    cout << "\nWould you like to add obstacles? (y/n): ";
    cin >> choice;

    while (choice == 'y') {
        int x, y;
        cout << "Enter obstacle coordinates (row col): ";
        cin >> x >> y;
        maze.addObstacle(x, y);

        cout << "\nUpdated Maze:\n";
        maze.display();

        cout << "\nAdd more obstacles? (y/n): ";
        cin >> choice;
    }

    cout << "\nSolving Maze...\n";

    if (maze.solveMaze()) {
        cout << "\nSolved Maze:\n";
        maze.display();
    } else {
        cout << "\nNo solution found!\n";
    }

    return 0;
}
