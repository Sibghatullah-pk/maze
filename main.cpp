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

struct Cell
{
    int x, y;
};

class Maze
{
private:
    int rows, cols;
    vector<vector<char>> grid;
    mt19937 rng;
    //mersennne twister 
public:
    Maze(int r, int c)
    {
        rows = r;
        cols = c;
        rng = mt19937(time(0)); // Initialize the RNG with the current time

        // Resize the grid to the given dimensions and fill it with walls
        grid.resize(rows);
        for (int i = 0; i < rows; ++i)
        {
            grid[i].resize(cols, WALL);
        }

        generateMaze(); // Generate the maze after the grid is set up
    }

    void generateMaze()
    {
        stack<Cell> cellStack;
        cellStack.push({1, 1}); // Start at the initial point (1, 1)
        grid[1][1] = PATH;      // Mark the start position as a path

        while (!cellStack.empty())
        {
            // Get the current cell
            Cell currentCell = cellStack.top();
            cellStack.pop();

            // Shuffle the possible directions (up, down, left, right)
            vector<int> possibleDirections = {0, 1, 2, 3};
            shuffle(possibleDirections.begin(), possibleDirections.end(), rng);

            for (int direction : possibleDirections)
            {
                int nextX = currentCell.x + dx[direction] * 2;
                int nextY = currentCell.y + dy[direction] * 2;

                // Check if the next cell is within bounds and is still a wall
                if (isValid(nextX, nextY) && grid[nextX][nextY] == WALL)
                {
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

    bool isValid(int x, int y)
    {
        if (x <= 0 || x >= rows - 1)
            return false; // Check if x is outside the valid range
        if (y <= 0 || y >= cols - 1)
            return false; // Check if y is outside the valid range
        return true;      // If both conditions are valid, return true
    }

    void addObstacle(int x, int y)
    {
        if (isValid(x, y) && grid[x][y] == PATH)
        {
            grid[x][y] = WALL;
        }
        else
        {
            cout << "Invalid position or already a wall.\n";
        }
    }
    bool solveMazeDFS(int x, int y)
    {
        // Base case: If we reach the end point, return true
        if (grid[x][y] == END)
            return true;

        // Mark the current cell as visited
        grid[x][y] = VISITED;

        // Explore all four directions (up, down, left, right)
        for (int direction = 0; direction < 4; ++direction)
        {
            int newX = x + dx[direction];
            int newY = y + dy[direction];

            // Check if the cell is valid and is either a PATH or END
            if (isValid(newX, newY) && (grid[newX][newY] == PATH || grid[newX][newY] == END))
            {
                if (solveMazeDFS(newX, newY))
                {
                    return true;
                }
            }
        }

        // If no path found, backtrack by marking it as a path again
        grid[x][y] = PATH;
        return false;
    }

    void display()
    {
        // Print column indices at the top
        cout <<"  "; // Offset for row numbers
        for (int j = 0; j < cols; ++j)
        {
            cout << j % 10 << ' '; // Print column numbers (mod 10 for better readability)
        }
        cout << '\n';

        for (int i = 0; i < rows; ++i)
        {
            // Print row index on the left side
            cout << (i % 10) << " "; // Print row numbers (mod 10 for alignment)

            // Print the maze content for each row
            for (int j = 0; j < cols; ++j)
            {
                cout << grid[i][j] << ' ';
            }
            cout << '\n';
        }
    }
};

int main()
{
    int rows = 21;
    int cols = 21;
    Maze maze(rows, cols);

    cout << "Generated Maze:\n";
    maze.display();

    char choice;
    cout << "\nWould you like to add obstacles? (y/n): ";
    cin >> choice;

    while (choice == 'y')
    {
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

    if (maze.solveMazeDFS(1, 1))
    {
        cout << "\nSolved Maze:\n";
        maze.display();
    }
    else
    {
        cout << "\nNo solution found!\n";
    }

    return 0;
}
