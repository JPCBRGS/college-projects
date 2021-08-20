# 8 Puzzle game using the A* search algorithm

This project contains a solution for the 8 Puzzle game using the A* search algorithm. I didn't implement 100% of this code as some classes were already given previously, but the **AEstrelaImp.py** file which contains the class that represents algorithm and problem solving was entirely implemented by myself, João Pedro Clemente Borges. There are some comments in Portuguese explaining some relevant parts of the code, and how it works. 

## Game and code explanation:
The 8 Puzzle game consists of a 3x3 matrix with values that go from 1 to 8 on each cell of this matrix, and the 9th position is a void one. The table is initially shuffled, and the game objective is moving the void position in a way such as the numbers inside the matrix become ordered. You can set any table you want on the **main.py** file, and as you compile this same file, the output will be the series of positions you have to move the void cell to so that you solve the game and get to the objective state. A* algorithm is an efficient way of solving this problem since it's an efficient search method to search for the best move. More information about these topics will be linked below.

## Useful links:
**For more information about the 8 Puzzle with A* algorithm:*  https://www.d.umn.edu/~jrichar4/8puz.html

**For more information on the algorithm:* https://en.wikipedia.org/wiki/A*_search_algorithm
