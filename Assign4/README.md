
Conway's Game of Life in C++

Description

    This program implements Conway's Game of Life using the NCurses library for a text-based graphical interface. 
    Users can interact with a grid where cells can be either alive (represented by "X") or dead (represented by "."). 
    The simulation updates the grid according to the rules of the Game of Life, allowing users to create initial configurations by clicking on the grid.

Install NCurses (ubuntu/debian)

    sudo agpt-get install libncurses5-dev libncursesw5-dev
    
Compile the program

    g++ -o curses curses.cpp -lncurses

Run the program

    ./curses


Controls

    Left Click: Toggle the state of the clicked cell (alive/dead).
    Press 'n': Start the Game of Life simulation.
    Press 'q': Exit the program.

Notes
    The grid size is set to 20x20 cells.
    The program updates the display every 500 milliseconds during the simulation.
    Upon exiting, the program outputs the minimum and maximum coordinates of the cells that were clicked, along with a list of those coordinates.



