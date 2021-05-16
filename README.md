
# HackUPC 2021
# Team: Pyl·lers
Carlos Bayona

Jonathan Calderon

Pedro Megias

# Project: Conway's Game of Life

The universe of the Game of Life is an infinite, two-dimensional grid of square cells, each of which is in one of two possible states, live or dead, (or populated and unpopulated, respectively). Every cell interacts with its eight neighbours, which are the cells that are horizontally, vertically, or diagonally adjacent. At each step in time, a cycle occurs, following the next rules:

  - Any live cell with fewer than two live neighbours dies, as if by underpopulation.
  - Any live cell with two or three live neighbours lives on to the next generation.
  - Any live cell with more than three live neighbours dies, as if by overpopulation.
  - Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

These rules, which compare the behavior of the automaton to real life, can be condensed into the following:

  - Any live cell with two or three live neighbours survives.
  - Any dead cell with three live neighbours becomes a live cell.
  - All other live cells die in the next generation. Similarly, all other dead cells stay dead.

The project is build mainly with love and C++. The graphic part of the project leans on the SFML library a lot, but it was one of the main challenges for us. Also we use parallelization techniques, using OMP, for improve the performance of the display and avoid all types of performance issues like fps drops and more. Finally the project also uses gnuplot to generate some plots with useful and interesting information on real time within the game windows, giving the opportunity to the user to see how his game is advancing.

We hope to extend all this work creating new rules for the cells to stay alive or die and also implement a new mode called The Game of War consisting of two teams fighting each other with exclusive rules.

# Dependencies
To install the dependencies
`sudo apt install libsfml-dev libomp-dev`

# Compile and Execute
There are two ways:
  1. Using the script provided by us: `./run.sh`
  2. Make and execute: `make clean ; make ; ./build`

We highly recommend to redirect build's output to `/dev/null` (both `stdout` and `stderr`) since the code prints a lot of garbage.

