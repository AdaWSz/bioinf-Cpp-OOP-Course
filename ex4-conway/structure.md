Make it graphical because yes.


1. Class for the grid
  1) Grid will have some defined dimensions (due to computation constraints).
    a. sizeX, sizeY
  2) Grid will be made up of Square objects (as many as the defined dimensions dictate).
  3) The grid must hold data about each and every Square contained on it.
    a. data array containing a lot of Square objects?
    b. Save a StartPos
  4) Must be able to iterate through it - done with arrays i guess.
    a. Iterate left-to-right, top-to-bottom, only render once iteration is done.
  5) Must have data on the generation, maybe on the population too.
    a. generation, population


2. Class for each square on the grid
  1) Square has two states: Alive and dead.
  2) Every iteration (so the whole thing runs in a while loop), each Square on the Grid must check the 8 squares surrounding it:
    a. If dead:
      - If 3 alive neighbors, switch state to alive.
    b. If alive:
      - If <2 alive neighbors, switch state to dead.
      - If 2<=x<=3, no change in state.
      - If >3 alive neighbors, switch state to dead.
