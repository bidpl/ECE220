#include "sliding.h"
/*  Slide all values of array up
*/
void slide_up(int* my_array, int rows, int cols){
    // In each col
    for(int n = 0; n < cols; n++) {
        // Check each row
        for(int m = 0; m < rows; m++) {
            
            // If cell is not empty
            if(my_array[m*cols + n] != -1) {
                // Find first empty cell above it (if it exists)
                for(int i = 0; i < m; i++) {
                    // If it does, move the number into that spot
                    if(my_array[i*cols + n] == -1) {
                        my_array[i*cols + n] = my_array[m*cols + n];
                        my_array[m*cols + n] = -1;
                    }
                }

            }
        }
    }
    return;
}
