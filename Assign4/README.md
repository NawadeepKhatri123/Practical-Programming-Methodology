CRAP GAME & CONWAY'S GAME OF LIFE


This program simulates the dice game of Craps, allowing users to place bets and play against the house. 
Players roll two dice, with the game following specific rules to determine wins and losses based on the rolled totals.

Features
    
    Players start with 100 credits and can wager amounts within their balance.
    Clear outcomes based on the rules of Craps:
    Win on the first roll with a total of 7 or 11.
    Lose on the first roll with a total of 2, 3, or 12.
    Establish a point for totals of 4, 5, 6, 8, 9, or 10, requiring further rolls to win or lose.
    Option to play multiple rounds until the player chooses to exit or runs out of credits.

Compile & run the program

    g++ -o crap Prog2.cpp
    ./crap


Players are prompted to enter a wager amount before each round.
Valid wagers must be greater than 0 and not exceed the current credit balance.
Follow the on-screen messages to understand the outcome of each roll and the game.



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



