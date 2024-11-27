#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <random>
#include <algorithm>

using namespace std;

#define WALL '#'n
      
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
    Maze(int r, int c) : rows(r), cols(c), rng(random_device{}()) {
        grid.resize(rows, vector<char>(cols, WALL));
        generateMaze();
    }

    void generateMaze() {
        stack<Cell> s;
        s.push({1, 1});
        grid[1][1] = PATH;

        while (!s.empty()) {
            Cell current = s.top();
            s.pop();

            vector<int> directions = {0, 1, 2, 3};
            shuffle(directions.begin(), directions.end(), rng);

            for (int i : directions) {
                int nx = current.x + dx[i] * 2;
                int ny = current.y + dy[i] * 2;

                if (isValid(nx, ny) && grid[nx][ny] == WALL) {
                    grid[current.x + dx[i]][current.y + dy[i]] = PATH;
                    grid[nx][ny] = PATH;
                    s.push({nx, ny});
                }
            }
        }

        grid[1][1] = START;
        grid[rows - 2][cols - 2] = END;
    }

    bool isValid(int x, int y) {
        return x > 0 && x < rows - 1 && y > 0 && y < cols - 1;
    }

    void addObstacle(int x, int y) {
        if (isValid(x, y) && grid[x][y] == PATH) {
            grid[x][y] = WALL;
        } else {
            cout << "Invalid position or already a wall.\n";
        }
    }

    bool solveMaze() {
        queue<Cell> q;
        q.push({1, 1});

        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        vector<vector<Cell>> parent(rows, vector<Cell>(cols, {-1, -1}));

        visited[1][1] = true;

        while (!q.empty()) {
            Cell current = q.front();
            q.pop();

            if (grid[current.x][current.y] == END) {
                // Trace back the path from END to START
                Cell path = current;
                while (parent[path.x][path.y].x != -1) {
                    grid[path.x][path.y] = VISITED;
                    path = parent[path.x][path.y];
                }
                grid[1][1] = START;
                return true;
            }

            for (int i = 0; i < 4; ++i) {
                int nx = current.x + dx[i];
                int ny = current.y + dy[i];

                if (isValid(nx, ny) && !visited[nx][ny] && (grid[nx][ny] == PATH || grid[nx][ny] == END)) {
                    visited[nx][ny] = true;
                    parent[nx][ny] = current;
                    q.push({nx, ny});
                }
            }
        }
        return false;
    }

    void display() {
        for (const auto &row : grid) {
            for (const auto &cell : row) {
                cout << cell << ' ';
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
