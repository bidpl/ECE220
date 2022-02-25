#include <stdio.h>
#include <stdlib.h>
#include "dice.h"

/* Code to simulate rolling three six-sided dice (D6)
 * User first types in seed value
 * Use seed value as argument to srand()
 * Call roll_three to generate three integers, 1-6
 * Print result "%d %d %d "
 * If triple, print "Triple!\n"
 * If it is not a triple but it is a dobule, print "Double!\n"
 * Otherwise print "\n"
 */


int main() {
    unsigned int seed;

    int one;
    int two;
    int three;

    printf("Enter a seed: \n");
    scanf("%u", &seed);

    srand(seed);

    roll_three(&one, &two, &three);

    printf("%d %d %d ", one, two, three);

    if(one == two && two == three) {
        printf("Triple!\n");
    } else if(one == two || two == three || one == three) {
        printf("Double!\n");
    } else {
        printf("\n");
    }

    return 0;
}