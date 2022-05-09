### Notice
If you find that the solver has messed up (A mine exploded and you see `KABOOM!`) or failed to solve something which is indeed solvable, please send me the field with an explanation. I may have missed something and I want the solver to the best that it can be! Thank you!

# MineSweeper
Welcome to MineSweeper on the command line! This program has two different modes:

1. The first mode is run by using the `make run` command. This mode generates a valid minefield and then tries to solve it. Feel free to adjust the number of mines in the field in `main.cpp` at line 14. 100 mines is considered to be expert level. Any number above 125 will most assuredly not be solvable because there will not be an empty patch big enough from which to begin solving the minefield. While the generator does generate valid fields, guessing may still be required to solve the field. Thus, the solver will not always be able to solve the field because it does not guess.

2. The second mode is more focused on solving a field given by the user. Make sure to have a valid minefield loaded into an `input.txt` file in your MineSweeper directory. The solver will give all new informaion possible by placing `*` on mines and `c` on empty cells. The solver will reload `input.txt` with the updated field. The user needs to fill in the `c` cells with either a number or a space according to what is contained in their field.
### Clone
`git clone https://github.com/poold3/MineSweeper.git`
### Add a MineField
Load any minefield into input.txt. It must have the following format.
```
[#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#]  
[#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#]  
[#][#][2][1][1][#][#][#][#][#][#][#][#][#][#][#][#][#]  
[2][2][1][ ][1][2][#][#][#][#][#][#][#][#][#][#][#][#]  
[ ][ ][ ][ ][ ][2][#][#][#][#][#][#][#][#][#][#][#][#]  
[ ][ ][1][1][1][2][#][#][#][#][#][#][#][#][#][#][#][#]  
[ ][ ][1][#][#][#][#][#][#][#][#][#][#][#][#][#][#][#]  
[ ][ ][1][1][2][#][#][#][#][#][#][#][#][#][2][2][1][1]  
[ ][ ][ ][ ][1][#][#][#][#][#][#][#][#][#][1][ ][ ][ ]  
[ ][ ][ ][ ][1][#][#][#][#][1][1][1][#][#][2][1][1][ ]  
[ ][1][1][1][#][#][#][#][#][2][2][*][2][1][2][*][1][ ]  
[ ][1][#][#][#][#][#][#][#][2][*][2][1][ ][1][2][2][1]  
[ ][1][1][1][1][#][#][#][#][#][2][1][ ][ ][ ][1][*][1]  
[ ][ ][ ][ ][1][#][#][#][#][#][1][1][1][1][ ][1][1][1]  
[ ][ ][ ][ ][1][2][#][#][#][#][1][2][*][2][ ][ ][ ][ ]  
[ ][ ][ ][ ][ ][2][#][5][3][1][1][3][*][2][ ][ ][ ][ ]  
[2][2][1][ ][ ][2][*][*][1][1][3][*][3][1][1][1][1][ ]  
[#][#][1][1][1][2][2][3][2][2][*][*][3][1][1][*][1][ ]  
[2][2][1][2][*][2][ ][1][*][2][2][3][*][1][1][1][1][ ]  
[ ][ ][ ][3][*][5][2][2][1][1][ ][1][2][2][1][ ][ ][ ]  
[ ][ ][ ][2][*][*][*][2][1][1][ ][ ][2][*][2][ ][ ][ ]  
[ ][ ][ ][1][3][4][4][4][*][2][ ][ ][2][*][2][ ][ ][ ]  
[ ][ ][1][2][3][*][2][*][*][3][1][ ][1][1][1][ ][1][1]  
[1][1][2][*][*][2][2][2][3][*][1][ ][1][1][2][1][2][*]  
[1][*][3][3][3][1][ ][ ][1][2][3][2][2][*][2][*][2][1]  
[1][1][2][*][2][1][ ][ ][ ][1][*][*][2][1][2][1][1][ ]  
[ ][ ][1][2][*][1][ ][ ][ ][1][2][2][1][ ][ ][ ][ ][ ]  
[ ][ ][ ][2][2][2][ ][ ][ ][ ][ ][ ][1][1][1][ ][ ][ ]  
[ ][ ][ ][1][*][1][ ][1][1][1][ ][1][2][*][2][1][ ][ ]  
[ ][ ][ ][1][2][2][1][1][*][1][ ][1][*][4][*][2][ ][ ]  
[ ][ ][ ][ ][1][*][2][2][2][1][ ][1][1][3][*][2][ ][ ]  
[ ][ ][ ][ ][1][1][2][*][1][ ][ ][ ][ ][1][1][1][ ][ ]
```
### Notes
```
[#] - Cell content unknown/Cell may contain mine.
[ ] - Cell is verified to be empty.
[*] - Cell is flagged/Cell contains a mine.
[x] - Cell is surrounded by x number of mines. Domain:{1-8}
[c] - Cell should be uncovered/Cell does not contain a mine.
```
### Compile
`make`
### Run
`make run`
The run command will cause the program to generate its own minefield and try to solve it.
### Input
`make input`
The input command will take a field from input.txt within the directory and solve it as much as is possible. Note that the user will have to manually fill in the cells with numbers since the program has no way of knowing what the hidden numbers are in the user's minefield.
### Notes on Field Generation
If you would like to see the fields that are being generated and what an "empty patch" is referring to, uncomment lines 302-303 and 305-307 in `main.cpp`. 

The first field that is shown only contains the mines that were randomly generated in our field. Notice that no single cell is completely surrounded by mines. Additionally, no group of cells is completely surrounded by mines. For a field to be valid, one must be able to traverse through all empty cells on the field by moving up, down, left, right, or diagonally in a chain from empty cell to empty cell. In other words, there can be no cell that is not a neighbor with an empty cell. The generation of such an invalid field is very rare when dealing with only 100 mines. If you would like to see a better example of a correct field, try upping the mines to 200 or 300. Even with that many mines, all the empty cells will be connected.  

The second field shows the field after all the numbers are generated around the mines. An empty patch refers to a group of empty cells from this second field. MineSweeper always begins by uncovering an empty patch. For the field to be valid, there must be at least one empty patch consisting of at least 10 cells. This will give the solver a fair place from which to begin. Anywhere above 150 mines, there will most likely be no empty patch big enough from which to begin.
### Notes on Deduction
While observing the solver work, you may notice the words "Trying Deductions" beign outputted. This occurs when the solver can gain no immediate information from the field. In other words, there are not cells which the solver can automatically flag as a mine. This happens when every number cell with surrounding unknown cells has more unknown cells than the value of the number in the number cell.
At this point, the solver enters a brute force algorithm that tests every possible combination of mine placement around every number cell. If it can eliminate all combinations except one for a single number cell, then the solver knows that it found the right combination.
Even if the solver cannot narrow the combinations of mines around a number cell down to a single combination, further information can be gleaned from the brute force method by tracking if a cell is always labeled as a mine or as an empty cell regardless of the combination of mines.
If you would like to see where this logic is taking place, see lines 724-749 in `Field.h`. Please note that tracking the number of mines found so far and comparing that to the total number of mines known to be in the field is a valid method of solving MineSweeper.
### Notes on SCC
To increase the efficiency of this program, the solver does not iterate through the entire field at once when trying to solve the program. Rather, the program will generate SCCs and the iterate through each SCC.
SCC stands for "Strongly Connected Component". An SCC is a group of number cells that when evaluated individually can affect the way we evaluate the other number cells in the group. In simple terms, an SCC for our purposes is a chain of number cells where each number cell shares a neighbor that could contain a mine with at least one other number cell in the chain. This is more efficient because the solver iterates through groups of cells that affect each other rather than the entire field. We save time by not iterating over cells which do not affect the cells we are currently trying to solve.

Example:
SCC#1 has 5 cells.
SCC#2 has 5 cells.

SCC#1 requires 1 iteration in a fixed-point algorithm.
SCC#2 requires 2 iterations in a fixed-point algorithm.

No SCCs results in iterating over 20 cells.
Using SCCs results in iterating over 15 cells.

A fixed-point algorithm requires a new iteration through the group as long as new information is being generated.

The code regarding the SCC generation and the fixed-point algorithm can be found in the `evaluate` method in `Field.h` at line 758.
