/* ECE 220 MP6 Game of Life - UIUC SP2022 (bmn4)
 * I completed the countLiveNeighbor(), udpateBoard(), and aliveStable() functions
 * Instead of making a copy of the array to store the next state in updateBoard, I store the next state in the second bit of the board (board is array of ints, we only use LSB). This way some memory is saved, I'm not sure about memory access.
 * Other two I did in a pretty standard way
 */


/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
    int numAlive = 0;

    // 3 rows (above, same, below)
    for(int i = -1; i <= 1; i++) {
        // 3 cols (left, same, right)
        for(int j = -1; j <= 1; j++) {
            // Make sure target cell is valid coordinates
            if((row+i < boardRowSize) && (row+i >= 0) && (col+j < boardColSize) && (col+j >=0)) {
                // Increment of alive and not self, bitwise and to mask last bit (MSB might be 1)
                if((board[(row+i) * boardColSize + col+j] & 0b1) && !(i == 0 && j == 0)) {
                    numAlive++;
                }
            }
        }
    }

    return numAlive;
}
/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
    //Instead of making a temp array, I'm just going to use the MSB to temp store next state (1/negative will be alive next, 0/positive will be dead next)

    int numAlive;

    //Store next state into bit 2
    for(int r = 0; r < boardRowSize; r++) {
        for(int c = 0; c < boardColSize; c++) {
            numAlive = countLiveNeighbor(board, boardRowSize, boardColSize, r, c);
            
            //Default next state is dead (defualt 1 (0b01) or 0 (0b00)), next alive would be 2 (0b10) or 3 (0b11)
            //If 2 alive neighbors and is alive
            //or If 3 alive neighbors
            //it will be alive next time
            if( (numAlive == 2  && board[(r) * boardColSize + c]) || numAlive == 3 ) {
                board[(r) * boardColSize + c] |= 0b10;
            }
        }
    }

    //Get next state in cell bit 2 and write to cell
    for(int r = 0; r < boardRowSize; r++) {
        for(int c = 0; c < boardColSize; c++) {
            board[(r) * boardColSize + c] >>= 1;
        }
    }
}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){
    int numAlive;

    //Check every cell
    for(int r = 0; r < boardRowSize; r++) {
        for(int c = 0; c < boardColSize; c++) {
            //Get number of alive neighbors
            numAlive = countLiveNeighbor(board, boardRowSize, boardColSize, r, c);
            
            //If next state is forced alive and currently dead, or if next state is forced dead and currently alive, it's going to change so board isn't stable
            if( (numAlive == 3 && !board[(r) * boardColSize + c]) || ((numAlive < 2 || numAlive > 3) && board[(r) * boardColSize + c]) ) {
                return 0;
            }
        }
    }

    // If nothing changes, it's stable
    return 1;
}

				
				
			

