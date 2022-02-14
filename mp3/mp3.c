/* MP3 - Pascal's Triangle
 * Binh-Minh Nguyen (bmn4) UIUC ECE 220 SP 2022
 * Program promts user for a row number then prints out that row of pascal's triangle.
 * Uses choose numbers to calculate items, uses the simplified factorial defintion to calculate nCr.
 */

#include <stdio.h>
#include <stdlib.h>

unsigned long int nCr(int n, int k) {
  unsigned long int result = 1;

  //Implement the multiply/factorial formula
  //Multiply k times
  for(int i = 1; i <= k; i ++) {
    // Factor to multiply (n+1-i/i)
    result *= n + 1 - i;
    result /= i;
  }

  return result;
} 

int main()
{
  int row;

  printf("Enter a row index: ");
  scanf("%d",&row);

  // Write your code here
  for(int i = 0; i <= row; i++) {
    // Print item + ' '
    printf("%lu ", nCr(row,i));
  }

  printf("\n");

  return 0;
}