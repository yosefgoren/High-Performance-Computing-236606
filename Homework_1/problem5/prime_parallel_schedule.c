#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <omp.h>

#define ITER 60000000
// control the number of threads here (2,4,8) to fill the table
#define NTHREADS 32
/*
   <scheduling>
      <num threads> <time> <certinty repetitions>

   default
      2 34.562892
      4 18.569548
      8 9.637336
      16 5.263171
   
   static
      2 34.561807
      4 18.606011
      8 9.642268
      16 5.789831

   static4
      2 27.596030
      4 13.829777
      8 7.070557
      16 4.848455
      32 4.239543

   dynamic8
      2 27.705691
      4 13.855253
      8 7.053304
      16 4.299371
      32 3.638962
   
   guided
      2 27.576898
      4 13.805458
      8 6.956129
      10 5.646284
      16 4.262394
      20 3.920670
      32 3.620917
*/


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

   // int serial_section_sum = 0;
   // const int serial_section_iter = 10000000;
   // for (int i = 2; i < serial_section_iter; ++i)
   //    serial_section_sum += check_prime(i);
   
   omp_set_num_threads(NTHREADS);
   #pragma omp parallel for schedule(guided) reduction(+ : sum)
   for (int i = 2; i <= ITER ; i++) {//2 <--- serial_section_iter
      if (check_prime(i))
         sum++;
   }

   // sum += serial_section_iter;    
   printf("Number of prime numbers is %d in %f sec, with %d threads \n", sum, omp_get_wtime() - start_time, NTHREADS);
   return 0;
}