/* Semiprime generator - UIUC ECE220 MP4 2/18/2022
 * "debugged" (just fixed the errors) by Binh-Minh Nguyen (bmn4) for mp4
 * Takes two numbers  from terminal, prints out semiprime numbers between them.
 * 
 * Fixes:
 * Added ';' on main.c line 28 -> Fix compiler/syntax error
 * is_prime: swapped return values, they were flipped in original
 *  - This would make is_prime return the wrong value, saying prime #s are composite and composites #s prime
 * print_semiprimes: k = i/j, originally i%j
 *  - This would return k = 0, so anything with at least one prime factor would be considered semiprime
 * print_semiprimes: added break after printing a number so we wouldn't check it twice
 *  - Without this som numbers would print twice e.g. 6 prints twice since it's 2x3 and 3x2
 * print_semiprimes: set ret = 1 when a number is printed (when a semi-prime is detected)
 *  - It was always returning 0 without this line.
 * 
 * End intro paragraph
 */

#include <stdlib.h>
#include <stdio.h>


/*
 * is_prime: determines whether the provided number is prime or not
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
    int i;
    if (number == 1) {return 0;}
    for (i = 2; i < number; i++) { //for each number smaller than it
        if (number % i == 0) { //check if the remainder is 0
            return 0;
        }
    }
    return 1;
}


/*
 * print_semiprimes: prints all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
    int i, j, k;
    int ret = 0;
    for (i = a; i <=b; i++) { //for each item in interval
        //check if semiprime
        for (j = 2; j <= i; j++) {
            if (i%j == 0) {
                if (is_prime(j)) {
                    k = i/j;
                    if (is_prime(k)) {
                        ret = 1;
                        printf("%d ", i);
                        break; // Only need to print once per number, don't check again
                    }
                }
            }
        }

    }
    printf("\n");
    return ret;

}
