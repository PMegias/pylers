# pylers
Los pyl·lers que te pyl·lean el pyl·lon with Serpiente

The universe of the Game of Life is an infi
nite, two-dimensional orthogonal grid of square cells, each of which is in one of two possible states, live or dead, (or populated and unpopulated, respectively). Every cell interacts with its eight neighbours, which are the cells that are horizontally, vertically, or diagonally adjacent. At each step in time, the following transitions occur:

Te hago la vida, te hago le conwey! (Darwin would be praut)

Normas del juego de la vida:
  - Si estas vivo y tienes menos de 2 vecinos o mas de 3 vecinos vivos, mueres
  - Si estas vivo y tienes 2 o 3 vecinos vivos, vives
  - Si estas muerta y tienes 3 vecinos vivos, se vuelve una celda viva

These rules, which compare the behavior of the automaton to real life, can be condensed into the following:

Any live cell with two or three live neighbours survives.
Any dead cell with three live neighbours becomes a live cell.
All other live cells die in the next generation. Similarly, all other dead cells stay dead.





######################## TODO

- 2 escenas: configuracion + simulacion --> ?
- recolectar info poblacion //DONE
- plot de datos  --< bonitez de los plots?>
- Control tiempos entrada-salida del calculo paralelo

# POBLACION.CSV
iteracion,# poblacion
