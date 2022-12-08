#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <omp.h>

#define ITER 60000000
// control the number of threads here (2,4,8) to fill the table
#define NTHREADS 8

bool check_prime(int num)
{
   int i;
   for (i = 2; i <= sqrt(num); i++) {
      if (num % i == 0)
         return false;
   }
   return true;
}

int main(){
   int sum = 0;    
   double start_time = omp_get_wtime();

   omp_set_num_threads(NTHREADS);
   int i = 0;
   #pragma omp parallel for schedule(guided) reduction(+ : sum)
   for (i = 2; i <= ITER ; i++) {
      if (check_prime(i))
         sum++;
   }

   printf("Number of prime numbers is %d in %f sec, with %d threads \n", sum, omp_get_wtime() - start_time, NTHREADS);
   return 0;
}