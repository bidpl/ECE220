#include "prime.h"
#include <math.h>

int is_prime(int n){
  // Return 1 if n is a prime, and 0 if it is not
  if(n<=1) {return 0;} // Check for 1, 0, or negative

  for(int i = 2; i < sqrt(n); i++) {
    if(n % i == 0) {
      return 0;
    }
  }

  return 1;
}

