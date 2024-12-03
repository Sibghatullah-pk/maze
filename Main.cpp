#include <iostream>
#include "Maze.h"

/*

g++ -o maze main.cpp maze.cpp
./maze
c
*/
int main()
{
    int rows = 21, cols = 21;
    Maze maze(rows, cols);

    std::cout << "Generated Maze:\n";
    maze.display();

    char choice;
    std::cout << "\nWould you like to add obstacles? (y/n): ";
    std::cin >> choice;

    while (choice == 'y')
    {
        int x, y;
        std::cout << "Enter obstacle coordinates (row col): ";
        std::cin >> x >> y;
        maze.addObstacle(x, y);

        std::cout << "\nUpdated Maze:\n";
        maze.display();

        std::cout << "\nAdd more obstacles? (y/n): ";
        std::cin >> choice;
    }

    std::cout << "\nSolving Maze...\n";

    if (maze.solveMazeDFS(1, 1))
    {
        std::cout << "\nSolved Maze:\n";
        maze.display();
    }
    else
    {
        std::cout << "\nNo solution found!\n";
    }

    return 0;
}
