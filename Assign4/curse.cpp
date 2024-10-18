#include <vector>
#include <ncurses.h>
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

using VEC = vector<int>;
using MATRIX = vector<VEC>;

void displayMatrix(const MATRIX &M) {
    clear(); // Clear the screen before displaying
    // Display the matrix
    for (int y = 0; y < M.size(); y++) {
        for (int x = 0; x < M[y].size(); x++) {
            if (M[y][x] == 1) {
                mvprintw(y, x * 5, " X "); // Display "X" for alive cells
            } else {
                mvprintw(y, x * 5, " . "); // Display "." for dead cells
            }
        }
    }
    refresh(); // Refresh to show the grid
}

void gameOfLife(MATRIX &M, bool &exitFlag) {
    int rows = M.size();
    int cols = M[0].size();

    while (!exitFlag) {
        displayMatrix(M); // Display the current state
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Delay for a bit

        MATRIX nextGen(rows, VEC(cols, 0)); // Prepare the next generation

        // Update each cell based on the rules of Conway's Game of Life
        for (int y = 0; y < rows; y++) {
            for (int x = 0; x < cols; x++) {
                int aliveNeighbors = 0;

                // Count alive neighbors
                for (int dy = -1; dy <= 1; dy++) {
                    for (int dx = -1; dx <= 1; dx++) {
                        if (dy == 0 && dx == 0) continue; // Skip the cell itself
                        int ny = y + dy;
                        int nx = x + dx;
                        if (ny >= 0 && ny < rows && nx >= 0 && nx < cols && M[ny][nx] == 1) {
                            aliveNeighbors++;
                        }
                    }
                }

                // Apply the Game of Life rules
                if (M[y][x] == 1) { // Cell is alive
                    nextGen[y][x] = (aliveNeighbors == 2 || aliveNeighbors == 3) ? 1 : 0;
                } else { // Cell is dead
                    nextGen[y][x] = (aliveNeighbors == 3) ? 1 : 0;
                }
            }
        }

        M = nextGen; // Move to the next generation

        // Check for user input to exit
        if (getch() == 'q') {
            exitFlag = true; // Exit on 'q'
        }
    }
}

int main() {
    MEVENT event;
    int yMax = 0, yMin = 1000, xMax = 0, xMin = 1000;
    vector<pair<int, int>> clicks; // Vector to store clicked coordinates
    bool exitFlag = false; // Flag to control the main loop
    bool gameRunning = false; // Flag to control the game running state

    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);
    mouseinterval(3);
    mousemask(ALL_MOUSE_EVENTS, NULL);

    MATRIX M(20, VEC(20, 0)); // Initialize matrix outside the loop

    displayMatrix(M); // Initial display

    while (!exitFlag) {
        if (!gameRunning) {
            int c = getch();
            switch (c) {
                case KEY_MOUSE:
                    if (getmouse(&event) == OK) {
                        if (event.bstate & BUTTON1_PRESSED) {
                            // Update min/max coordinates
                            yMin = (event.y < yMin) ? event.y : yMin;
                            yMax = (event.y > yMax) ? event.y : yMax;
                            xMin = (event.x < xMin) ? event.x / 5 : xMin; // Divide by 5 for spacing
                            xMax = (event.x > xMax) ? event.x / 5 : xMax;

                            // Update the matrix and store the clicked coordinates
                            int matrixY = event.y;
                            int matrixX = event.x / 5; // Convert to matrix coordinates
                            if (matrixY < M.size() && matrixX < M[matrixY].size()) {
                                M[matrixY][matrixX] = 1; // Change value to 1 (representing alive)
                                clicks.push_back({matrixY, matrixX}); // Store the coordinates of the click
                            }

                            displayMatrix(M); // Redisplay the updated matrix
                        }
                    }
                    break;

                case 'n': // Start the Game of Life on 'n'
                    gameRunning = true; // Set game running flag
                    break;

                case 'q': // Exit on 'q'
                    exitFlag = true; // Set the exit flag
                    break;
            }
        } else {
            // If the game is running, call the gameOfLife function
            gameOfLife(M, exitFlag);
            gameRunning = false; // Reset the flag after gameOfLife completes
        }
    }

    endwin(); // End NCurses mode

    // Output the min/max coordinates and the list of clicks
    cout << "yMin: " << yMin << ", yMax: " << yMax << ", xMin: " << xMin << ", xMax: " << xMax << endl;
    cout << "Clicked coordinates:\n";
    for (const auto &click : clicks) {
        cout << "(" << click.first << ", " << click.second << ")\n";
    }

    return 0;
}
