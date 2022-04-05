# MineSweeper
This program will help you solve MineSweeper! It is meant to be run on the command line.
### Clone
`git clone https://github.com/poold3/MineSweeper.git`
### Add a MineField
Load any minefield into input.txt. It must have the following format.
```
[ ][1][*][*][*][*][*]
[ ][1][1][2][1][2][*]
[ ][ ][ ][ ][ ][1][*]
[1][1][ ][ ][ ][2][*]
[*][2][ ][ ][ ][1][*]
[*][2][ ][ ][ ][1][*]
[*][1][ ][ ][1][1][*]
[*][1][1][1][1][*][*]
[*][*][*][*][*][*][*]
[*][*][*][*][*][*][*]
```
### Notes
```
[*] - Cell content unknown/Cell may contain mine
[ ] - Cell is verified to be empty
[f] - Cell is flagged
[x] - Cell is surrounded by x number of mines. Domain:{1-8}
```
### Compile
`make`
### Run
`make run`
