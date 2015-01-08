# GameOfLife
C++/Windows Implementation of Conway's Game of Life

## Rules

(see [wikipedia](http://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) for more info)

The rules of the game are simple. The environment is a grid made up of individual 'cells'.

1. Any live cell with fewer than two live neighbours dies, as if caused by under-population.
2. Any live cell with two or three live neighbours lives on to the next generation.
3. Any live cell with more than three live neighbours dies, as if by overcrowding.
4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

## Commands

You must press enter after typing a command.

- q: Quit / halt execution. This terminates execution immediately.
- p: Pause / pause execution. This pauses execution. Only valid if running. May quit from here.
- r: Resume / resume execution. This resumes execution. Only valid if paused.
- x<num>: Execution speed / set iteration delay. Enter in x100 to set delay to 100ms, x200 for 200ms, etc.

## Screenshots

From wikipedia, Gosper's Glider Gun:

<img src=http://upload.wikimedia.org/wikipedia/commons/e/e5/Gospers_glider_gun.gif>

Still frame of GameOfLife:

<img src=http://i.imgur.com/UzzydBc.png>

## Build environment

This is designed specifically for a Windows/Visual Studio build environment. Built on Win8.1 x64 with VS 2013 Update 2.
