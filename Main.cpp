#include <iostream>
#include "Maze.h"

using namespace std;

int main() {
    int rows = 21, cols = 21;
    Maze maze(rows, cols);

    cout << "Generated Maze:\n";
    maze.display();

    char choice;
    cout << "\nAdd obstacles? (y/n): ";
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
    if (maze.solveMazeDFS(1, 1)) {
        cout << "\nSolved Maze:\n";
        maze.display();
    } else {
        cout << "\nNo solution found!\n";
    }

    return 0;
}
