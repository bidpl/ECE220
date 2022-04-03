#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

/* Recursive Maze Solver - MP9 UIUC ECE220 SP22 bmn4
 *
 * I filled out all the functions, just did a lot of safety checking cause James told me people wouldn't :P
 * (yes, checked if file opened, malloc worked, and sscanf worked on file that is already formatted, along with some other stuff)
 * The safety checks don't really do anything since I didn't edit main.c to check for the safety checks here going off
 * 
 */


/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.
    char buff[60]; // Char buffer for file IO, each line should be at most 52 chars
    int i, j; // Loop counters since no -std=c99 compiler option in makefile 

    FILE *fp = fopen(fileName, "r"); // Open the file

    // Check for sucessful file open
    if(fp == NULL) {
        printf("Could not open file, probably invalid filename.\n");
        return NULL;
    }

    // Allocate space for a new maze
    maze_t *maze = malloc(sizeof(maze_t));

    // Read first line to get maze dimensions + check for not empty line
    if(fgets(buff, 60, fp) == NULL) {
        printf("Empty file \n");
        return NULL;
    }

    // Parse the first line for height/width + check for valid reading
    if(sscanf(buff, "%d %d", &(maze->height), &(maze->width)) != 2) {
        printf("Invalid file dimensions: %s\n", buff);
        return NULL;
    }

    // Setup cell matrix

    // Allocate space for cell row pointers + check for allocation success
    maze->cells = malloc(maze->height * sizeof(char*));
    if(maze->cells == NULL) {
        printf("Failed to allocate space for maze\n");
        return NULL;
    }

    // Allocate space for rows + check for allocation success
    for(i = 0; i < maze->height; i++) {
        maze->cells[i] = malloc(maze->width * sizeof(char));
        if(maze->cells[i] == NULL) {
            printf("Failed to allocate space for maze\n");
            return NULL;
        }
    }

    // Scan in maze (doesn't check for extra lines nor multiple starts/ends)
    for(i = 0; i < maze->height; i++) {
        // Read in next line + check for failed read
        if(fgets(buff, 60, fp) == NULL) {
            printf("Not enought lines based on input dimensions \n");
            return NULL;
        }

        for(j = 0; j < maze->width; j++) {
            maze->cells[i][j] = buff[j];

            // Check for start/end and legal characters
            // If start/end, set corresponding coordinates
            // If invalid, return NULL (not required by project)
            if(buff[j] == START) {
                maze->startRow = i;
                maze->startColumn = j;
            } else if(buff[j] == END) {
                maze->endRow = i;
                maze->endColumn = j;
            } else if(buff[j] != ' ' && buff[j] != '%') {
                printf("Illegal maze character '%c' at %d, %d", buff[j], i, j);
                return NULL;
            }
        }
    }

    // Close file
    fclose(fp);

    return maze;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    // Your code here.

    int i; // Loop counter

    // Free cells array rows
    for(i = 0; i < maze->height; i++) {
        free(maze->cells[i]);
    }

    // Frees cell array
    free(maze->cells);

    // Free rest of maze
    free(maze);
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here.

    int i,j; // Loop counter, again not c99

    // Take each line of maze and print it to stdout
    for(i = 0; i < maze->height; i++) {
        // Print each character in each line then newline at the end
        for(j = 0; j < maze->width; j++) {
            printf("%c", maze->cells[i][j]);
        }

        printf("\n");
    }
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.

    // Check for recursion base cases -> Hitting end
    if(maze->cells[row][col] == END) {
        return 1;
    }

    // Record that this spot is on the current path we are checking
    if(maze->cells[row][col] == EMPTY){
        maze->cells[row][col] = PATH;
    }
    
    // Check left, right, up, then down (only if in bounds + empty/end spot)
    if( (col - 1 > 0) && ((maze->cells[row][col-1] == EMPTY) || (maze->cells[row][col-1] == END)) ) { 
        if(solveMazeDFS(maze, col-1, row)) {
            return 1;
        }
    }
    
    // Check right
    if( (col + 1 < maze->width) && ((maze->cells[row][col+1] == EMPTY) || (maze->cells[row][col+1] == END)) ) { 
        if(solveMazeDFS(maze, col+1, row)) {
            return 1;
        }
    }
    
    // Check up
    if( (row - 1 > 0) && ((maze->cells[row-1][col] == EMPTY) || (maze->cells[row-1][col] == END)) ) { 
        if(solveMazeDFS(maze, col, row-1)) {
            return 1;
        }
    }
    
    // Check down
    if( (row + 1 < maze->height) && ((maze->cells[row+1][col] == EMPTY) || (maze->cells[row+1][col] == END)) ) {
        if(solveMazeDFS(maze, col, row+1)) {
            return 1;
        }
    }

    // If none of the options reach end, this is a dead end so mark it as visited and return 0
    maze->cells[row][col] = VISITED;
    return 0;
}
