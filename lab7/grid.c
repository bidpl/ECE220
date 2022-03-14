#include <stdio.h>
#include "grid.h"
#include "grid_provided.h"


// Procedure: parse_grid: 
/* Pseudocode algorithm: 
	open the file for reading
	make sure the file is valid
	for each row and column
		scan the file to read the next int into grid at (row, column)
	close the file
*/
//
void parse_grid(const char fpath[], int grid[5][5]) {
	// Open File
	FILE* sudokuGrid = fopen(fpath, "r");

	// If invalid file
	if(sudokuGrid == NULL) {
		printf("Could not open %s", fpath);
		return;
	}

	// Read file to array
	char fileLine[20];

	for(int i = 0; i < 5; i++) {
		// Read one line
		fgets(fileLine, 20, sudokuGrid);

		// Copy it to array
		char post[2];
		int numRead = sscanf(fileLine, "%d %d %d %d %d %2s", &grid[i][0], &grid[i][1], &grid[i][2], &grid[i][3], &grid[i][4], post);

		if (numRead != 5) {
			printf("Invalid row: %s\n", fileLine);
			fclose(sudokuGrid);
			return;
		}

		for(int j = 0; j < 5; j++) {
			if(grid[i][j] < 0 || grid[i][j] > 5) {
				printf("Invalid number at row %d col %d: %d\n", i, j, grid[i][j]);
				fclose(sudokuGrid);
				return;
			}
		}
	}

	fclose(sudokuGrid);
}

// Procedure: solve_grid
// Solve the given grid instance. See wiki for algorithm.
int solve_grid(int grid[5][5]) {
	int row;
	int col;

	// Find next spot, If grid is full, it is solved
	if(!FindUnassignedLocation(grid, &row, &col)) {
		return 1;
	}

	// Try every value in next spot
	for(int i = 1; i <= 5; i++) {
		// If valid, try solving using that value
		if(is_val_valid(i, row, col, grid)) {
			grid[row][col] = i;

			// If it works, you're done
			if(solve_grid(grid)) {
				return 1;
			} else {
				// If it doesn't work, remove item and try next val
				grid[row][col] = 0;
			}
		}
	}

	return 0;
}
