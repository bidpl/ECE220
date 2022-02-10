#include <stdio.h>
#include <math.h>

#define M_PI 3.14159265358979323846

/*
 * main
 *  DESCRIPTION: compute a set of points of a function and print the results
 *  INPUTS: console (int, float float) -- equation related constants
 *  OUTPUTS: console (x, f(x)) -- sequence of values to be printed
 *  RETURN VALUE: 0
 *  SIDE EFFECTS: none
 */
int main()
{
    // Declare variables
    int n, w1, w2;
        
    // Prompt user for input
    printf("Enter the values of n, omega1, and omega2 in that order\n");
    
    // Get user input
    scanf("%d %d %d", &n, &w1, &w2);
    
    // Compute function output
    /* for i from 0 to n-1
     *     compute and print xi and f(xi)
     *     use sin() function from math.h
     */
    
    for(int i = 0; i < n; i++) {
        double xi = M_PI / n;
        xi = xi * i;

        double fi = sin(w1*xi) + 0.5 * sin(w2*xi);

        printf("(%lf, %lf)\n", xi, fi);
    }

    return 0;
}

