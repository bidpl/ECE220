#include <stdio.h>
#include "prime.h"

int main(){
  // Write the code to take a number n from user and print all the prime numbers between 1 and n
  int n;

  printf("Enter value of n: ");
  scanf("%d", &n);

  printf("Printing primes less than or equal of %d:\n", n);

  for(int i = 1; i <= n; i++) {
    if(is_prime(i)){
      printf("%d\n", i);
    }
  } 

  return 0;
}

