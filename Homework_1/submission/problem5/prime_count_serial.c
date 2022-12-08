#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <omp.h>

#define ITER 60000000
//result is 3562115 primes. took 54.671852 seconds.

bool check_prime(int num)
{
   int i;
   for (i = 2; i <= sqrt(num); i++) {
      if (num % i == 0)
         return false;
   }
   return true;
}

int main( )
{
   int sum = 0;    
   double start_time = omp_get_wtime();
   for (int i = 2; i <= ITER ; i++) {
      if (check_prime(i))
         sum++;
   }
    
   printf("Number of prime numbers is %d in %f sec, with %d threads \n", sum, omp_get_wtime() - start_time, 1);
   return 0;
}