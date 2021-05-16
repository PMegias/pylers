
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

## Inspiration
It was a project that we thought it could be fun for our first hackathon together and not hard enough to get so stressed we give up.

## What it does
It simulates the game of life, reporting real time statistics.

## How we built it
With **love** and C++. Using SFML to display the graphics.

## Challenges we ran into
We had to learn SFML from zero. It was challenging but the results are really good (at least for us :) ).
We also had to make parts of the code parallel because of performance issues (fps went on vacation).

## Accomplishments that we're proud of
Building the whole app from scratch.

## What we learned
Mainly SFML, but also how to merge SFML and parallelism. Also printing plot generated with gnuplot in real time within the game window.

## What's next for The game of life
Add some extra features like different classes of entities that compete with each other or different sets of rules.


