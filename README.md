# Maze Generation and Solver Project

## Description
This project is a **maze generator and solver** written in C++. It uses recursive backtracking to generate random mazes and implements breadth-first search (BFS) for pathfinding. The project allows users to generate mazes, add obstacles, and solve them programmatically or manually.

## Features
- **Maze Generation:** Generates a maze using recursive backtracking.
- **Maze Solving:** Solves the maze using BFS with backtracking for the solution path.
- **User Interaction:** Allows users to add custom obstacles.
- **Visualization:** Displays the maze in the console with clear markings for the start (`S`), end (`E`), walls (`#`), paths (` `), and visited cells (`.`).
- **Customizable Size:** Maze dimensions can be set when initializing.

## Getting Started

### Prerequisites
- A C++ compiler (e.g., GCC or Clang).
- An IDE or text editor (e.g., Visual Studio Code, Eclipse).

### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/sibghatullah-pk/maze-generator-solver.git
   cd maze-generator-solver
   ```
2. Compile the program:
   ```bash
   g++ maze.cpp -o maze
   ```

3. Run the program:
   ```bash
   ./maze
   ```

## Usage
- The program will generate a maze and display it in the console.
- You can add obstacles by entering coordinates when prompted.
- The maze solver will attempt to find a path from the start (`S`) to the end (`E`).
  
### Example Output:
```
Generated Maze:
# # # # # # # # # # # # # # # # # # # #
# S     #     #     #         #       #
# ##### # ### # ### ##### ##### ##### #
#       #   #     # #     #   #     # #
# ########### ### # # ### ### # ### # #
#     #       #   #   #   #   # #   # #
##### # ##### ### ### ##### ### # ### #
#   # # #     #     # #     # # # #   #
# ### ### ### ####### ### ### # ### ###
#   #   #   #     #     # #   #     # #
### ##### ### ##### ### ### ##### ### #
# #     #   #   #   #   #   # #     # #
# ### ##### ### ##### ### # ### ##### #
# #     #     #     # #   #   #     # #
# # ##### ##### ### ### ##### ##### ###
# # #       #   #     #   #       #   #
# ### ### ### ######### ######### ### #
# # #   #   #         #       # #   # #
# # ### ##### ### ### ##### ### ### # #
#       #     #   #       #     # E   #
# # # # # # # # # # # # # # # # # # # #
Would you like to add obstacles? (y/n):
```

## Functions Overview
- `generateMaze()`: Generates the maze using recursive backtracking.
- `solveMaze()`: Solves the maze using BFS.
- `addObstacle(int x, int y)`: Allows users to add obstacles at specified coordinates.
- `display()`: Displays the maze in the console.
- `isValid(int x, int y)`: Checks if a cell is within bounds and accessible.

## Future Enhancements
- Add a graphical interface using **SFML** or **Qt**.
- Implement additional pathfinding algorithms (A*, Dijkstra).
- Support exporting and importing maze layouts.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Contributing
Contributions are welcome! Please fork the repository and submit a pull request for any features or bug fixes.

## Acknowledgments
- Inspired by classic maze generation algorithms and pathfinding techniques.

---

You can adjust the **License** and **Contributing** sections based on your preferences. Would you like me to draft a specific **MIT License** file for you?
