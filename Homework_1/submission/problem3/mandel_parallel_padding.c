#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

# define NPOINTS 3000
# define MAXITER 1000
#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))


struct d_complex {
   double r;
   double i;
};

#define CACHE_SIZE_BYTES 64

int numoutside = 0;
int numoutside_arr[24][CACHE_SIZE_BYTES];//max num threads, when less - ignore tail.

void init_padded_arr(int arr[24][CACHE_SIZE_BYTES], int size){
   for(int i = 0; i < size; ++i){
      arr[i][0] = 0;
   }
}

int sum_padded_arr(int arr[24][CACHE_SIZE_BYTES], int size){
   int sum = 0;
   for(int i = 0; i < size; ++i){
      sum += arr[i][0];
   }
   return sum;
}

int main() {
   int threads[6] = {1,2,4,8,16,24};  
   double area, error, eps = 1.0e-5;
   double start_time, run_time;

   // Test varying number of threads: 1,2,4,8,16 and 24 threads
   for (int k=0; k< NELEMS(threads); k++) {
      int num_of_threads = threads[k];
      init_padded_arr(numoutside_arr, num_of_threads);
      omp_set_num_threads(num_of_threads);
      start_time = omp_get_wtime();
      
      // Loop over grid of points in the complex plane which contains 
      // the Mandelbrot set, test each point to see whether it is 
      // inside or outside the set
      #pragma omp parallel
      {
         int tid = omp_get_thread_num();
         for (int i = tid; i < NPOINTS; i += num_of_threads) {
            // if(i%4 == 0)
            //    printf("thread number %d starting to work on colum %d\n", tid, i);
            struct d_complex c;
            for (int j = 0; j < NPOINTS; j++) {
               c.r = -2.0 + 2.5 * (double)(i) / (double)(NPOINTS) + eps;
               c.i = 1.125 * (double)(j) / (double)(NPOINTS) + eps;
               
               struct d_complex z;
               int iter;
               double temp;

               z = c;
               for (iter = 0; iter < MAXITER; iter++) {
                  temp = (z.r * z.r) - (z.i * z.i) + c.r;
                  z.i = z.r * z.i * 2 + c.i;
                  z.r = temp;
                  if ((z.r * z.r + z.i * z.i) > 4.0) {
                     numoutside_arr[tid][0]++;
                     break;
                  }
               }
            }
         }
      }
      
      numoutside = sum_padded_arr(numoutside_arr, num_of_threads);
      run_time = omp_get_wtime() - start_time;
      // Calculate area of set and error estimate and output the results
      area = 2.0 * 2.5 * 1.125 * (double)(NPOINTS * NPOINTS - numoutside) 
         / (double)(NPOINTS * NPOINTS);
      error = area / (double)NPOINTS;
      printf("Area of Mandlebrot set = %12.8f +/- %12.8f\n",area,error);
      printf("\ntime: %f seconds, with %d threads\n", run_time, num_of_threads);
   }
    
   printf("(Correct answer should be around 1.506)\n");
}